#include <iostream>
using namespace std;


void tukarNilai(int *a, int *b) {
  int c = *a;
    *a = *b;
    *b = c;
}
int main() {
    int angka1 = 2;
    int angka2 = 3;
    
    cout << "Nilai sebelum penukaran:" << endl;
    cout << "angka1 = " << angka1 << endl;
    cout << "angka2 = " << angka2 << endl;
    
    tukarNilai(&angka1, &angka2);

    cout << "\nNilai setelah penukaran:" << endl;
    cout << "angka1 = " << angka1 << endl;
    cout << "angka2 = " << angka2 << endl;
    
    return 0;
}