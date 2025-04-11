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


void tampilkanHeader(const string& judul);
void tampilkanHomepage();
void tampilkanMenu();
void tampilkanDaftarKontak(const Users& user);
int registrasiUser(Users users[], int userCount);
int loginUser(Users users[], int userCount);
void tambahKontak(Users& user);
void tampilkanTabelKontak(const Users& user, const string& judul);
void perbaruiKontak(Users& user);
void hapusKontak(Users& user);


int cariKontakRekursif(const Users& user, const string& nama, int index);


void tampilkanInfo(const string& pesan);
void tampilkanInfo(const string& pesan, const string& nama);
int hitungKontak(const Users& user); 
int hitungKontak(const Users& user, const string& kategori); 

int main() {
    Users users[MAX_USERS];
    int userCount = 0;
    bool programRunning = true;

    
    users[0].nama = "MTedyAzhari";
    users[0].nim = "2409106003";
    users[0].jumlahKontak = 0;
    userCount = 1;

    while (programRunning) {
        tampilkanHomepage();
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            tampilkanInfo("Input tidak valid! Masukkan angka.");
            continue;
        }

        switch (choice) {
            case 1: {
                if (userCount >= MAX_USERS) {
                    tampilkanInfo("User sudah penuh!");
                    break;
                }
                userCount = registrasiUser(users, userCount);
                break;
            }
            case 2: {
                if (userCount == 0) {
                    tampilkanInfo("Belum ada pengguna terdaftar!");
                    break;
                }
                
                int currentUser = loginUser(users, userCount);
                if (currentUser == -1) {
                    programRunning = false;
                    break;
                }
                
                tampilkanInfo("Login berhasil! Selamat datang, ", users[currentUser].nama);
                bool sessionRunning = true;

                while (sessionRunning) {
                    tampilkanMenu();
                    
                    int menuChoice;
                    if (!(cin >> menuChoice)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        tampilkanInfo("Input tidak valid! Masukkan angka.");
                        continue;
                    }

                    switch (menuChoice) {
                        case 1:
                            tambahKontak(users[currentUser]);
                            break;
                        case 2:
                            if (users[currentUser].jumlahKontak == 0) {
                                tampilkanInfo("Tidak ada kontak yang tersimpan.");
                                break;
                            }
                            tampilkanDaftarKontak(users[currentUser]);
                            break;
                        case 3:
                            perbaruiKontak(users[currentUser]);
                            break;
                        case 4:
                            hapusKontak(users[currentUser]);
                            break;
                        case 5: {
                            tampilkanInfo("Terima kasih. Kembali ke home page.");
                            sessionRunning = false;
                            break;
                        }
                        default: {
                            tampilkanInfo("Pilihan tidak valid! Pilih 1-5.");
                            break;
                        }
                    }
                }
                break;
            }
            case 3: {
                tampilkanInfo("Terima kasih telah menggunakan program.\nSampai jumpa!");
                programRunning = false;
                break;
            }
            default: {
                tampilkanInfo("Pilihan tidak valid! Pilih 1-3.");
                break;
            }
        }
    }
    return 0;
}


void tampilkanHeader(const string& judul) {
    cout << "\n+------------------------------------------+\n";
    cout << "|      " << setw(36) << left << judul << "|\n";
    cout << "+------------------------------------------+\n";
}

void tampilkanHomepage() {
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
}

void tampilkanMenu() {
    cout << "\n+------------------------------------------+\n";
    cout << "|           MENU DIREKTORI KONTAK          |\n";
    cout << "+------------------------------------------+\n";
    cout << "|  No  |          Pilihan                  |\n";
    cout << "+------------------------------------------+\n";
    cout << "|  1   | Tambah Kontak Baru                |\n";
    cout << "|  2   | Tampilkan Semua Kontak            |\n";
    cout << "|  3   | Perbarui Kontak                   |\n";
    cout << "|  4   | Hapus Kontak                      |\n";
    cout << "|  5   | Homepage                           |\n";
    cout << "+------------------------------------------+\n";
    cout << "| Pilihan Anda: ";
}

void tampilkanDaftarKontak(const Users& user) {
    tampilkanTabelKontak(user, "DAFTAR SEMUA KONTAK");
    
    
    cout << "\n+------------------------------------------+\n";
    cout << "| Statistik Kontak:                       |\n";
    cout << "| Total kontak: " << setw(24) << left << hitungKontak(user) << "|\n";
    cout << "| Kontak keluarga: " << setw(21) << left << hitungKontak(user, "keluarga") << "|\n";
    cout << "| Kontak teman: " << setw(23) << left << hitungKontak(user, "teman") << "|\n";
    cout << "| Kontak bisnis: " << setw(22) << left << hitungKontak(user, "bisnis") << "|\n";
    cout << "+------------------------------------------+\n";
}

void tampilkanTabelKontak(const Users& user, const string& judul) {
    tampilkanHeader(judul);
    cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
    cout << "| No  | " << setw(28) << left << "Nama" 
         << " | " << setw(18) << left << "Nomor Telepon" 
         << " | " << setw(18) << left << "Kategori" 
         << " | " << setw(28) << left << "Alamat" << " |\n";
    cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
    for (int i = 0; i < user.jumlahKontak; i++) {
        cout << "| " << setw(3) << right << (i + 1) << " | "
             << setw(28) << left << user.contacts[i].namaKontak << " | "
             << setw(18) << left << user.contacts[i].telepon << " | "
             << setw(18) << left << user.contacts[i].kategori << " | "
             << setw(28) << left << user.contacts[i].alamatKontak << " |\n";
    }
    cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
}


int registrasiUser(Users users[], int userCount) {
    cin.ignore();
    tampilkanHeader("REGISTER PENGGUNA BARU");
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
        tampilkanInfo("Nama sudah terdaftar! Gunakan nama lain.");
        return userCount;
    }

    cout << "| NIM: ";
    string newNim;
    getline(cin, newNim);

    users[userCount].nama = newNama;
    users[userCount].nim = newNim;
    users[userCount].jumlahKontak = 0;
    userCount++;
    tampilkanInfo("Pendaftaran berhasil!");
    return userCount;
}

int loginUser(Users users[], int userCount) {
    string inputNama;
    string inputNim;
    int loginAttempts = 0;
    bool loggedIn = false;
    int currentUser = -1;

    cin.ignore();
    while (loginAttempts < 3 && !loggedIn) {
        tampilkanHeader("LOGIN");
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
        tampilkanInfo("Anda telah 3 kali gagal login.\nProgram berhenti.");
        return -1;
    }
    
    return currentUser;
}

void tambahKontak(Users& user) {
    if (user.jumlahKontak >= MAX_CONTACTS) {
        tampilkanInfo("Kontak penuh! Hapus kontak dulu.");
        return;
    }
    
    cin.ignore();
    tampilkanHeader("TAMBAH KONTAK BARU");
    cout << "| Nama: ";
    getline(cin, user.contacts[user.jumlahKontak].namaKontak);
    cout << "| Nomor Telepon: ";
    getline(cin, user.contacts[user.jumlahKontak].telepon);
    cout << "| Kategori (keluarga/teman/bisnis): ";
    getline(cin, user.contacts[user.jumlahKontak].kategori);
    cout << "| Alamat: ";
    getline(cin, user.contacts[user.jumlahKontak].alamatKontak);
    cout << "+------------------------------------------+\n";
    user.jumlahKontak++;
    tampilkanInfo("Kontak berhasil ditambahkan!");
}

void perbaruiKontak(Users& user) {
    if (user.jumlahKontak == 0) {
        tampilkanInfo("Tidak ada kontak yang tersimpan.");
        return;
    }
    
    tampilkanHeader("PERBARUI KONTAK");
    cout << "| Jumlah kontak saat ini: " << setw(20) << left << user.jumlahKontak << "|\n";
    tampilkanTabelKontak(user, "PERBARUI KONTAK");
    
    int index;
    cout << "| Masukkan nomor kontak (1-" << user.jumlahKontak << "): ";
    cin >> index;
    cout << "+------------------------------------------+\n";
    
    if (index < 1 || index > user.jumlahKontak) {
        tampilkanInfo("Nomor kontak tidak valid!");
        return;
    }
    
    index--;
    cin.ignore();
    cout << "| Nama baru ('" << user.contacts[index].namaKontak << "'): ";
    string namaBaru;
    getline(cin, namaBaru);
    if (namaBaru != "") user.contacts[index].namaKontak = namaBaru;
    
    cout << "| Nomor telepon baru ('" << user.contacts[index].telepon << "'): ";
    string teleponBaru;
    getline(cin, teleponBaru);
    if (teleponBaru != "") user.contacts[index].telepon = teleponBaru;
    
    cout << "| Kategori baru ('" << user.contacts[index].kategori << "'): ";
    string kategoriBaru;
    getline(cin, kategoriBaru);
    if (kategoriBaru != "") user.contacts[index].kategori = kategoriBaru;
    
    cout << "| Alamat baru ('" << user.contacts[index].alamatKontak << "'): ";
    string alamatBaru;
    getline(cin, alamatBaru);
    if (alamatBaru != "") user.contacts[index].alamatKontak = alamatBaru;
    
    cout << "+------------------------------------------+\n";
    tampilkanInfo("Kontak berhasil diperbarui!");
}

void hapusKontak(Users& user) {
    if (user.jumlahKontak == 0) {
        tampilkanInfo("Tidak ada kontak yang tersimpan.");
        return;
    }
    
    tampilkanHeader("HAPUS KONTAK");
    cout << "| Jumlah kontak saat ini: " << setw(20) << left << user.jumlahKontak << "|\n";
    tampilkanTabelKontak(user, "HAPUS KONTAK");
    
    int index;
    cout << "| Masukkan nomor kontak (1-" << user.jumlahKontak << "): ";
    cin >> index;
    cout << "+------------------------------------------+\n";
    
    if (index < 1 || index > user.jumlahKontak) {
        tampilkanInfo("Nomor kontak tidak valid!");
        return;
    }
    
    index--;
    for (int i = index; i < user.jumlahKontak - 1; i++) {
        user.contacts[i] = user.contacts[i + 1];
    }
    user.jumlahKontak--;
    tampilkanInfo("Kontak berhasil dihapus!");
}


int cariKontakRekursif(const Users& user, const string& nama, int index) {
    
    if (index >= user.jumlahKontak) {
        return -1; 
    }
    
   
    if (user.contacts[index].namaKontak == nama) {
        return index;
    }
    
    
    return cariKontakRekursif(user, nama, index + 1);
}


void tampilkanInfo(const string& pesan) {
    cout << "\n+------------------------------------------+\n";
    cout << "| " << setw(40) << left << pesan << " |\n";
    cout << "+------------------------------------------+\n";
}

void tampilkanInfo(const string& pesan, const string& nama) {
    cout << "\n+------------------------------------------+\n";
    cout << "| " << pesan << setw(10) << left << nama << "|\n";
    cout << "+------------------------------------------+\n";
}

int hitungKontak(const Users& user) {
    return user.jumlahKontak;

}int hitungKontak(const Users& user, const string& kategori) {
    int count = 0;
    for (int i = 0; i < user.jumlahKontak; i++) {
        if (user.contacts[i].kategori == kategori) {
            count++;
        }
    }
    return count;
}