#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip> 
#include <cstdlib>
#include <cctype>

using namespace std;

struct Penerbangan {
    string nomor; 
    string tujuan;
    string waktu;
};

struct Penumpang {
    int id;
    string nama;
    Penumpang* next;
};

Penumpang* head = nullptr; 
const int MAX = 100; 
Penerbangan penerbangan[MAX];
int jumlahPenerbangan = 0;

stack<Penerbangan> historyPenerbangan;
queue<Penumpang*> historyPenumpang;

bool nomorUnik(const string& nomor) {
    for (int i = 0; i < jumlahPenerbangan; ++i) {
        if (penerbangan[i].nomor == nomor) {
            return false;
        }
    }
    return true;
}

bool waktuInput(const string& waktu) {
    if (waktu.size() != 5 || waktu[2] != ':') {
        return false;
    }
    if (!isdigit(waktu[0]) || !isdigit(waktu[1]) || !isdigit(waktu[3]) || !isdigit(waktu[4])) {
        return false;
    }
    int jam = stoi(waktu.substr(0, 2));
    int menit = stoi(waktu.substr(3, 2));
    return (jam >= 0 && jam <= 23) && (menit >= 0 && menit <= 59);
}

bool waktuUnik(const string& waktu) {
    for (int i = 0; i < jumlahPenerbangan; ++i) {
        if (penerbangan[i].waktu == waktu) {
            return false;
        }
    }
    return true;
}

void tambahPenerbangan(string nomor, string tujuan, string waktu) {
    if (jumlahPenerbangan < MAX) {
        if (!nomorUnik(nomor)) {
            cout << "Nomor penerbangan sudah ada! Masukkan nomor yang unik.\n";
            return;
        }
        
        if (!waktuInput(waktu)) {
            cout << "Waktu harus dalam format HH:MM dengan jam antara 00-23 dan menit antara 00-59.\n";
            return;
        }

        if (!waktuUnik(waktu)) {
            cout << "Waktu penerbangan sudah ada! Masukkan waktu yang unik.\n";
            return;
        }

        penerbangan[jumlahPenerbangan] = {nomor, tujuan, waktu};
        historyPenerbangan.push(penerbangan[jumlahPenerbangan]);
        jumlahPenerbangan++;
        cout << "Data penerbangan berhasil ditambahkan!\n";
    } else {
        cout << "Kapasitas penuh. Tidak dapat menambahkan data penerbangan.\n";
    }
}


void tampilkanPenerbangan() {
    cout << left << "| " << setw(15) << "Nomor"
         << "| " << setw(20) << "Tujuan"
         << "| " << setw(15) << "Waktu" << "|\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < jumlahPenerbangan; i++) {
        cout << "| " << setw(15) << penerbangan[i].nomor
             << "| " << setw(20) << penerbangan[i].tujuan
             << "| " << setw(15) << penerbangan[i].waktu << "|\n";
    }
}

void updatePenerbangan(string nomor) {
    for (int i = 0; i < jumlahPenerbangan; i++) {
        if (penerbangan[i].nomor == nomor) {
            cout << "Masukkan tujuan baru: ";
            cin.ignore();
            getline(cin, penerbangan[i].tujuan);

            string waktuBaru;
            cout << "Masukkan waktu baru: ";
            getline(cin, waktuBaru);
            
            if (!waktuInput(waktuBaru)) {
                cout << "Waktu tidak valid. Harus dalam format hh:mm.\n";
                return;
            }
            
            penerbangan[i].waktu = waktuBaru;
            cout << "Data penerbangan berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Penerbangan dengan nomor tersebut tidak ditemukan.\n";
}

void hapusPenerbangan(string nomor) {
    for (int i = 0; i < jumlahPenerbangan; i++) {
        if (penerbangan[i].nomor == nomor) {
            for (int j = i; j < jumlahPenerbangan - 1; j++) {
                penerbangan[j] = penerbangan[j + 1];
            }
            jumlahPenerbangan--;
            cout << "Data penerbangan berhasil dihapus!\n";
            return;
        }
    }
    cout << "Penerbangan dengan nomor tersebut tidak ditemukan.\n";
}

void tampilkanHistoryPenerbangan() {
    if (historyPenerbangan.empty()) {
        cout << "Tidak ada data penerbangan dalam history.\n";
        return;
    }
    
    cout << "History Penerbangan:\n";
    cout << left << "| " << setw(15) << "Nomor"
         << "| " << setw(20) << "Tujuan"
         << "| " << setw(15) << "Waktu" << "|\n";
    cout << "--------------------------------------------------------------\n";
    stack<Penerbangan> tempStack = historyPenerbangan;
    while (!tempStack.empty()) {
        Penerbangan topPenerbangan = tempStack.top();
        cout << "| " << setw(15) << topPenerbangan.nomor
             << "| " << setw(20) << topPenerbangan.tujuan
             << "| " << setw(15) << topPenerbangan.waktu << "|\n";
        tempStack.pop();
    }
}

bool idUnik(int id) {
    Penumpang* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

void tambahPenumpang(Penumpang*& head, int id, string nama) {
    if (cin.fail() || id <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ID penumpang harus berupa angka positif.\n";
        return;
    }

    if (!idUnik(id)) {
        cout << "ID penumpang sudah terdaftar! Masukkan ID yang unik.\n";
        return;
    }

    Penumpang* newPenumpang = new Penumpang{id, nama, head};
    historyPenumpang.push(newPenumpang);
    head = newPenumpang;
    cout << "Penumpang berhasil ditambahkan!\n";
}

void tampilkanPenumpang(Penumpang* head) {
    cout << left << "| " << setw(10) << "ID" 
         << "| " << setw(20) << "Nama" << "|\n";
    cout << "---------------------------------------\n";
    while (head != nullptr) {
        cout << "| " << setw(10) << head->id 
             << "| " << setw(20) << head->nama << "|\n";
        head = head->next;
    }
}

void hapusPenumpang(Penumpang*& head, int id) {
    Penumpang* temp = head;
    Penumpang* prev = nullptr;
    
    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Penumpang dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Penumpang berhasil dihapus!\n";
}
void tampilkanHistoryPenumpang() {
    if (historyPenumpang.empty()) {
        cout << "Tidak ada data penumpang dalam history.\n";
        return;
    }

    cout << "History Penumpang:\n";
    cout << left << "| " << setw(10) << "ID" 
         << "| " << setw(20) << "Nama" << "|\n";
    cout << "---------------------------------------\n";
    queue<Penumpang*> tempQueue = historyPenumpang;
    while (!tempQueue.empty()) {
        Penumpang* frontPenumpang = tempQueue.front();
        if (frontPenumpang != nullptr) {
            cout << "| " << setw(10) << frontPenumpang->id 
                 << "| " << setw(20) << frontPenumpang->nama << "|\n";
        } else {
            cout << "| " << setw(10) << "kosong" 
                 << "| " << setw(20) << "kosong" << "|\n";
        }

        tempQueue.pop(); 
    }
}

// sorting
void merge(Penerbangan arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Penerbangan L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].waktu <= R[j].waktu) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Penerbangan arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void tampilkanPenerbanganWaktu() {
    Penerbangan temp[MAX];
    for (int i = 0; i < jumlahPenerbangan; i++) {
        temp[i] = penerbangan[i];
    }
    mergeSort(temp, 0, jumlahPenerbangan - 1);
    
    cout << "Daftar Penerbangan (Diurutkan Berdasarkan Waktu):\n";
    for (int i = 0; i < jumlahPenerbangan; i++) {
        cout << "Nomor: " << temp[i].nomor
             << ", Tujuan: " << temp[i].tujuan
             << ", Waktu: " << temp[i].waktu << endl;
    }
}

int partition(Penerbangan arr[], int low, int high) {
    string pivot = arr[high].tujuan;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].tujuan > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(Penerbangan arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void tampilkanPenerbanganTujuan() {
    Penerbangan temp[MAX];
    for (int i = 0; i < jumlahPenerbangan; i++) {
        temp[i] = penerbangan[i];
    }
    quickSort(temp, 0, jumlahPenerbangan - 1);
    
    cout << "Daftar Penerbangan (Diurutkan Berdasarkan Tujuan Descending):\n";
    for (int i = 0; i < jumlahPenerbangan; i++) {
        cout << "Nomor: " << temp[i].nomor
             << ", Tujuan: " << temp[i].tujuan
             << ", Waktu: " << temp[i].waktu << endl;
    }
}

// cari tujuan penerbangan
int fibonacciSearch(Penerbangan arr[], int n, string x) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm1 + fibMMm2;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm1 + fibMMm2;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        if (arr[i].tujuan < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i].tujuan > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1].tujuan == x) {
        return offset + 1;
    }

    return -1;
}

// cari waktu penerbangan
int jumpSearch(Penerbangan arr[], int n, string x) {
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1].waktu < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (arr[prev].waktu < x) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (arr[prev].waktu == x)
        return prev;

    return -1;
}

// cari penumpang
bool boyerMooreSearch(string text, string pattern) {
    int m = pattern.length();
    int n = text.length();
    if (m > n) return false;

    vector<int> badChar(256, -1);  
    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i; 
    }

    int s = 0;  
    while (s <= n - m) {
        int j = m - 1;
        
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            return true; 
        } else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }

    return false;  
}

// fungsi menu search
void searchMenu() {
    int subChoice;
    cout << "\n--- Menu Pencarian ---\n";
    cout << "1. Pencarian Tujuan (Fibonacci Search)\n";
    cout << "2. Pencarian Waktu (Jump Search)\n";
    cout << "3. Pencarian Nama Penumpang (Boyer-Moore)\n";
    cout << "4. Kembali\n";
    cout << "Pilihan: ";
    cin >> subChoice;

    switch (subChoice) {
        case 1: {
            string tujuan;
            cout << "Masukkan tujuan penerbangan yang dicari: ";
            cin.ignore();
            getline(cin, tujuan);
            bool found = false;
            for (int i = 0; i < jumlahPenerbangan; i++) {
                if (penerbangan[i].tujuan == tujuan) {
                    if (!found) {
                        cout << "Penerbangan dengan tujuan '" << tujuan << "' ditemukan:\n";
                        found = true;
                    }
                    cout << "Nomor Penerbangan: " << penerbangan[i].nomor << endl;
                    cout << "Tujuan: " << penerbangan[i].tujuan << endl;
                    cout << "Waktu: " << penerbangan[i].waktu << endl;
                    cout << "----------------------\n";
                }
            }
            if (!found) {
                cout << "Tujuan tidak ditemukan.\n";
            }
            break;
        }
        case 2: {
            string waktu;
            cout << "Masukkan waktu penerbangan yang dicari: ";
            cin.ignore();
            getline(cin, waktu);
            bool found = false;
            for (int i = 0; i < jumlahPenerbangan; i++) {
                if (penerbangan[i].waktu == waktu) {
                    if (!found) {
                        cout << "Penerbangan dengan waktu '" << waktu << "' ditemukan:\n";
                        found = true;
                    }
                    cout << "Nomor Penerbangan: " << penerbangan[i].nomor << endl;
                    cout << "Tujuan: " << penerbangan[i].tujuan << endl;
                    cout << "Waktu: " << penerbangan[i].waktu << endl;
                    cout << "----------------------\n";
                }
            }
            if (!found) {
                cout << "Waktu tidak ditemukan.\n";
            }
            break;
        }
        case 3: {
            string nama;
            cout << "Masukkan nama penumpang yang dicari: ";
            cin.ignore();
            getline(cin, nama);
            bool found = false;
            Penumpang* temp = head;
            while (temp != nullptr) {
                if (temp->nama == nama) {
                    if (!found) {
                        cout << "Penumpang dengan nama '" << nama << "' ditemukan:\n";
                        found = true;
                    }
                    cout << "ID: " << temp->id << ", Nama: " << temp->nama << endl;
                    cout << "----------------------\n";
                }
                temp = temp->next;
            }
            if (!found) {
                cout << "Penumpang dengan nama tersebut tidak ditemukan.\n";
            }
            break;
        }

        case 4:
            return;
        default:
            cout << "Pilihan tidak valid.\n";
    }
}


// Program utama
int main() {
    int pilihan, id;
    string nomor, tujuan, waktu, nama;

    do {
        cout << "\n--- Sistem Penjadwalan Penerbangan ---\n";
        cout << "1. Tambah Penerbangan\n";
        cout << "2. Tampilkan Penerbangan\n";
        cout << "3. Update Penerbangan\n";
        cout << "4. Hapus Penerbangan\n";
        cout << "5. Tampilkan History Penerbangan\n";
        cout << "6. Tambah Penumpang\n";
        cout << "7. Tampilkan Penumpang\n";
        cout << "8. Hapus Penumpang\n";
        cout << "9. Tampilkan History Penumpang\n";
        cout << "10. Tampilkan Penerbangan Berdasarkan Waktu (Ascending-Merge Sort) \n";
        cout << "11. Tampilkan Penerbangan Berdasarkan Tujuan (Descending-Quick Sort)\n";
        cout << "12. Searcing\n";
        cout << "13. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                cout << "Nomor penerbangan: ";
                cin >> nomor;
                cin.ignore();
                cout << "Tujuan: ";
                getline(cin, tujuan);
                cout << "Waktu keberangkatan: ";
                getline(cin, waktu);
                tambahPenerbangan(nomor, tujuan, waktu);
                break;
            case 2:
                system("cls");
                tampilkanPenerbangan();
                break;
            case 3:
                system("cls");
                tampilkanPenerbangan();
                cout << "Masukkan nomor penerbangan untuk di-update: ";
                cin >> nomor;
                updatePenerbangan(nomor);
                break;
            case 4:
                system("cls");
                tampilkanPenerbangan();
                cout << "Masukkan nomor penerbangan untuk dihapus: ";
                cin >> nomor;
                hapusPenerbangan(nomor);
                break;
            case 5:
                system("cls");
                tampilkanHistoryPenerbangan();
                break;
            case 6:
                system("cls");
                cout << "ID penumpang: ";
                cin >> id;
                cin.ignore();
                cout << "Nama penumpang: ";
                getline(cin, nama);
                tambahPenumpang(head, id, nama);
                break;
            case 7:
                system("cls");
                tampilkanPenumpang(head);
                break;
            case 8:
                system("cls");
                tampilkanPenumpang(head);
                cout << "Masukkan ID penumpang untuk dihapus: ";
                cin >> id;
                hapusPenumpang(head, id);
                break;
            case 9:
                system("cls");
                tampilkanHistoryPenumpang();
                break;
            case 10:
                system("cls");
                tampilkanPenerbanganWaktu();
                break;
            case 11:
                system("cls");
                tampilkanPenerbanganTujuan();
                break;
            case 12:
                system("cls");
                searchMenu();
                break;
            case 13:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 13);

    return 0;
}
