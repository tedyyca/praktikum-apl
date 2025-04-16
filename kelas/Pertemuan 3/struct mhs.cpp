#include <iostream>
#include <string>
using namespace std;


struct Mahasiswa {
    string nim;
    string nama;
    float nilai;
};


void tampilkanData(Mahasiswa mhs[], int jumlah) {
    cout << "\nData Mahasiswa:\n";
    cout << "====================================\n";
    for(int i = 0; i < jumlah; i++) {
        cout << "Mahasiswa " << i+1 << ":\n";
        cout << "NIM   : " << mhs[i].nim << endl;
        cout << "Nama  : " << mhs[i].nama << endl;
        cout << "Nilai : " << mhs[i].nilai << endl;
        cout << "------------------------------------\n";
    }
}

int main() {
    int jumlahMhs;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlahMhs;
    cin.ignore(); 
    
   
    Mahasiswa *mhs = new Mahasiswa[jumlahMhs];
    
    for(int i = 0; i < jumlahMhs; i++) {
        cout << "\nMasukkan data mahasiswa " << i+1 << ":\n";
        cout << "NIM   : ";
        getline(cin, mhs[i].nim);
        cout << "Nama  : ";
        getline(cin, mhs[i].nama);
        cout << "Nilai : ";
        cin >> mhs[i].nilai;
        cin.ignore(); 
    }
    
    
    tampilkanData(mhs, jumlahMhs);
    
    [] mhs;
    
    return 0;
}