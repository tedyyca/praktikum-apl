#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CONTACTS = 100;

int main() {
    
    string daftarNama[MAX_CONTACTS];
    string daftarTelepon[MAX_CONTACTS];
    string daftarKategori[MAX_CONTACTS];
    string alamat[MAX_CONTACTS][1];
    int jumlahKontak = 0;

    cout << "\n===== MANAJEMEN DIREKTORI KONTAK =====\n";
    {
        string nama = "MTedyAzhari";
        string nim = "2409106003";
        string inputUsername;
        string inputPassword;
        int loginAttempts = 0;
        bool isLoggedIn = false;

        while (loginAttempts < 3 && !isLoggedIn) {
            cout << "\nLOGIN\n";
            cout << "Nama: ";
            cin >> inputUsername;
            cout << "NIM: ";
            cin >> inputPassword;
            
            if (inputUsername == nama && inputPassword == nim) {
                cout << "\nLogin berhasil! Selamat datang, " << nama << "!\n";
                isLoggedIn = true;
            } else {
                loginAttempts++;
                cout << "\nNama atau NIM salah! Percobaan ke-" << loginAttempts << " dari 3\n";
            }
        }
        
        if (!isLoggedIn) {
            cout << "\nAnda telah 3 kali gagal login. Program berhenti.\n";
            return 0;
        }
    }

    bool running = true;
    while (running) {
        cout << "\n===== MANAJEMEN DIREKTORI KONTAK =====\n";
        cout << "1. Tambah Kontak Baru\n";
        cout << "2. Tampilkan Semua Kontak\n";
        cout << "3. Perbarui Kontak\n";
        cout << "4. Hapus Kontak\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        
        int pilihan; 
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInput tidak valid! Silakan masukkan angka.\n";
            continue;
        }

        switch (pilihan) {
            case 1: {
                if (jumlahKontak >= MAX_CONTACTS) {
                    cout << "\nKontak sudah penuh! Hapus beberapa kontak terlebih dahulu.\n";
                    break;
                }
                cin.ignore();
                cout << "\n===== TAMBAH KONTAK BARU =====\n";
                cout << "Nama: ";
                getline(cin, daftarNama[jumlahKontak]);
                cout << "Nomor Telepon: ";
                getline(cin, daftarTelepon[jumlahKontak]);
                cout << "Kategori (keluarga/teman/bisnis/lainnya): ";
                getline(cin, daftarKategori[jumlahKontak]);
                cout << "Alamat: ";
                getline(cin, alamat[jumlahKontak][0]);
                jumlahKontak++;
                cout << "\nKontak berhasil ditambahkan!\n";
                break;
            }
            case 2: {
                if (jumlahKontak == 0) {
                    cout << "\nTidak ada kontak yang tersimpan.\n";
                    break;
                }
                cout << "\n===== DAFTAR SEMUA KONTAK =====\n";
                cout << "+-----+";
                for (int i = 0; i < 30; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 20; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 20; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 30; i++) cout << "-";
                cout << "+\n";
                cout << "| No  | " << setw(28) << left << "Nama" 
                     << " | " << setw(18) << left << "Nomor Telepon" 
                     << " | " << setw(18) << left << "Kategori" 
                     << " | " << setw(28) << left << "Alamat" << " |\n";
                cout << "+-----+";
                for (int i = 0; i < 30; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 20; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 20; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 30; i++) cout << "-";
                cout << "+\n";
                for (int i = 0; i < jumlahKontak; i++) {
                    cout << "| " << setw(3) << right << (i + 1) << " | "
                         << setw(28) << left << daftarNama[i] << " | "
                         << setw(18) << left << daftarTelepon[i] << " | "
                         << setw(18) << left << daftarKategori[i] << " | "
                         << setw(28) << left << alamat[i][0] << " |\n";
                }
                cout << "+-----+";
                for (int i = 0; i < 30; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 20; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 20; i++) cout << "-";
                cout << "+";
                for (int i = 0; i < 30; i++) cout << "-";
                cout << "+\n";
                break;
            }
            case 3: {
                if (jumlahKontak == 0) {
                    cout << "\nTidak ada kontak yang tersimpan.\n";
                    break;
                }
                int index; 
                cout << "\n===== PERBARUI KONTAK =====\n";
                cout << "Masukkan nomor kontak yang ingin diperbarui (1-" << jumlahKontak << "): ";
                cin >> index;
                if (index < 1 || index > jumlahKontak) {
                    cout << "\nNomor kontak tidak valid!\n";
                    break;
                }
                index--;
                cin.ignore();
                cout << "Nama baru (kosongkan jika tidak ingin mengubah '" << daftarNama[index] << "'): ";
                string namaBaru; 
                getline(cin, namaBaru);
                if (namaBaru != "") {
                    daftarNama[index] = namaBaru;
                }
                cout << "Nomor telepon baru (kosongkan jika tidak ingin mengubah '" << daftarTelepon[index] << "'): ";
                string teleponBaru; 
                getline(cin, teleponBaru);
                if (teleponBaru != "") {
                    daftarTelepon[index] = teleponBaru;
                }
                cout << "Kategori baru (kosongkan jika tidak ingin mengubah '" << daftarKategori[index] << "'): ";
                string kategoriBaru; 
                getline(cin, kategoriBaru);
                if (kategoriBaru != "") {
                    daftarKategori[index] = kategoriBaru;
                }
                cout << "Alamat baru (kosongkan jika tidak ingin mengubah '" << alamat[index][0] << "'): ";
                string alamatBaru; 
                getline(cin, alamatBaru);
                if (alamatBaru != "") {
                    alamat[index][0] = alamatBaru;
                }
                cout << "\nKontak berhasil diperbarui!\n";
                break;
            }
            case 4: {
                if (jumlahKontak == 0) {
                    cout << "\nTidak ada kontak yang tersimpan.\n";
                    break;
                }
                int index; 
                cout << "\n===== HAPUS KONTAK =====\n";
                cout << "Masukkan nomor kontak yang ingin dihapus (1-" << jumlahKontak << "): ";
                cin >> index;
                if (index < 1 || index > jumlahKontak) {
                    cout << "\nNomor kontak tidak valid!\n";
                    break;
                }
                index--;
                for (int i = index; i < jumlahKontak - 1; i++) {
                    daftarNama[i] = daftarNama[i + 1];
                    daftarTelepon[i] = daftarTelepon[i + 1];
                    daftarKategori[i] = daftarKategori[i + 1];
                    alamat[i][0] = alamat[i + 1][0];
                }
                jumlahKontak--;
                cout << "\nKontak berhasil dihapus!\n";
                break;
            }
            case 5: {
                cout << "\nTerima kasih telah menggunakan program ini. Sampai jumpa!\n";
                running = false;
                break;
            }
            default: {
                cout << "\nPilihan tidak valid! Silakan pilih antara 1-5.\n";
                break;
            }
        }
    }

    return 0;
}