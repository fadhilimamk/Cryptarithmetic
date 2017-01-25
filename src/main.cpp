// File  : main.cpp
// Name  : Fadhil Imam Kurnia - 13515146
// Program to solving cryptarithmatic with brute force

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
using namespace std;

list<int> idx_char;
vector<int> idx_char_v;
vector<int> temp;
int angka[26];
string result;
vector<string> operand;
bool selesai = false;

// fungsi untuk merubah string s, baik operan atau hasil menjadi angka
int stringToNumber(string s);

// fungsi untuk menghitung dari hasil tebakan. Menghasilkan true jika
// hasil evaluasi tebakan memenuhi cryptarithmatic
bool evaluasi();

// prosedur untuk menulis hasil cryptarithmatic
void writeResult();

// prosedur rekursif untuk melakukan bruteforce
void checkAll(int offset, int k);

// program utama
int main(){
  string s;
  int i;

  // membaca masukan cryptarithmatic bagian operan-operan
  do{
    getline(cin, s);
    i = 0;
    while( i < ( (s[s.length()-1]!='+')? s.length() : s.length()-1)){
      idx_char.push_back( (int) s[i]-'A');
      angka[(int) s[i]-'A'] = i; // inisialisasi
      i++;
    }
    operand.push_back(s);
  }while(s[s.length()-1]!='+');
  operand.back() = operand.back().substr(0, operand.back().length()-1);
  getline(cin, s);
  getline(cin, result);

  // membaca masukan cryptarithmatic bagian hasil penjumlahan
  i = 0;
  while(i<result.length()){
    idx_char.push_back( (int) result[i]-'A');
    angka[(int) s[i]-'A'] = i; // inisialisasi
    i++;
  }

  // mendata kemunculan huruf, namun meletekan awal huruf pada hasil penjumlahan pertama kali
  auto t_start = std::chrono::high_resolution_clock::now();
  idx_char.sort();
  idx_char.unique();
  for (list<int>::iterator it = idx_char.begin(); it != idx_char.end(); ++it){
    if(*it == result[0]-'A')
        idx_char_v.insert(idx_char_v.begin(),*it);
    else
      idx_char_v.push_back(*it);
  }

  if(idx_char_v.size()>10){
    cout << "Tidak ada solusi" << endl;
  }else{
    // memulai bruteforce dengan fungsi rekursif, menampilkan hasilnya, serta menghitung waktunya
    checkAll(0,idx_char.size());
    if(!selesai)
      cout << "Tidak ada solusi" << endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    cout  << endl
          << endl
          << "waktu: "
          << std::chrono::duration<double, std::milli>(t_end-t_start).count()
          << " ms"
          << endl;
  }

  return 0;
}

int stringToNumber(string s){
  int hasil, i;

  hasil = 0;
  for(i = 0; i < s.length() ; i++){
    hasil = (hasil*10) + angka[(int) s[i]-'A'];
  }
  return hasil;
}

bool evaluasi(){
  int hasil, temp, i;
  bool fail;

  hasil = stringToNumber(result); temp = 0; i = 0;
  fail = false;

  if(angka[(int)result[0]-'A'] == 0)
    return false;

  while(i < operand.size() && !fail){
    if(angka[operand[i][0]-'A'] == 0){
      fail = true;
    }else{
      temp = temp + stringToNumber(operand[i]);
      i++;
    }
  }

  if(fail)
    return false;
  else
    return (temp == hasil);
}

void writeResult(){
  int i;

  i = 0;
  while(i < operand.size()-1){
    cout << operand[i] << endl;
    i++;
  }
  cout << operand[i] << "+" << endl;

  cout << "--------" << endl;
  cout << result<< endl << endl;

  // menulis hasil
  i = 0;
  while(i < operand.size()-1){
    cout << stringToNumber(operand[i]) << endl;
    i++;
  }
  cout << stringToNumber(operand[i]) << "+" << endl;
  cout << "--------" << endl;
  cout << stringToNumber(result)<< endl;

}

void checkAll(int offset, int k){
  bool found; int j;

  if(selesai)
    return;
  else if(k == 0){
    if(evaluasi()){
      writeResult();
      selesai = true;
    }
    return;
  }else{
    // brute force dari 1 sampai 9
    for(int i = 1; i<=9; i++){
      found = false; j = 0;
      while(j < temp.size() && !found){
        if(temp[j] == i)
          found = true;
        else
          j++;
      }
      if(!found){
        angka[idx_char_v[offset]] = i;
        temp.push_back(i);
        checkAll(offset+1,k-1);
        temp.pop_back();
      }
    }

    // brute force untuk angka 0
    found = false; j = 0;
    while(j < temp.size() && !found){
      if(temp[j] == 0)
        found = true;
      else
        j++;
    }
    if(!found){
      angka[idx_char_v[offset]] = 0;
      temp.push_back(0);
      checkAll(offset+1,k-1);
      temp.pop_back();
    }

  }
}
