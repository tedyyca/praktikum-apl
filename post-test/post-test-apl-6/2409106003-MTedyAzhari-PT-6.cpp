#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_USERS = 100;
const int MAX_CONTACTS = 100;

struct Contact {  
    string namaKontak;    
    string telepon;       
    string kategori;      
    string alamatKontak;  
};

struct User {
    string nama;
    string nim;
    Contact contacts[MAX_CONTACTS]; 
    int jumlahKontak;
};

void tampilkanHeader(const string& judul);
void tampilkanHomepage();
void tampilkanMenu();
void tampilkanDaftarKontak(const User& user);
int registrasiUser(User users[], int userCount);
int loginUser(User users[], int userCount);
void tambahKontak(User& user);
void tampilkanTabelKontak(const User& user, const string& judul);
void perbaruiKontak(User& user);
void hapusKontak(User& user);


void urutkanKontakBerdasarkanNama(User& user);    
void urutkanKontakBerdasarkanTelepon(User& user);  
void urutkanKontakBerdasarkanKategori(User& user); 
void urutkanKontakBerdasarkanAlamat(User& user);   
void tampilkanMenuPengurutan();
void pengurutanKontak(User& user);

int cariKontakRekursif(const User* user, const string& nama, int index);

void tampilkanInfo(const string& pesan);
void tampilkanInfo(const string& pesan, const string& nama);
int hitungKontak(const User* user); 
int hitungKontak(const User* user, const string* kategori); 


int partisi(Contact arr[], int low, int high);
void quickSort(Contact arr[], int low, int high);

int main() {
    User users[MAX_USERS];
    User* pUsers = users; 
    int userCount = 0;
    bool programRunning = true;

    pUsers[0].nama = "MTedyAzhari";
    pUsers[0].nim = "2409106003";
    pUsers[0].jumlahKontak = 0;
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
                userCount = registrasiUser(pUsers, userCount);
                break;
            }
            case 2: {
                if (userCount == 0) {
                    tampilkanInfo("Belum ada pengguna terdaftar!");
                    break;
                }
                
                int currentUser = loginUser(pUsers, userCount);
                if (currentUser == -1) {
                    programRunning = false;
                    break;
                }
                
                User* currentUserPtr = &pUsers[currentUser]; 
                tampilkanInfo("Login berhasil! Selamat datang, ", currentUserPtr->nama);
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
                            tambahKontak(*currentUserPtr); 
                            break;
                        case 2:
                            if (currentUserPtr->jumlahKontak == 0) {
                                tampilkanInfo("Tidak ada kontak yang tersimpan.");
                                break;
                            }
                            tampilkanDaftarKontak(*currentUserPtr); 
                            break;
                        case 3:
                            perbaruiKontak(*currentUserPtr); 
                            break;
                        case 4:
                            hapusKontak(*currentUserPtr); 
                            break;
                        case 5:
                            pengurutanKontak(*currentUserPtr); 
                            break;
                        case 6: {
                            tampilkanInfo("Terima kasih. Kembali ke home page.");
                            sessionRunning = false;
                            break;
                        }
                        default: {
                            tampilkanInfo("Pilihan tidak valid! Pilih 1-6.");
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
    cout << "|  5   | Sorting Kontak                    |\n";
    cout << "|  6   | Homepage                          |\n";
    cout << "+------------------------------------------+\n";
    cout << "| Pilihan Anda: ";
}

void tampilkanDaftarKontak(const User& user) {
    tampilkanTabelKontak(user, "DAFTAR SEMUA KONTAK");
    
    const User* pUser = &user; 
    cout << "\n+------------------------------------------+\n";
    cout << "| Statistik Kontak:                       |\n";
    cout << "| Total kontak: " << setw(24) << left << hitungKontak(pUser) << "|\n";
    
    string kategoriKeluarga = "keluarga";
    string kategoriTeman = "teman";
    string kategoriBisnis = "bisnis";
    
    cout << "| Kontak keluarga: " << setw(21) << left << hitungKontak(pUser, &kategoriKeluarga) << "|\n";
    cout << "| Kontak teman: " << setw(23) << left << hitungKontak(pUser, &kategoriTeman) << "|\n";
    cout << "| Kontak bisnis: " << setw(22) << left << hitungKontak(pUser, &kategoriBisnis) << "|\n";
    cout << "+------------------------------------------+\n";
}

void tampilkanTabelKontak(const User& user, const string& judul) {
    tampilkanHeader(judul);
    cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
    cout << "| No  | " << setw(28) << left << "Nama" 
         << " | " << setw(18) << left << "Nomor Telepon" 
         << " | " << setw(18) << left << "Kategori" 
         << " | " << setw(28) << left << "Alamat" << " |\n";
    cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
    
    const Contact* pContacts = user.contacts;
    for (int i = 0; i < user.jumlahKontak; i++) {
        cout << "| " << setw(3) << right << (i + 1) << " | "
             << setw(28) << left << (pContacts + i)->namaKontak << " | "
             << setw(18) << left << (pContacts + i)->telepon << " | "
             << setw(18) << left << (pContacts + i)->kategori << " | "
             << setw(28) << left << (pContacts + i)->alamatKontak << " |\n";
    }
    cout << "+-----+--------------------------------+--------------------+--------------------+--------------------------------+\n";
}

int registrasiUser(User users[], int userCount) {
    cin.ignore();
    tampilkanHeader("REGISTER PENGGUNA BARU");
    cout << "| Nama: ";
    string newNama;
    getline(cin, newNama);

    bool nameExists = false;
    User* pUsers = users; 
    
    for (int i = 0; i < userCount; i++) {
        if ((pUsers + i)->nama == newNama) {
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

    User* newUser = &pUsers[userCount];
    newUser->nama = newNama;
    newUser->nim = newNim;
    newUser->jumlahKontak = 0;
    
    userCount++;
    tampilkanInfo("Pendaftaran berhasil!");
    return userCount;
}

int loginUser(User users[], int userCount) {
    string inputNama;
    string inputNim;
    int loginAttempts = 0;
    bool loggedIn = false;
    int currentUser = -1;
    User* pUsers = users; 

    cin.ignore();
    while (loginAttempts < 3 && !loggedIn) {
        tampilkanHeader("LOGIN");
        cout << "| Nama: ";
        getline(cin, inputNama);
        cout << "| NIM:  ";
        getline(cin, inputNim);
        cout << "+------------------------------------------+\n";
        
        for (int i = 0; i < userCount; i++) {
            if ((pUsers + i)->nama == inputNama && (pUsers + i)->nim == inputNim) {
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

void tambahKontak(User& user) {
    if (user.jumlahKontak >= MAX_CONTACTS) {
        tampilkanInfo("Kontak penuh! Hapus kontak dulu.");
        return;
    }
    
    cin.ignore();
    tampilkanHeader("TAMBAH KONTAK BARU");
     
    Contact* newContact = &user.contacts[user.jumlahKontak];
    
    cout << "| Nama: ";
    getline(cin, newContact->namaKontak);
    cout << "| Nomor Telepon: ";
    getline(cin, newContact->telepon);
    cout << "| Kategori (keluarga/teman/bisnis): ";
    getline(cin, newContact->kategori);
    cout << "| Alamat: ";
    getline(cin, newContact->alamatKontak);
    cout << "+------------------------------------------+\n";
    user.jumlahKontak++;
    tampilkanInfo("Kontak berhasil ditambahkan!");
}


void perbaruiKontak(User& user) {
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
    
    Contact* contactToUpdate = &user.contacts[index];
    
    cin.ignore();
    cout << "| Nama baru ('" << contactToUpdate->namaKontak << "'): ";
    string namaBaru;
    getline(cin, namaBaru);
    if (namaBaru != "") contactToUpdate->namaKontak = namaBaru;
    
    cout << "| Nomor telepon baru ('" << contactToUpdate->telepon << "'): ";
    string teleponBaru;
    getline(cin, teleponBaru);
    if (teleponBaru != "") contactToUpdate->telepon = teleponBaru;
    
    cout << "| Kategori baru ('" << contactToUpdate->kategori << "'): ";
    string kategoriBaru;
    getline(cin, kategoriBaru);
    if (kategoriBaru != "") contactToUpdate->kategori = kategoriBaru;
    
    cout << "| Alamat baru ('" << contactToUpdate->alamatKontak << "'): ";
    string alamatBaru;
    getline(cin, alamatBaru);
    if (alamatBaru != "") contactToUpdate->alamatKontak = alamatBaru;
    
    cout << "+------------------------------------------+\n";
    tampilkanInfo("Kontak berhasil diperbarui!");
}

void hapusKontak(User& user) {
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
    Contact* contacts = user.contacts;
    for (int i = index; i < user.jumlahKontak - 1; i++) {
        *(contacts + i) = *(contacts + i + 1);
    }
    user.jumlahKontak--;
    tampilkanInfo("Kontak berhasil dihapus!");
}

int cariKontakRekursif(const User* user, const string& nama, int index) {
    if (index >= user->jumlahKontak) {
        return -1; 
    }
    
    if (user->contacts[index].namaKontak == nama) {
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

int hitungKontak(const User* user) {
    return user->jumlahKontak;
}

int hitungKontak(const User* user, const string* kategori) {
    int count = 0;
    const Contact* contacts = user->contacts;
    
    for (int i = 0; i < user->jumlahKontak; i++) {
        if ((contacts + i)->kategori == *kategori) {
            count++;
        }
    }
    return count;
}


void urutkanKontakBerdasarkanNama(User& user) {
    Contact* kontak = user.contacts;
    int n = user.jumlahKontak;
    
    for (int i = 1; i < n; i++) {
        Contact kunci = kontak[i];
        int j = i - 1;
        
        
        while (j >= 0 && kontak[j].namaKontak > kunci.namaKontak) {
            kontak[j + 1] = kontak[j];
            j = j - 1;
        }
        kontak[j + 1] = kunci;
    }
}


void urutkanKontakBerdasarkanTelepon(User& user) {
    Contact* kontak = user.contacts;
    int n = user.jumlahKontak;
    
    for (int i = 0; i < n - 1; i++) {
        int indeksMaks = i;
        for (int j = i + 1; j < n; j++) {
           
            if (kontak[j].telepon > kontak[indeksMaks].telepon) {
                indeksMaks = j;
            }
        }
        
       
        if (indeksMaks != i) {
            Contact temp = kontak[i];
            kontak[i] = kontak[indeksMaks];
            kontak[indeksMaks] = temp;
        }
    }
}


void urutkanKontakBerdasarkanKategori(User& user) {
    Contact* kontak = user.contacts;
    int n = user.jumlahKontak;
    
    for (int i = 0; i < n - 1; i++) {
        bool ditukar = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (kontak[j].kategori > kontak[j + 1].kategori) {
                
                Contact temp = kontak[j];
                kontak[j] = kontak[j + 1];
                kontak[j + 1] = temp;
                ditukar = true;
            }
        }
        
        
        if (!ditukar) break;
    }
}


int partisi(Contact arr[], int low, int high) {
    string pivot = arr[high].alamatKontak;
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].alamatKontak <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quickSort(Contact arr[], int low, int high) {
    if (low < high) {
        int pi = partisi(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void urutkanKontakBerdasarkanAlamat(User& user) {
    Contact* kontak = user.contacts;
    int n = user.jumlahKontak;
    
    quickSort(kontak, 0, n - 1);
}

void tampilkanMenuPengurutan() {
    cout << "\n+------------------------------------------+\n";
    cout << "|             MENU SORTING                  |\n";
    cout << "+------------------------------------------+\n";
    cout << "|  No  |          Pilihan                  |\n";
    cout << "+------------------------------------------+\n";
    cout << "|  1   | Sorting berdasarkan Nama          |\n";
    cout << "|  2   | Sorting berdasarkan Telepon       |\n";
    cout << "|  3   | Sorting berdasarkan Kategori      |\n";
    cout << "|  4   | Sorting berdasarkan Alamat        |\n";
    cout << "|  5   | Menu Direktori Kontak             |\n";
    cout << "+------------------------------------------+\n";
    cout << "| Pilihan Anda: ";
}


void pengurutanKontak(User& user) {
    if (user.jumlahKontak == 0) {
        tampilkanInfo("Tidak ada kontak yang tersimpan.");
        return;
    }
    
    bool menuPengurutanBerjalan = true;
    
    while (menuPengurutanBerjalan) {
        tampilkanMenuPengurutan();
        
        int pilihanUrut;
        if (!(cin >> pilihanUrut)) {
            cin.clear();
            cin.ignore(10000, '\n');
            tampilkanInfo("Input tidak valid! Masukkan angka.");
            continue;
        }
        
        switch (pilihanUrut) {
            case 1:
                urutkanKontakBerdasarkanNama(user);
                tampilkanTabelKontak(user, "SORTING5 BERDASARKAN NAMA");
                tampilkanInfo("Kontak berhasil diurutkan berdasarkan nama!");
                break;
            case 2:
                urutkanKontakBerdasarkanTelepon(user);
                tampilkanTabelKontak(user, "SORTING BERDASARKAN TELEPON");
                tampilkanInfo("Kontak berhasil diurutkan berdasarkan nomor telepon!");
                break;
            case 3:
                urutkanKontakBerdasarkanKategori(user);
                tampilkanTabelKontak(user, "SORTING BERDASARKAN KATEGORI");
                tampilkanInfo("Kontak berhasil diurutkan berdasarkan kategori!");
                break;
            case 4:
                urutkanKontakBerdasarkanAlamat(user);
                tampilkanTabelKontak(user, "SORTING BERDASARKAN ALAMAT");
                tampilkanInfo("Kontak berhasil diurutkan berdasarkan alamat!");
                break;
            case 5:
                menuPengurutanBerjalan = false;
                break;
            default:
                tampilkanInfo("Pilihan tidak valid! Pilih 1-5.");
                break;
        }
    }
}