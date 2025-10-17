#include <iostream>  // Untuk input dan output
#include <cstdlib>   // Untuk fungsi rand()
#include <ctime>     // Untuk waktu acak
#include <string>    // Untuk string

using namespace std;

void tampilkanPapan(char papan[3][3]);  // Fungsi untuk menampilkan papan
bool cekMenang(char papan[3][3], char pemain);  // Fungsi untuk cek pemenang
void komputerGerak(char papan[3][3]);  // Fungsi untuk gerak komputer

int main() {
    srand(time(0));  // Seed untuk angka acak
    
    char papan[3][3] = {  // Inisialisasi papan kosong
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    
    char pemain = 'X';  // Pemain adalah 'X'
    char komputer = 'O';
    int posisi;
    char mainLagi = 'y';
    int skorPemain = 0;
    int skorKomputer = 0;
    int skorSeri = 0;
    
    cout << "Selamat datang di Game Tic-Tac-Toe!" << endl;
    cout << "Anda adalah 'X', komputer adalah 'O'." << endl;
    cout << "Pilih posisi 1-9 untuk menempatkan 'X'." << endl;
    
    while (mainLagi == 'y' || mainLagi == 'Y') {  // Loop untuk bermain berkali-kali
        // Reset papan untuk game baru
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                papan[i][j] = '1' + (i*3 + j);  // Kembalikan ke 1-9
            }
        }
        
        bool gameBerjalan = true;
        int giliran = 0;  // 0 untuk pemain, 1 untuk komputer
        
        while (gameBerjalan) {
            tampilkanPapan(papan);  // Tampilkan papan saat ini
            
            if (giliran % 2 == 0) {  // Giliran pemain
                cout << "Giliran Anda (pilih 1-9): ";
                cin >> posisi;
                
                if (posisi >= 1 && posisi <= 9) {
                    int baris = (posisi - 1) / 3;
                    int kolom = (posisi - 1) % 3;
                    
                    if (papan[baris][kolom] != 'X' && papan[baris][kolom] != 'O') {
                        papan[baris][kolom] = pemain;  // Tempatkan 'X'
                    } else {
                        cout << "Posisi sudah diambil! Coba lagi." << endl;
                        continue;  // Lewati giliran jika posisi salah
                    }
                } else {
                    cout << "Posisi tidak valid! Masukkan 1-9." << endl;
                    continue;
                }
            } else {  // Giliran komputer
                cout << "Giliran komputer..." << endl;
                komputerGerak(papan);  // Komputer memilih posisi
            }
            
            giliran++;  // Ganti giliran
            
            if (cekMenang(papan, pemain)) {
                tampilkanPapan(papan);
                cout << "Selamat! Anda menang." << endl;
                skorPemain++;
                gameBerjalan = false;
            } else if (cekMenang(papan, komputer)) {
                tampilkanPapan(papan);
                cout << "Komputer menang! Anda kalah." << endl;
                skorKomputer++;
                gameBerjalan = false;
            } else if (giliran >= 9) {  // Papan penuh
                tampilkanPapan(papan);
                cout << "Seri!" << endl;
                skorSeri++;
                gameBerjalan = false;
            }
        }
        
        // Tampilkan skor
        cout << "\nSkor: Anda (" << skorPemain << ") - Komputer (" << skorKomputer << ") - Seri (" << skorSeri << ")" << endl;
        cout << "Ingin main lagi? (y/n): ";
        cin >> mainLagi;
    }
    
    cout << "Terima kasih telah bermain! Sampai jumpa." << endl;
    return 0;
}

// Fungsi untuk menampilkan papan
void tampilkanPapan(char papan[3][3]) {
    cout << endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << " " << papan[i][j] << " ";
            if(j < 2) cout << "|";
        }
        cout << endl;
        if(i < 2) cout << "---+---+---" << endl;
    }
    cout << endl;
}

// Fungsi untuk cek pemenang
bool cekMenang(char papan[3][3], char pemain) {
    // Cek baris
    for(int i = 0; i < 3; i++) {
        if(papan[i][0] == pemain && papan[i][1] == pemain && papan[i][2] == pemain) return true;
    }
    // Cek kolom
    for(int i = 0; i < 3; i++) {
        if(papan[0][i] == pemain && papan[1][i] == pemain && papan[2][i] == pemain) return true;
    }
    // Cek diagonal
    if(papan[0][0] == pemain && papan[1][1] == pemain && papan[2][2] == pemain) return true;
    if(papan[0][2] == pemain && papan[1][1] == pemain && papan[2][0] == pemain) return true;
    return false;
}

// Fungsi untuk gerak komputer (AI sederhana: pilih posisi kosong secara acak)
void komputerGerak(char papan[3][3]) {
    int baris, kolom;
    do {
        baris = rand() % 3;
        kolom = rand() % 3;
    } while (papan[baris][kolom] == 'X' || papan[baris][kolom] == 'O');  // Cari posisi kosong
    papan[baris][kolom] = 'O';  // Tempatkan 'O'
}
