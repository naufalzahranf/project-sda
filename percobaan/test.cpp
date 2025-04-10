#include <iostream>
#include <string>
using namespace std;

// ==================== STRUCT ====================
struct DataPemakaman {
    string namaJenazah;
    string tanggalLahir;
    string tanggalKematian;
    string lokasi;
    string penanggungJawab;
    bool statusTerisi;
};

struct LahanPemakaman {
    string kodeBlok;
    bool statusTerisi;
    string agama;
};

struct DesainMakam {
    string kodeDesain;
    string namaDesain;
    string deskripsi;
};

struct PermintaanPembersihan {
    string namaPemohon;
    string lokasiMakam;
    string catatan;
};

// ==================== VARIABEL GLOBAL ====================
const int MAX_MAKAM = 100;
DataPemakaman makam[MAX_MAKAM];
int jumlahMakam = 0;

const int MAX_LAHAN = 100;
LahanPemakaman lahan[MAX_LAHAN];
int jumlahLahan = 0;

const int MAX_DESAIN = 100;
DesainMakam katalog[MAX_DESAIN];
int jumlahDesain = 0;

const int MAX_PERMINTAAN = 100;
PermintaanPembersihan permintaan[MAX_PERMINTAAN];
int jumlahPermintaan = 0;

// ==================== FUNGSI PROTOTIPE ====================
void tampilWelcome();
void menuAdmin();
void menuUser();
void tambahDataPemakaman();
void lihatDataPemakaman();
void hapusDataPemakaman();
void kelolaLahan();
void laporanKetersediaan();
void kelolaKatalogDesain();
void tambahDesainMakam();
void lihatKatalogDesain();
void hapusDesainMakam();
void ajukanPembersihan();
void lihatPermintaanPembersihan();

// ==================== MAIN ====================
int main() {
    tampilWelcome();
    cout << "Hello, World!" << endl;
    cout << "This is a test program." << endl;
    cout << "Let's see if it works." << endl;
    cout << "This is a test for the GitHub Copilot." << endl;
    return 0;

}

// ==================== MENU UTAMA ====================
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

// ==================== MENU ADMIN ====================
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
        case 1: tambahDataPemakaman(); break;
        case 2: lihatDataPemakaman(); break;
        case 3: hapusDataPemakaman(); break;
        case 4: kelolaLahan(); break;
        case 5: laporanKetersediaan(); break;
        case 6: kelolaKatalogDesain(); break;
        case 7: lihatPermintaanPembersihan(); break;
        case 8: tampilWelcome(); return;
        default: cout << "Pilihan tidak valid." << endl;
    }

    menuAdmin();
}

// ==================== FITUR ADMIN ====================
void tambahDataPemakaman() {
    if (jumlahMakam >= MAX_MAKAM) {
        cout << "Kapasitas data makam sudah penuh!" << endl;
        return;
    }
    cout << "\n== Tambah Data Pemakaman ==" << endl;
    cout << "Nama Jenazah          : "; getline(cin, makam[jumlahMakam].namaJenazah);
    cout << "Tanggal Lahir         : "; getline(cin, makam[jumlahMakam].tanggalLahir);
    cout << "Tanggal Kematian      : "; getline(cin, makam[jumlahMakam].tanggalKematian);
    cout << "Lokasi (blok/baris)   : "; getline(cin, makam[jumlahMakam].lokasi);
    cout << "Penanggung Jawab      : "; getline(cin, makam[jumlahMakam].penanggungJawab);
    makam[jumlahMakam].statusTerisi = true;
    jumlahMakam++;
    cout << "Data berhasil ditambahkan!\n" << endl;
}

void lihatDataPemakaman() {
    if (jumlahMakam == 0) {
        cout << "\nBelum ada data pemakaman.\n" << endl;
        return;
    }
    cout << "\n== Data Pemakaman ==" << endl;
    for (int i = 0; i < jumlahMakam; i++) {
        cout << "Data ke-" << i+1 << endl;
        cout << "Nama Jenazah       : " << makam[i].namaJenazah << endl;
        cout << "Tanggal Lahir      : " << makam[i].tanggalLahir << endl;
        cout << "Tanggal Kematian   : " << makam[i].tanggalKematian << endl;
        cout << "Lokasi             : " << makam[i].lokasi << endl;
        cout << "Penanggung Jawab   : " << makam[i].penanggungJawab << endl;
        cout << "Status             : " << (makam[i].statusTerisi ? "Terisi" : "Kosong") << endl;
        cout << "-----------------------------" << endl;
    }
}

void hapusDataPemakaman() {
    int index;
    lihatDataPemakaman();
    if (jumlahMakam == 0) return;
    cout << "\nMasukkan nomor data yang ingin dihapus: "; cin >> index;
    index--;
    if (index < 0 || index >= jumlahMakam) {
        cout << "Nomor tidak valid!" << endl;
        return;
    }
    for (int i = index; i < jumlahMakam - 1; i++) {
        makam[i] = makam[i + 1];
    }
    jumlahMakam--;
    cout << "Data berhasil dihapus.\n" << endl;
}

void kelolaLahan() {
    int pilihan;
    cout << "\n== Kelola Lahan Pemakaman ==" << endl;
    cout << "1. Tambah Lahan Baru" << endl;
    cout << "2. Tampilkan Semua Lahan" << endl;
    cout << "3. Ubah Status Lahan" << endl;
    cout << "Pilih opsi: "; cin >> pilihan; cin.ignore();

    if (pilihan == 1) {
        if (jumlahLahan >= MAX_LAHAN) {
            cout << "Jumlah maksimum lahan tercapai!" << endl;
            return;
        }
        cout << "Kode Blok (contoh i1, k2): "; getline(cin, lahan[jumlahLahan].kodeBlok);
        cout << "Agama (Islam/Kristen/dll): "; getline(cin, lahan[jumlahLahan].agama);
        lahan[jumlahLahan].statusTerisi = false;
        jumlahLahan++;
        cout << "Lahan berhasil ditambahkan!" << endl;
    } else if (pilihan == 2) {
        if (jumlahLahan == 0) {
            cout << "Belum ada lahan yang ditambahkan." << endl;
            return;
        }
        cout << "\n== Daftar Lahan ==" << endl;
        for (int i = 0; i < jumlahLahan; i++) {
            cout << i+1 << ". Blok: " << lahan[i].kodeBlok
                 << " | Agama: " << lahan[i].agama
                 << " | Status: " << (lahan[i].statusTerisi ? "Terisi" : "Kosong") << endl;
        }
    } else if (pilihan == 3) {
        int idx;
        cout << "Masukkan nomor lahan yang ingin diubah statusnya: "; cin >> idx;
        idx--;
        if (idx < 0 || idx >= jumlahLahan) {
            cout << "Nomor tidak valid!" << endl;
            return;
        }
        lahan[idx].statusTerisi = !lahan[idx].statusTerisi;
        cout << "Status lahan berhasil diubah ke: " << (lahan[idx].statusTerisi ? "Terisi" : "Kosong") << endl;
    } else {
        cout << "Pilihan tidak tersedia." << endl;
    }
}

void laporanKetersediaan() {
    int kosong = 0, terisi = 0;
    for (int i = 0; i < jumlahLahan; i++) {
        if (lahan[i].statusTerisi) terisi++;
        else kosong++;
    }
    cout << "Lahan kosong  : " << kosong << endl;
    cout << "Lahan terisi  : " << terisi << endl;
}

void kelolaKatalogDesain() {
    int pilihan;
    cout << "\n== Kelola Katalog Desain ==" << endl;
    cout << "1. Tambah Desain" << endl;
    cout << "2. Lihat Katalog" << endl;
    cout << "3. Hapus Desain" << endl;
    cout << "Pilih opsi: "; cin >> pilihan; cin.ignore();
    switch (pilihan) {
        case 1: tambahDesainMakam(); break;
        case 2: lihatKatalogDesain(); break;
        case 3: hapusDesainMakam(); break;
        default: cout << "Pilihan tidak valid." << endl;
    }
}

void tambahDesainMakam() {
    if (jumlahDesain >= MAX_DESAIN) {
        cout << "Katalog penuh!" << endl;
        return;
    }
    cout << "\nKode Desain   : "; getline(cin, katalog[jumlahDesain].kodeDesain);
    cout << "Nama Desain   : "; getline(cin, katalog[jumlahDesain].namaDesain);
    cout << "Deskripsi     : "; getline(cin, katalog[jumlahDesain].deskripsi);
    jumlahDesain++;
    cout << "Desain berhasil ditambahkan.\n";
}

void lihatKatalogDesain() {
    cout << "\n== Katalog Desain Makam ==" << endl;
    if (jumlahDesain == 0) {
        cout << "Belum ada desain." << endl;
        return;
    }
    for (int i = 0; i < jumlahDesain; i++) {
        cout << "Kode     : " << katalog[i].kodeDesain << endl;
        cout << "Nama     : " << katalog[i].namaDesain << endl;
        cout << "Deskripsi: " << katalog[i].deskripsi << endl;
        cout << "--------------------------" << endl;
    }
}

void hapusDesainMakam() {
    int index;
    lihatKatalogDesain();
    cout << "\nMasukkan nomor desain yang ingin dihapus: ";
    cin >> index;
    index--;
    if (index < 0 || index >= jumlahDesain) {
        cout << "Nomor tidak valid!" << endl;
        return;
    }
    for (int i = index; i < jumlahDesain - 1; i++) {
        katalog[i] = katalog[i + 1];
    }
    jumlahDesain--;
    cout << "Desain berhasil dihapus.\n";
}

void lihatPermintaanPembersihan() {
    cout << "\n== Daftar Permintaan Pembersihan ==" << endl;
    if (jumlahPermintaan == 0) {
        cout << "Belum ada permintaan." << endl;
        return;
    }
    for (int i = 0; i < jumlahPermintaan; i++) {
        cout << "Nama Pemohon : " << permintaan[i].namaPemohon << endl;
        cout << "Lokasi Makam : " << permintaan[i].lokasiMakam << endl;
        cout << "Catatan      : " << permintaan[i].catatan << endl;
        cout << "-----------------------------" << endl;
    }
}

// Tambahkan prototipe fungsi baru pada bagian FUNGSI PROTOTIPE
void cariDataPemakaman();

// Ubah fungsi menuUser() dengan opsi "Cari Data Pemakaman" di nomor 1
void menuUser() {
    int pilihan;
    cout << "\n==== MENU USER ====" << endl;
    cout << "1. Cari Data Pemakaman" << endl;  // Opsi pindah ke nomor 1
    cout << "2. Lihat Katalog Desain Makam" << endl;
    cout << "3. Lihat Ketersediaan Lahan" << endl;
    cout << "4. Ajukan Permintaan Pembersihan" << endl;
    cout << "5. Kembali ke Menu Utama" << endl;
    cout << "Pilih opsi: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1: cariDataPemakaman(); break;  // Opsi pindah ke nomor 1
        case 2: lihatKatalogDesain(); break;
        case 3: laporanKetersediaan(); break;
        case 4: ajukanPembersihan(); break;
        case 5: tampilWelcome(); return;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }

    menuUser();
}

// Implementasi fungsi pencarian data pemakaman dengan tanggal lengkap
void cariDataPemakaman() {
    string namaCari, blokCari;
    bool ditemukan = false;
    
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
    
    for (int i = 0; i < jumlahMakam; i++) {
        // Periksa kondisi pencarian
        bool cocokNama = namaCari.empty() || 
            makam[i].namaJenazah.find(namaCari) != string::npos;
        bool cocokBlok = blokCari.empty() || 
            makam[i].lokasi.find(blokCari) != string::npos;
        
        // Jika cocok dengan kriteria pencarian
        if (cocokNama && cocokBlok) {
            ditemukan = true;
            cout << "\nData Pemakaman Ditemukan:" << endl;
            cout << "Nama Jenazah       : " << makam[i].namaJenazah << endl;
            cout << "Tanggal Lahir      : " << makam[i].tanggalLahir << endl;
            cout << "Tanggal Meninggal  : " << makam[i].tanggalKematian << endl;
            cout << "Lokasi             : " << makam[i].lokasi << endl;
            cout << "Penanggung Jawab   : " << makam[i].penanggungJawab << endl;
            cout << "-----------------------------" << endl;
        }
    }
    
    if (!ditemukan) {
        cout << "Data pemakaman tidak ditemukan dengan kriteria yang diberikan." << endl;
    }
}

void ajukanPembersihan() {
    if (jumlahPermintaan >= MAX_PERMINTAAN) {
        cout << "Permintaan penuh!" << endl;
        return;
    }
    cout << "\n== Ajukan Permintaan Pembersihan ==" << endl;
    cout << "Nama Pemohon    : "; getline(cin, permintaan[jumlahPermintaan].namaPemohon);
    cout << "Lokasi Makam    : "; getline(cin, permintaan[jumlahPermintaan].lokasiMakam);
    cout << "Catatan Tambahan: "; getline(cin, permintaan[jumlahPermintaan].catatan);
    jumlahPermintaan++;
    cout << "Permintaan berhasil diajukan!\n" << endl;
}