#include <iostream>
#include <string>
using namespace std;

// Constants for array sizes
const int MAX_PEMAKAMAN = 100;
const int MAX_LAHAN = 100;
const int MAX_DESAIN = 50;
const int MAX_PERMINTAAN = 100;

// ==================== STRUCTS ====================
// Struct for Burial Data
struct DataPemakaman {
    string namaJenazah;
    string tanggalLahir;
    string tanggalKematian;
    string lokasi;
    string penanggungJawab;
    bool statusTerisi;
};

// Struct for Land/Plot
struct Lahan {
    string kodeBlok;
    bool statusTerisi;
    string agama;
};

// Struct for Tomb Design
struct DesainMakam {
    string kodeDesain;
    string namaDesain;
    string deskripsi;
};

// Node for Cleaning Request (keeping this as linked list)
struct NodePermintaan {
    string namaPemohon;
    string lokasiMakam;
    string catatan;
    NodePermintaan* next;
};

// Struct to manage Cleaning Requests list
struct PermintaanList {
    NodePermintaan* head;
    int count;
};

// ==================== GLOBAL VARIABLES & ARRAYS ====================
// Arrays to store data
DataPemakaman dataPemakaman[MAX_PEMAKAMAN];
int jumlahPemakaman = 0;

Lahan dataLahan[MAX_LAHAN];
int jumlahLahan = 0;

DesainMakam katalogDesain[MAX_DESAIN];
int jumlahDesain = 0;

// Linked list for cleaning requests
PermintaanList permintaanPembersihan;

// ==================== FUNCTION PROTOTYPES ====================
void inisialisasiPermintaanPembersihan(PermintaanList* list);
void bersihkanMemoriPermintaan(PermintaanList* list);

// Burial Data Management
void tambahDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int& count, string nama, string tglLahir, string tglKematian, string lok, string pj);
void lihatDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int count);
bool hapusDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int& count, int index);
void cariDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int count, string nama, string blok);

// Land Management
void tambahLahan(Lahan data[MAX_LAHAN], int& count, string kode, string agm);
void lihatLahan(Lahan data[MAX_LAHAN], int count);
bool ubahStatusLahan(Lahan data[MAX_LAHAN], int count, int index);
void laporanKetersediaan(Lahan data[MAX_LAHAN], int count);

// Design Catalog Management
void tambahDesain(DesainMakam data[MAX_DESAIN], int& count, string kode, string nama, string desk);
void lihatKatalog(DesainMakam data[MAX_DESAIN], int count);
bool hapusDesain(DesainMakam data[MAX_DESAIN], int& count, int index);

// Cleaning Request Management (using linked list)
void tambahPermintaan(PermintaanList* list, string nama, string lokasi, string cat);
void lihatPermintaan(PermintaanList* list);

// Menu Functions
void tampilWelcome();
void menuAdmin();
void menuUser();
void tambahDataPemakamanMenu();
void lihatDataPemakamanMenu();
void hapusDataPemakamanMenu();
void kelolaLahan();
void laporanKetersediaanMenu();
void kelolaKatalogDesain();
void tambahDesainMakamMenu();
void lihatKatalogDesainMenu();
void hapusDesainMakamMenu();
void ajukanPembersihanMenu();
void lihatPermintaanPembersihanMenu();
void cariDataPemakamanMenu();

// ==================== MAIN ====================
int main() {
    // Initialize the cleaning request linked list
    inisialisasiPermintaanPembersihan(&permintaanPembersihan);
    
    // Start the application
    tampilWelcome();
    
    // Clean up memory before exiting
    bersihkanMemoriPermintaan(&permintaanPembersihan);
    
    return 0;
}

// ==================== INITIALIZATION & CLEANUP ====================
void inisialisasiPermintaanPembersihan(PermintaanList* list) {
    list->head = NULL;
    list->count = 0;
}

void bersihkanMemoriPermintaan(PermintaanList* list) {
    NodePermintaan* current = list->head;
    while (current != NULL) {
        NodePermintaan* temp = current;
        current = current->next;
        delete temp;
    }
    list->head = NULL;
    list->count = 0;
}

// ==================== BURIAL DATA FUNCTIONS (ARRAY) ====================
void tambahDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int& count, string nama, string tglLahir, string tglKematian, string lok, string pj) {
    if (count >= MAX_PEMAKAMAN) {
        cout << "Database pemakaman penuh!" << endl;
        return;
    }
    
    data[count].namaJenazah = nama;
    data[count].tanggalLahir = tglLahir;
    data[count].tanggalKematian = tglKematian;
    data[count].lokasi = lok;
    data[count].penanggungJawab = pj;
    data[count].statusTerisi = true;
    count++;
}

void lihatDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int count) {
    if (count == 0) {
        cout << "\nBelum ada data pemakaman.\n" << endl;
        return;
    }
    
    cout << "\n== Data Pemakaman ==" << endl;
    
    for (int i = 0; i < count; i++) {
        cout << "Data ke-" << (i+1) << endl;
        cout << "Nama Jenazah       : " << data[i].namaJenazah << endl;
        cout << "Tanggal Lahir      : " << data[i].tanggalLahir << endl;
        cout << "Tanggal Kematian   : " << data[i].tanggalKematian << endl;
        cout << "Lokasi             : " << data[i].lokasi << endl;
        cout << "Penanggung Jawab   : " << data[i].penanggungJawab << endl;
        cout << "Status             : " << (data[i].statusTerisi ? "Terisi" : "Kosong") << endl;
        cout << "-----------------------------" << endl;
    }
}

bool hapusDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int& count, int index) {
    if (count == 0 || index < 1 || index > count) {
        return false;
    }
    
    // Shifting elements to remove the selected index
    for (int i = index - 1; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    
    count--;
    return true;
}

void cariDataPemakaman(DataPemakaman data[MAX_PEMAKAMAN], int count, string nama, string blok) {
    if (count == 0) {
        cout << "Belum ada data pemakaman." << endl;
        return;
    }
    
    bool ditemukan = false;
    
    for (int i = 0; i < count; i++) {
        bool cocokNama = nama.empty() || 
            data[i].namaJenazah.find(nama) != string::npos;
        bool cocokBlok = blok.empty() || 
            data[i].lokasi.find(blok) != string::npos;
        
        if (cocokNama && cocokBlok) {
            ditemukan = true;
            cout << "\nData Pemakaman Ditemukan:" << endl;
            cout << "Nama Jenazah       : " << data[i].namaJenazah << endl;
            cout << "Tanggal Lahir      : " << data[i].tanggalLahir << endl;
            cout << "Tanggal Meninggal  : " << data[i].tanggalKematian << endl;
            cout << "Lokasi             : " << data[i].lokasi << endl;
            cout << "Penanggung Jawab   : " << data[i].penanggungJawab << endl;
            cout << "-----------------------------" << endl;
        }
    }
    
    if (!ditemukan) {
        cout << "Data pemakaman tidak ditemukan dengan kriteria yang diberikan." << endl;
    }
}

// ==================== LAND FUNCTIONS (ARRAY) ====================
void tambahLahan(Lahan data[MAX_LAHAN], int& count, string kode, string agm) {
    if (count >= MAX_LAHAN) {
        cout << "Database lahan penuh!" << endl;
        return;
    }
    
    data[count].kodeBlok = kode;
    data[count].agama = agm;
    data[count].statusTerisi = false;
    count++;
}

void lihatLahan(Lahan data[MAX_LAHAN], int count) {
    if (count == 0) {
        cout << "Belum ada lahan yang ditambahkan." << endl;
        return;
    }
    
    cout << "\n== Daftar Lahan ==" << endl;
    
    for (int i = 0; i < count; i++) {
        cout << (i+1) << ". Blok: " << data[i].kodeBlok
             << " | Agama: " << data[i].agama
             << " | Status: " << (data[i].statusTerisi ? "Terisi" : "Kosong") << endl;
    }
}

bool ubahStatusLahan(Lahan data[MAX_LAHAN], int count, int index) {
    if (count == 0 || index < 1 || index > count) {
        return false;
    }
    
    data[index-1].statusTerisi = !data[index-1].statusTerisi;
    return true;
}

void laporanKetersediaan(Lahan data[MAX_LAHAN], int count) {
    int kosong = 0, terisi = 0;
    
    for (int i = 0; i < count; i++) {
        if (data[i].statusTerisi) terisi++;
        else kosong++;
    }
    
    cout << "Lahan kosong  : " << kosong << endl;
    cout << "Lahan terisi  : " << terisi << endl;
    cout << "Total lahan   : " << count << endl;
}

// ==================== DESIGN CATALOG FUNCTIONS (ARRAY) ====================
void tambahDesain(DesainMakam data[MAX_DESAIN], int& count, string kode, string nama, string desk) {
    if (count >= MAX_DESAIN) {
        cout << "Katalog desain penuh!" << endl;
        return;
    }
    
    data[count].kodeDesain = kode;
    data[count].namaDesain = nama;
    data[count].deskripsi = desk;
    count++;
}

void lihatKatalog(DesainMakam data[MAX_DESAIN], int count) {
    if (count == 0) {
        cout << "\nBelum ada desain.\n" << endl;
        return;
    }
    
    cout << "\n== Katalog Desain Makam ==" << endl;
    
    for (int i = 0; i < count; i++) {
        cout << (i+1) << ". Kode     : " << data[i].kodeDesain << endl;
        cout << "   Nama     : " << data[i].namaDesain << endl;
        cout << "   Deskripsi: " << data[i].deskripsi << endl;
        cout << "--------------------------" << endl;
    }
}

bool hapusDesain(DesainMakam data[MAX_DESAIN], int& count, int index) {
    if (count == 0 || index < 1 || index > count) {
        return false;
    }
    
    // Shifting elements to remove the selected index
    for (int i = index - 1; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    
    count--;
    return true;
}

// ==================== CLEANING REQUEST FUNCTIONS (LINKED LIST) ====================
void tambahPermintaan(PermintaanList* list, string nama, string lokasi, string cat) {
    NodePermintaan* newNode = new NodePermintaan();
    newNode->namaPemohon = nama;
    newNode->lokasiMakam = lokasi;
    newNode->catatan = cat;
    newNode->next = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        NodePermintaan* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
}

void lihatPermintaan(PermintaanList* list) {
    if (list->head == NULL) {
        cout << "\nBelum ada permintaan.\n" << endl;
        return;
    }
    
    cout << "\n== Daftar Permintaan Pembersihan ==" << endl;
    NodePermintaan* current = list->head;
    int i = 1;
    
    while (current != NULL) {
        cout << i << ". Nama Pemohon : " << current->namaPemohon << endl;
        cout << "   Lokasi Makam : " << current->lokasiMakam << endl;
        cout << "   Catatan      : " << current->catatan << endl;
        cout << "-----------------------------" << endl;
        
        current = current->next;
        i++;
    }
}

// ==================== MENU FUNCTIONS ====================
void tampilWelcome() {
    int pilihan;
    cout << "=======================================" << endl;
    cout << "  SELAMAT DATANG DI SISTEM PEMAKAMAN   " << endl;
    cout << "=======================================" << endl;
    cout << "1. Masuk sebagai Admin" << endl;
    cout << "2. Masuk sebagai User" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih opsi: ";
    cin >> pilihan;

    switch(pilihan) {
        case 1:
            menuAdmin(); break;
        case 2:
            menuUser(); break;
        case 3:
            cout << "Terima kasih telah menggunakan aplikasi ini." << endl; break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            tampilWelcome();
    }
}

void menuAdmin() {
    int pilihan;
    cout << "\n==== MENU ADMIN ====" << endl;
    cout << "1. Tambah Data Pemakaman" << endl;
    cout << "2. Lihat Data Pemakaman" << endl;
    cout << "3. Hapus Data Pemakaman" << endl;
    cout << "4. Kelola Lahan Pemakaman" << endl;
    cout << "5. Laporan Ketersediaan Lahan" << endl;
    cout << "6. Kelola Katalog Desain Makam" << endl;
    cout << "7. Lihat Permintaan Pembersihan" << endl;
    cout << "8. Kembali ke Menu Utama" << endl;
    cout << "Pilih opsi: ";
    cin >> pilihan;
    cin.ignore();

    switch(pilihan) {
        case 1: tambahDataPemakamanMenu(); break;
        case 2: lihatDataPemakamanMenu(); break;
        case 3: hapusDataPemakamanMenu(); break;
        case 4: kelolaLahan(); break;
        case 5: laporanKetersediaanMenu(); break;
        case 6: kelolaKatalogDesain(); break;
        case 7: lihatPermintaanPembersihanMenu(); break;
        case 8: tampilWelcome(); return;
        default: cout << "Pilihan tidak valid." << endl;
    }

    menuAdmin();
}

void menuUser() {
    int pilihan;
    cout << "\n==== MENU USER ====" << endl;
    cout << "1. Cari Data Pemakaman" << endl;
    cout << "2. Lihat Katalog Desain Makam" << endl;
    cout << "3. Lihat Ketersediaan Lahan" << endl;
    cout << "4. Ajukan Permintaan Pembersihan" << endl;
    cout << "5. Kembali ke Menu Utama" << endl;
    cout << "Pilih opsi: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1: cariDataPemakamanMenu(); break;
        case 2: lihatKatalogDesainMenu(); break;
        case 3: laporanKetersediaanMenu(); break;
        case 4: ajukanPembersihanMenu(); break;
        case 5: tampilWelcome(); return;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }

    menuUser();
}

// ==================== ADMIN FEATURES MENU ====================
void tambahDataPemakamanMenu() {
    string nama, tglLahir, tglKematian, lokasi, pj;
    
    cout << "\n== Tambah Data Pemakaman ==" << endl;
    cout << "Nama Jenazah          : "; getline(cin, nama);
    cout << "Tanggal Lahir         : "; getline(cin, tglLahir);
    cout << "Tanggal Kematian      : "; getline(cin, tglKematian);
    cout << "Lokasi (blok/baris)   : "; getline(cin, lokasi);
    cout << "Penanggung Jawab      : "; getline(cin, pj);
    
    tambahDataPemakaman(dataPemakaman, jumlahPemakaman, nama, tglLahir, tglKematian, lokasi, pj);
    cout << "Data berhasil ditambahkan!\n" << endl;
}

void lihatDataPemakamanMenu() {
    lihatDataPemakaman(dataPemakaman, jumlahPemakaman);
}

void hapusDataPemakamanMenu() {
    int index;
    
    lihatDataPemakaman(dataPemakaman, jumlahPemakaman);
    if (jumlahPemakaman == 0) return;
    
    cout << "\nMasukkan nomor data yang ingin dihapus: "; cin >> index;
    
    if (hapusDataPemakaman(dataPemakaman, jumlahPemakaman, index)) {
        cout << "Data berhasil dihapus.\n" << endl;
    } else {
        cout << "Nomor tidak valid!" << endl;
    }
}

void kelolaLahan() {
    int pilihan;
    cout << "\n== Kelola Lahan Pemakaman ==" << endl;
    cout << "1. Tambah Lahan Baru" << endl;
    cout << "2. Tampilkan Semua Lahan" << endl;
    cout << "3. Ubah Status Lahan" << endl;
    cout << "Pilih opsi: "; cin >> pilihan; cin.ignore();

    if (pilihan == 1) {
        string kode, agama;
        cout << "Kode Blok (contoh i1, k2): "; getline(cin, kode);
        cout << "Agama (Islam/Kristen/dll): "; getline(cin, agama);
        
        tambahLahan(dataLahan, jumlahLahan, kode, agama);
        cout << "Lahan berhasil ditambahkan!" << endl;
    } else if (pilihan == 2) {
        lihatLahan(dataLahan, jumlahLahan);
    } else if (pilihan == 3) {
        int idx;
        lihatLahan(dataLahan, jumlahLahan);
        cout << "Masukkan nomor lahan yang ingin diubah statusnya: "; cin >> idx;
        
        if (ubahStatusLahan(dataLahan, jumlahLahan, idx)) {
            cout << "Status lahan berhasil diubah!" << endl;
        } else {
            cout << "Nomor tidak valid!" << endl;
        }
    } else {
        cout << "Pilihan tidak tersedia." << endl;
    }
}

void laporanKetersediaanMenu() {
    laporanKetersediaan(dataLahan, jumlahLahan);
}

void kelolaKatalogDesain() {
    int pilihan;
    cout << "\n== Kelola Katalog Desain ==" << endl;
    cout << "1. Tambah Desain" << endl;
    cout << "2. Lihat Katalog" << endl;
    cout << "3. Hapus Desain" << endl;
    cout << "Pilih opsi: "; cin >> pilihan; cin.ignore();
    switch (pilihan) {
        case 1: tambahDesainMakamMenu(); break;
        case 2: lihatKatalogDesainMenu(); break;
        case 3: hapusDesainMakamMenu(); break;
        default: cout << "Pilihan tidak valid." << endl;
    }
}

void tambahDesainMakamMenu() {
    string kode, nama, deskripsi;
    
    cout << "\nKode Desain   : "; getline(cin, kode);
    cout << "Nama Desain   : "; getline(cin, nama);
    cout << "Deskripsi     : "; getline(cin, deskripsi);
    
    tambahDesain(katalogDesain, jumlahDesain, kode, nama, deskripsi);
    cout << "Desain berhasil ditambahkan.\n";
}

void lihatKatalogDesainMenu() {
    lihatKatalog(katalogDesain, jumlahDesain);
}

void hapusDesainMakamMenu() {
    int index;
    
    lihatKatalog(katalogDesain, jumlahDesain);
    if (jumlahDesain == 0) return;
    
    cout << "\nMasukkan nomor desain yang ingin dihapus: ";
    cin >> index;
    
    if (hapusDesain(katalogDesain, jumlahDesain, index)) {
        cout << "Desain berhasil dihapus.\n";
    } else {
        cout << "Nomor tidak valid!" << endl;
    }
}

void lihatPermintaanPembersihanMenu() {
    lihatPermintaan(&permintaanPembersihan);
}

// ==================== USER FEATURES MENU ====================
void cariDataPemakamanMenu() {
    string namaCari, blokCari;
    
    cout << "\n==== CARI DATA PEMAKAMAN ====" << endl;
    cout << "Masukkan nama jenazah (kosongkan jika tidak ingin mencari berdasarkan nama): ";
    getline(cin, namaCari);
    cout << "Masukkan blok/lokasi (kosongkan jika tidak ingin mencari berdasarkan lokasi): ";
    getline(cin, blokCari);
    
    cout << "\n=== HASIL PENCARIAN ===" << endl;
    
    // Jika kedua input kosong
    if (namaCari.empty() && blokCari.empty()) {
        cout << "Silakan masukkan minimal satu kriteria pencarian." << endl;
        return;
    }
    
    cariDataPemakaman(dataPemakaman, jumlahPemakaman, namaCari, blokCari);
}

void ajukanPembersihanMenu() {
    string nama, lokasi, catatan;
    
    cout << "\n== Ajukan Permintaan Pembersihan ==" << endl;
    cout << "Nama Pemohon    : "; getline(cin, nama);
    cout << "Lokasi Makam    : "; getline(cin, lokasi);
    cout << "Catatan Tambahan: "; getline(cin, catatan);
    
    tambahPermintaan(&permintaanPembersihan, nama, lokasi, catatan);
    cout << "Permintaan berhasil diajukan!\n" << endl;
}