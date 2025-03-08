#include <iostream>
using namespace std;

int main() {
    // Inisialisasi variabel counter
    int surya= 1;
    
    // Perulangan while yang akan berjalan selama counter <= 5
    while (surya <= 5) {
        cout << "Surya bungkus ke-" << surya << endl;
        
        // Increment counter
        surya++;
    }
    
    cout << "Surya selesai!" << endl;
    
    return 0;
}