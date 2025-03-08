#include <iostream>
#include <string>

using namespace std;

int main() {
   
    string nama_terdaftar = "MTedyAzhari";
    string nim_terdaftar = "2409106003";
    
    cout << "==========================================" << endl;
    cout << "| Selamat Datang di Program Konversi     |" << endl;
    cout << "| Satuan Ukuran Panjang                  |" << endl;
    cout << "==========================================" << endl;
    
    int percobaan_login = 0;
    bool login_berhasil = false;
    
    while (percobaan_login < 3 && !login_berhasil) {
        string nama_input, nim_input;
        
        cout << "\n+--------------- Login -----------------+" << endl;
        cout << "| Masukkan Nama: ";
        cin >> nama_input;
        cout << "| Masukkan NIM : ";
        cin >> nim_input;
        cout << "+---------------------------------------+" << endl;

        cout << "+---------------------------------------+" << endl;
        if (nama_input == nama_terdaftar && nim_input == nim_terdaftar) {
            login_berhasil = true;
            cout << "| Login Berhasil!                       |" << endl;
            cout << "| Selamat datang, " << nama_terdaftar << "!          |" << endl;
            cout << "+---------------------------------------+" << endl;
        } else {
            percobaan_login++;
            int sisa_percobaan = 3 - percobaan_login;
            cout << "| Login Gagal!                          |" << endl;
            cout << "| Sisa percobaan: " << sisa_percobaan << "           |" << endl;
            cout << "+---------------------------------------+" << endl;
            
            if (percobaan_login == 3) {
                cout << "| Anda telah melebihi batas percobaan. |" << endl;
                cout << "| Program berakhir karena gagal login. |" << endl;
                cout << "+---------------------------------------+" << endl;
                return 0;
            }
        }
    }

    bool program_berjalan = true;
    
    while (program_berjalan) {
        string pilihan_menu;
        
        cout << "\n==========================================" << endl;
        cout << "|    MENU KONVERSI SATUAN PANJANG        |" << endl;
        cout << "==========================================" << endl;
        cout << "| 1. Meter  -> [Cm, Mile, Foot]          |" << endl;
        cout << "| 2. Cm     -> [Meter, Mile, Foot]       |" << endl;
        cout << "| 3. Mile   -> [Meter, Cm, Foot]         |" << endl;
        cout << "| 4. Foot   -> [Meter, Cm, Mile]         |" << endl;
        cout << "| 5. Keluar                              |" << endl;
        cout << "==========================================" << endl;
        cout << "| Pilih menu (1-5): ";
        cin >> pilihan_menu;
        cout << "==========================================" << endl;
        
        if (pilihan_menu == "1") {
            cout << "\n+------- Konversi dari Meter --------+" << endl;
            double nilai_meter;
            cout << "| Masukkan nilai (Meter): ";
            cin >> nilai_meter;
            double nilai_centimeter = nilai_meter * 100;  
            double nilai_mile = nilai_meter * 0.000621371; 
            double nilai_foot = nilai_meter * 3.28084;
            
            cout << "+-------------------------------------+" << endl;
            cout << "| Hasil Konversi:                    |" << endl;
            cout << "| " << nilai_meter << " m  = " << nilai_centimeter << " cm         |" << endl;
            cout << "| " << nilai_meter << " m  = " << nilai_mile << " mile      |" << endl;
            cout << "| " << nilai_meter << " m  = " << nilai_foot << " ft        |" << endl;
            cout << "+-------------------------------------+" << endl;
            
        } else if (pilihan_menu == "2") {
            cout << "\n+------- Konversi dari Cm -----------+" << endl;
            double nilai_centimeter;
            cout << "| Masukkan nilai (Cm): ";
            cin >> nilai_centimeter;
            double nilai_meter = nilai_centimeter * 0.01;     
            double nilai_mile = nilai_centimeter * 0.00000621371;  
            double nilai_foot = nilai_centimeter * 0.0328084;  
            
            cout << "+-------------------------------------+" << endl;
            cout << "| Hasil Konversi:                    |" << endl;
            cout << "| " << nilai_centimeter << " cm = " << nilai_meter << " m          |" << endl;
            cout << "| " << nilai_centimeter << " cm = " << nilai_mile << " mile      |" << endl;
            cout << "| " << nilai_centimeter << " cm = " << nilai_foot << " ft        |" << endl;
            cout << "+-------------------------------------+" << endl;
            
        } else if (pilihan_menu == "3") {
            cout << "\n+------- Konversi dari Mile ---------+" << endl;
            double nilai_mile;
            cout << "| Masukkan nilai (Mile): ";
            cin >> nilai_mile;
            double nilai_meter = nilai_mile * 1609.34;      
            double nilai_centimeter = nilai_mile * 160934; 
            double nilai_foot = nilai_mile * 5280;          
            
            cout << "+-------------------------------------+" << endl;
            cout << "| Hasil Konversi:                    |" << endl;
            cout << "| " << nilai_mile << " mile = " << nilai_meter << " m          |" << endl;
            cout << "| " << nilai_mile << " mile = " << nilai_centimeter << " cm        |" << endl;
            cout << "| " << nilai_mile << " mile = " << nilai_foot << " ft        |" << endl;
            cout << "+-------------------------------------+" << endl;
            
        } else if (pilihan_menu == "4") {
            cout << "\n+------- Konversi dari Foot ---------+" << endl;
            double nilai_foot;
            cout << "| Masukkan nilai (Foot): ";
            cin >> nilai_foot;
            double nilai_meter = nilai_foot * 0.3048;       
            double nilai_centimeter = nilai_foot * 30.48;  
            double nilai_mile = nilai_foot * 0.000189394;   
            
            cout << "+-------------------------------------+" << endl;
            cout << "| Hasil Konversi:                    |" << endl;
            cout << "| " << nilai_foot << " ft  = " << nilai_meter << " m          |" << endl;
            cout << "| " << nilai_foot << " ft  = " << nilai_centimeter << " cm        |" << endl;
            cout << "| " << nilai_foot << " ft  = " << nilai_mile << " mile      |" << endl;
            cout << "+-------------------------------------+" << endl;
            
        } else if (pilihan_menu == "5") {
            cout << "\n|=============================================|" << endl;
            cout << "| Terima kasih telah menggunakan program ini! |" << endl;
            cout << "| Sampai jumpa!                               |" << endl;
            cout << "|=============================================|" << endl;
            program_berjalan = false;
        } else {
            cout << "\n+-------------------------------------+" << endl;
            cout << "|Pilihan tidak valid! Pilih angka 1-5.|" << endl;
            cout << "+-------------------------------------+" << endl;
        }
    }
    
    return 0;
}