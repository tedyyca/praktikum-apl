#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_USERS = 100;
const int MAX_CONTACTS = 100;

struct Users {
    string nama;
    string nim;
    struct Contact {  
        string namaKontak;    
        string telepon;       
        string kategori;      
        string alamatKontak;  
    };
    Contact contacts[MAX_CONTACTS]; 
    int jumlahKontak;
};

int main() {
    Users users[MAX_USERS];
    int userCount = 0;
    bool programRunning = true;

    users[0].nama = "MTedyAzhari";
    users[0].nim = "2409106003";
    users[0].jumlahKontak = 0;
    userCount = 1;

    while (programRunning) {
        
        cout << "\n+------------------------------------------+\n";
        cout << "|      HOMEPAGE DIREKTORI KONTAK           |\n";
        cout << "+------------------------------------------+\n";
        cout << "|  No  |          Pilihan                  |\n";
        cout << "+------------------------------------------+\n";
        cout << "|  1   | Register                          |\n";
        cout << "|  2   | Login                             |\n";
        cout << "|  3   | Keluar Program                    |\n";
        cout << "+------------------------------------------+\n";
        cout << "| Pilihan Anda: ";
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n+------------------------------------------+\n";
            cout << "| Input tidak valid! Masukkan angka.       |\n";
            cout << "+------------------------------------------+\n";
            continue;
        }

        switch (choice) {
            case 1: {
                if (userCount >= MAX_USERS) {
                    cout << "\n+------------------------------------------+\n";
                    cout << "| User sudah penuh!                          |\n";
                    cout << "+------------------------------------------+\n";
                    break;
                }
                cin.ignore();
                cout << "\n+------------------------------------------+\n";
                cout << "|        REGISTER PENGGUNA BARU            |\n";
                cout << "+------------------------------------------+\n";
                cout << "| Nama: ";
                string newNama;
                getline(cin, newNama);

                bool nameExists = false;
                for (int i = 0; i < userCount; i++) {
                    if (users[i].nama == newNama) {
                        nameExists = true;
                        break;
                    }
                }
                if (nameExists) {
                    cout << "\n+------------------------------------------+\n";
                    cout << "| Nama sudah terdaftar! Gunakan nama lain. |\n";
                    cout << "+------------------------------------------+\n";
                    break;
                }

                cout << "| NIM: ";
                string newNim;
                getline(cin, newNim);

                users[userCount].nama = newNama;
                users[userCount].nim = newNim;
                users[userCount].jumlahKontak = 0;
                userCount++;
                cout << "\n+------------------------------------------+\n";
                cout << "|         Pendaftaran berhasil!            |\n";
                cout << "+------------------------------------------+\n";
                break;
            }
            case 2: {
                if (userCount == 0) {
                    cout << "\n+------------------------------------------+\n";
                    cout << "|     Belum ada pengguna terdaftar!        |\n";
                    cout << "+------------------------------------------+\n";
                    break;
                }
                string inputNama;
                string inputNim;
                int loginAttempts = 0;
                bool loggedIn = false;
                int currentUser = -1;

                cin.ignore();
                while (loginAttempts < 3 && !loggedIn) {
                    cout << "\n+------------------------------------------+\n";
                    cout << "|                LOGIN                     |\n";
                    cout << "+------------------------------------------+\n";
                    cout << "| Nama: ";
                    getline(cin, inputNama);
                    cout << "| NIM:  ";
                    getline(cin, inputNim);
                    cout << "+------------------------------------------+\n";
                    
                    for (int i = 0; i < userCount; i++) {
                        if (users[i].nama == inputNama && users[i].nim == inputNim) {
                            loggedIn = true;
                            currentUser = i;
                            break;
                        }
                    }
                    if (!loggedIn) {
                        loginAttempts++;
                        cout << "\n+------------------------------------------+\n";
                        cout << "| Nama atau NIM salah! Percobaan ke-" << loginAttempts << " dari 3 |\n";
                        cout << "+------------------------------------------+\n";
                    }
                }
                
                if (!loggedIn) {
                    cout << "\n+------------------------------------------+\n";
                    cout << "| Anda telah 3 kali gagal login.           |\n";
                    cout << "| Program berhenti.                        |\n";
                    cout << "+------------------------------------------+\n";
                    programRunning = false; 
                    break; 
                }

                cout << "\n+------------------------------------------+\n";
                cout << "| Login berhasil! Selamat datang, " << setw(10) << left << users[currentUser].nama << "|\n";
                cout << "+------------------------------------------+\n";
                bool sessionRunning = true;

                while (sessionRunning) {
                    cout << "\n+------------------------------------------+\n";
                    cout << "|           MENU DIREKTORI KONTAK          |\n";
                    cout << "+------------------------------------------+\n";
                    cout << "|  No  |          Pilihan                  |\n";
                    cout << "+------------------------------------------+\n";
                    cout << "|  1   | Tambah Kontak Baru                |\n";
                    cout << "|  2   | Tampilkan Semua Kontak            |\n";
                    cout << "|  3   | Perbarui Kontak                   |\n";
                    cout << "|  4   | Hapus Kontak                      |\n";
                    cout << "|  5   | Keluar                            |\n";
                    cout << "+------------------------------------------+\n";
                    cout << "| Pilihan Anda: ";
                    
                    int menuChoice;
                    if (!(cin >> menuChoice)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\n+------------------------------------------+\n";
                        cout << "| Input tidak valid! Masukkan angka.       |\n";
                        cout << "+------------------------------------------+\n";
                        continue;
                    }

                    switch (menuChoice) {
                        case 1: {
                            if (users[currentUser].jumlahKontak >= MAX_CONTACTS) {
                                cout << "\n+------------------------------------------+\n";
                                cout << "| Kontak penuh! Hapus kontak dulu.         |\n";
                                cout << "+------------------------------------------+\n";
                                break;
                            }
                            cin.ignore();
                            cout << "\n+------------------------------------------+\n";
                            cout << "|         TAMBAH KONTAK BARU               |\n";
                            cout << "+------------------------------------------+\n";
                            cout << "| Nama: ";
                            getline(cin, users[currentUser].contacts[users[currentUser].jumlahKontak].namaKontak);
                            cout << "| Nomor Telepon: ";
                            getline(cin, users[currentUser].contacts[users[currentUser].jumlahKontak].telepon);
                            cout << "| Kategori (keluarga/teman/bisnis): ";
                            getline(cin, users[currentUser].contacts[users[currentUser].jumlahKontak].kategori);
                            cout << "| Alamat: ";
                            getline(cin, users[currentUser].contacts[users[currentUser].jumlahKontak].alamatKontak);
                            cout << "+------------------------------------------+\n";
                            users[currentUser].jumlahKontak++;
                            cout << "\n+------------------------------------------+\n";
                            cout << "|      Kontak berhasil ditambahkan!        |\n";
                            cout << "+------------------------------------------+\n";
                            break;
                        }
                        case 2: {
                            if (users[currentUser].jumlahKontak == 0) {
                                cout << "\n+------------------------------------------+\n";
                                cout << "|   Tidak ada kontak yang tersimpan.       |\n";
                                cout << "+------------------------------------------+\n";
                                break;
                            }
                            cout << "\n+------------------------------------------+\n";
                            cout << "|         DAFTAR SEMUA KONTAK              |\n";
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            cout << "| No  | " << setw(28) << left << "Nama" 
                                 << " | " << setw(18) << left << "Nomor Telepon" 
                                 << " | " << setw(18) << left << "Kategori" 
                                 << " | " << setw(28) << left << "Alamat" << " |\n";
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            for (int i = 0; i < users[currentUser].jumlahKontak; i++) {
                                cout << "| " << setw(3) << right << (i + 1) << " | "
                                     << setw(28) << left << users[currentUser].contacts[i].namaKontak << " | "
                                     << setw(18) << left << users[currentUser].contacts[i].telepon << " | "
                                     << setw(18) << left << users[currentUser].contacts[i].kategori << " | "
                                     << setw(28) << left << users[currentUser].contacts[i].alamatKontak << " |\n";
                            }
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            break;
                        }
                        case 3: {
                            if (users[currentUser].jumlahKontak == 0) {
                                cout << "\n+------------------------------------------+\n";
                                cout << "|   Tidak ada kontak yang tersimpan.       |\n";
                                cout << "+------------------------------------------+\n";
                                break;
                            }
                            cout << "\n+------------------------------------------+\n";
                            cout << "|           PERBARUI KONTAK                |\n";
                            cout << "+------------------------------------------+\n";
                            cout << "| Jumlah kontak saat ini: " << setw(20) << left << users[currentUser].jumlahKontak << "|\n";
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            cout << "| No  | " << setw(28) << left << "Nama" 
                                 << " | " << setw(18) << left << "Nomor Telepon" 
                                 << " | " << setw(18) << left << "Kategori" 
                                 << " | " << setw(28) << left << "Alamat" << " |\n";
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            for (int i = 0; i < users[currentUser].jumlahKontak; i++) {
                                cout << "| " << setw(3) << right << (i + 1) << " | "
                                     << setw(28) << left << users[currentUser].contacts[i].namaKontak << " | "
                                     << setw(18) << left << users[currentUser].contacts[i].telepon << " | "
                                     << setw(18) << left << users[currentUser].contacts[i].kategori << " | "
                                     << setw(28) << left << users[currentUser].contacts[i].alamatKontak << " |\n";
                            }
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            int index;
                            cout << "| Masukkan nomor kontak (1-" << users[currentUser].jumlahKontak << "): ";
                            cin >> index;
                            cout << "+------------------------------------------+\n";
                            if (index < 1 || index > users[currentUser].jumlahKontak) {
                                cout << "\n+------------------------------------------+\n";
                                cout << "|       Nomor kontak tidak valid!          |\n";
                                cout << "+------------------------------------------+\n";
                                break;
                            }
                            index--;
                            cin.ignore();
                            cout << "| Nama baru ('" << users[currentUser].contacts[index].namaKontak << "'): ";
                            string namaBaru;
                            getline(cin, namaBaru);
                            if (namaBaru != "") users[currentUser].contacts[index].namaKontak = namaBaru;
                            cout << "| Nomor telepon baru ('" << users[currentUser].contacts[index].telepon << "'): ";
                            string teleponBaru;
                            getline(cin, teleponBaru);
                            if (teleponBaru != "") users[currentUser].contacts[index].telepon = teleponBaru;
                            cout << "| Kategori baru ('" << users[currentUser].contacts[index].kategori << "'): ";
                            string kategoriBaru;
                            getline(cin, kategoriBaru);
                            if (kategoriBaru != "") users[currentUser].contacts[index].kategori = kategoriBaru;
                            cout << "| Alamat baru ('" << users[currentUser].contacts[index].alamatKontak << "'): ";
                            string alamatBaru;
                            getline(cin, alamatBaru);
                            if (alamatBaru != "") users[currentUser].contacts[index].alamatKontak = alamatBaru;
                            cout << "+------------------------------------------+\n";
                            cout << "\n+------------------------------------------+\n";
                            cout << "|       Kontak berhasil diperbarui!        |\n";
                            cout << "+------------------------------------------+\n";
                            break;
                        }
                        case 4: {
                            if (users[currentUser].jumlahKontak == 0) {
                                cout << "\n+------------------------------------------+\n";
                                cout << "|   Tidak ada kontak yang tersimpan.       |\n";
                                cout << "+------------------------------------------+\n";
                                break;
                            }
                            cout << "\n+------------------------------------------+\n";
                            cout << "|            HAPUS KONTAK                  |\n";
                            cout << "+------------------------------------------+\n";
                            cout << "| Jumlah kontak saat ini: " << setw(20) << left << users[currentUser].jumlahKontak << "|\n";
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            cout << "| No  | " << setw(28) << left << "Nama" 
                                 << " | " << setw(18) << left << "Nomor Telepon" 
                                 << " | " << setw(18) << left << "Kategori" 
                                 << " | " << setw(28) << left << "Alamat" << " |\n";
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            for (int i = 0; i < users[currentUser].jumlahKontak; i++) {
                                cout << "| " << setw(3) << right << (i + 1) << " | "
                                     << setw(28) << left << users[currentUser].contacts[i].namaKontak << " | "
                                     << setw(18) << left << users[currentUser].contacts[i].telepon << " | "
                                     << setw(18) << left << users[currentUser].contacts[i].kategori << " | "
                                     << setw(28) << left << users[currentUser].contacts[i].alamatKontak << " |\n";
                            }
                            cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
                            int index;
                            cout << "| Masukkan nomor kontak (1-" << users[currentUser].jumlahKontak << "): ";
                            cin >> index;
                            cout << "+------------------------------------------+\n";
                            if (index < 1 || index > users[currentUser].jumlahKontak) {
                                cout << "\n+------------------------------------------+\n";
                                cout << "|       Nomor kontak tidak valid!          |\n";
                                cout << "+------------------------------------------+\n";
                                break;
                            }
                            index--;
                            for (int i = index; i < users[currentUser].jumlahKontak - 1; i++) {
                                users[currentUser].contacts[i] = users[currentUser].contacts[i + 1];
                            }
                            users[currentUser].jumlahKontak--;
                            cout << "\n+------------------------------------------+\n";
                            cout << "|        Kontak berhasil dihapus!          |\n";
                            cout << "+------------------------------------------+\n";
                            break;
                        }
                        case 5: {
                            cout << "\n+------------------------------------------+\n";
                            cout << "| Terima kasih. Kembali ke home page.      |\n";
                            cout << "+------------------------------------------+\n";
                            sessionRunning = false;
                            break;
                        }
                        default: {
                            cout << "\n+------------------------------------------+\n";
                            cout << "| Pilihan tidak valid! Pilih 1-5.          |\n";
                            cout << "+------------------------------------------+\n";
                            break;
                        }
                    }
                }
                break;
            }
            case 3: {
                cout << "\n+------------------------------------------+\n";
                cout << "| Terima kasih telah menggunakan program.  |\n";
                cout << "| Sampai jumpa!                            |\n";
                cout << "+------------------------------------------+\n";
                programRunning = false;
                break;
            }
            default: {
                cout << "\n+------------------------------------------+\n";
                cout << "| Pilihan tidak valid! Pilih 1-3.          |\n";
                cout << "+------------------------------------------+\n";
                break;
            }
        }
    }
    return 0;
}