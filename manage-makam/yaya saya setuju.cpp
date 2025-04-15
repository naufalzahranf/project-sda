#include <iostream>
#include <string>
using namespace std;

// ==================== STRUCT NODE ====================
// Node untuk Data Pemakaman
struct NodePemakaman {
    string namaJenazah;
    string tanggalLahir;
    string tanggalKematian;
    string lokasi;
    string penanggungJawab;
    bool statusTerisi;
    NodePemakaman* next;
};

// Node untuk Lahan Pemakaman
struct NodeLahan {
    string kodeBlok;
    bool statusTerisi;
    string agama;
    NodeLahan* next;
};

// Node untuk Desain Makam
struct NodeDesain {
    string kodeDesain;
    string namaDesain;
    string deskripsi;
    NodeDesain* next;
};

// Node untuk Permintaan Pembersihan
struct NodePermintaan {
    string namaPemohon;
    string lokasiMakam;
    string catatan;
    NodePermintaan* next;
};

// ==================== LINKED LIST CLASS ====================
// Linked List untuk Data Pemakaman
class PemakamanList {
private:
    NodePemakaman* head;
    int count;
    
public:
    PemakamanList() {
        head = NULL;
        count = 0;
    }
    
    ~PemakamanList() {
        NodePemakaman* current = head;
        while (current != NULL) {
            NodePemakaman* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    void tambahData(string nama, string tglLahir, string tglKematian, string lok, string pj) {
        NodePemakaman* newNode = new NodePemakaman();
        newNode->namaJenazah = nama;
        newNode->tanggalLahir = tglLahir;
        newNode->tanggalKematian = tglKematian;
        newNode->lokasi = lok;
        newNode->penanggungJawab = pj;
        newNode->statusTerisi = true;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
        } else {
            NodePemakaman* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++;
    }
    
    void lihatData() {
        if (head == NULL) {
            cout << "\nBelum ada data pemakaman.\n" << endl;
            return;
        }
        
        cout << "\n== Data Pemakaman ==" << endl;
        NodePemakaman* current = head;
        int i = 1;
        
        while (current != NULL) {
            cout << "Data ke-" << i << endl;
            cout << "Nama Jenazah       : " << current->namaJenazah << endl;
            cout << "Tanggal Lahir      : " << current->tanggalLahir << endl;
            cout << "Tanggal Kematian   : " << current->tanggalKematian << endl;
            cout << "Lokasi             : " << current->lokasi << endl;
            cout << "Penanggung Jawab   : " << current->penanggungJawab << endl;
            cout << "Status             : " << (current->statusTerisi ? "Terisi" : "Kosong") << endl;
            cout << "-----------------------------" << endl;
            
            current = current->next;
            i++;
        }
    }
    
    bool hapusData(int index) {
        if (head == NULL || index < 1 || index > count) {
            return false;
        }
        
        NodePemakaman* temp = head;
        if (index == 1) {
            head = head->next;
            delete temp;
            count--;
            return true;
        }
        
        NodePemakaman* current = head;
        for (int i = 1; i < index - 1; i++) {
            current = current->next;
        }
        
        temp = current->next;
        current->next = temp->next;
        delete temp;
        count--;
        return true;
    }
    
    void cariData(string nama, string blok) {
        if (head == NULL) {
            cout << "Belum ada data pemakaman." << endl;
            return;
        }
        
        NodePemakaman* current = head;
        bool ditemukan = false;
        
        while (current != NULL) {
            bool cocokNama = nama.empty() || 
                current->namaJenazah.find(nama) != string::npos;
            bool cocokBlok = blok.empty() || 
                current->lokasi.find(blok) != string::npos;
            
            if (cocokNama && cocokBlok) {
                ditemukan = true;
                cout << "\nData Pemakaman Ditemukan:" << endl;
                cout << "Nama Jenazah       : " << current->namaJenazah << endl;
                cout << "Tanggal Lahir      : " << current->tanggalLahir << endl;
                cout << "Tanggal Meninggal  : " << current->tanggalKematian << endl;
                cout << "Lokasi             : " << current->lokasi << endl;
                cout << "Penanggung Jawab   : " << current->penanggungJawab << endl;
                cout << "-----------------------------" << endl;
            }
            
            current = current->next;
        }
        
        if (!ditemukan) {
            cout << "Data pemakaman tidak ditemukan dengan kriteria yang diberikan." << endl;
        }
    }
    
    int getCount() {
        return count;
    }
};

// Linked List untuk Lahan Pemakaman
class LahanList {
    private:
        NodeLahan* head;
        int count;
        
    public:
        LahanList() {
            head = NULL;
            count = 0;
        }
        
        ~LahanList() {
            NodeLahan* current = head;
            while (current != NULL) {
                NodeLahan* temp = current;
                current = current->next;
                delete temp;
            }
        }
        
        void tambahLahan(string kode, string agm) {
            NodeLahan* newNode = new NodeLahan();
            newNode->kodeBlok = kode;
            newNode->agama = agm;
            newNode->statusTerisi = false;
            newNode->next = NULL;
            
            if (head == NULL) {
                head = newNode;
            } else {
                NodeLahan* current = head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNode;
            }
            count++;
        }
        
        void lihatLahan() {
            if (head == NULL) {
                cout << "Belum ada lahan yang ditambahkan." << endl;
                return;
            }
            
            cout << "\n== Daftar Lahan ==" << endl;
            NodeLahan* current = head;
            int i = 1;
            
            while (current != NULL) {
                cout << i << ". Blok: " << current->kodeBlok
                     << " | Agama: " << current->agama
                     << " | Status: " << (current->statusTerisi ? "Terisi" : "Kosong") << endl;
                
                current = current->next;
                i++;
            }
        }
        
        bool ubahStatusLahan(int index) {
            if (head == NULL || index < 1 || index > count) {
                return false;
            }
            
            NodeLahan* current = head;
            for (int i = 1; i < index; i++) {
                current = current->next;
            }
            
            current->statusTerisi = !current->statusTerisi;
            return true;
        }
        
        void laporanKetersediaan() {
            int kosong = 0, terisi = 0;
            NodeLahan* current = head;
            
            while (current != NULL) {
                if (current->statusTerisi) terisi++;
                else kosong++;
                current = current->next;
            }
            
            cout << "Lahan kosong  : " << kosong << endl;
            cout << "Lahan terisi  : " << terisi << endl;
            cout << "Total lahan   : " << count << endl;
        }
        
        int getCount() {
            return count;
        }
    };
    
    // Linked List untuk Katalog Desain
    class DesainList {
    private:
        NodeDesain* head;
        int count;
        
    public:
        DesainList() {
            head = NULL;
            count = 0;
        }
        
        ~DesainList() {
            NodeDesain* current = head;
            while (current != NULL) {
                NodeDesain* temp = current;
                current = current->next;
                delete temp;
            }
        }
        
        void tambahDesain(string kode, string nama, string desk) {
            NodeDesain* newNode = new NodeDesain();
            newNode->kodeDesain = kode;
            newNode->namaDesain = nama;
            newNode->deskripsi = desk;
            newNode->next = NULL;
            
            if (head == NULL) {
                head = newNode;
            } else {
                NodeDesain* current = head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNode;
            }
            count++;
        }
        
        void lihatKatalog() {
            if (head == NULL) {
                cout << "\nBelum ada desain.\n" << endl;
                return;
            }
            
            cout << "\n== Katalog Desain Makam ==" << endl;
            NodeDesain* current = head;
            int i = 1;
            
            while (current != NULL) {
                cout << i << ". Kode     : " << current->kodeDesain << endl;
                cout << "   Nama     : " << current->namaDesain << endl;
                cout << "   Deskripsi: " << current->deskripsi << endl;
                cout << "--------------------------" << endl;
                
                current = current->next;
                i++;
            }
        }
        
        bool hapusDesain(int index) {
            if (head == NULL || index < 1 || index > count) {
                return false;
            }
            
            NodeDesain* temp = head;
            if (index == 1) {
                head = head->next;
                delete temp;
                count--;
                return true;
            }
            
            NodeDesain* current = head;
            for (int i = 1; i < index - 1; i++) {
                current = current->next;
            }
            
            temp = current->next;
            current->next = temp->next;
            delete temp;
            count--;
            return true;
        }
        
        int getCount() {
            return count;
        }
    };
    
// Linked List untuk Permintaan Pembersihan
class PermintaanList {
    private:
        NodePermintaan* head;
        int count;
        
    public:
        PermintaanList() {
            head = NULL;
            count = 0;
        }
        
        ~PermintaanList() {
            NodePermintaan* current = head;
            while (current != NULL) {
                NodePermintaan* temp = current;
                current = current->next;
                delete temp;
            }
        }
        
        void tambahPermintaan(string nama, string lokasi, string cat) {
            NodePermintaan* newNode = new NodePermintaan();
            newNode->namaPemohon = nama;
            newNode->lokasiMakam = lokasi;
            newNode->catatan = cat;
            newNode->next = NULL;
            
            if (head == NULL) {
                head = newNode;
            } else {
                NodePermintaan* current = head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNode;
            }
            count++;
        }
        
        void lihatPermintaan() {
            if (head == NULL) {
                cout << "\nBelum ada permintaan.\n" << endl;
                return;
            }
            
            cout << "\n== Daftar Permintaan Pembersihan ==" << endl;
            NodePermintaan* current = head;
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
        
        int getCount() {
            return count;
        }
    };
    
    // ==================== INSTANCE GLOBAL ====================
    PemakamanList dataPemakaman;
    LahanList dataLahan;
    DesainList katalogDesain;
    PermintaanList permintaanPembersihan;
    
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
    void cariDataPemakaman();
    
    // ==================== MAIN ====================
    int main() {
        tampilWelcome();
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
    
// ==================== MENU USER ====================
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
        case 1: cariDataPemakaman(); break;
        case 2: lihatKatalogDesain(); break;
        case 3: laporanKetersediaan(); break;
        case 4: ajukanPembersihan(); break;
        case 5: tampilWelcome(); return;
        default:
            cout << "Pilihan tidak valid!" << endl;
    }

    menuUser();
}

// ==================== FITUR ADMIN ====================
void tambahDataPemakaman() {
    string nama, tglLahir, tglKematian, lokasi, pj;
    
    cout << "\n== Tambah Data Pemakaman ==" << endl;
    cout << "Nama Jenazah          : "; getline(cin, nama);
    cout << "Tanggal Lahir         : "; getline(cin, tglLahir);
    cout << "Tanggal Kematian      : "; getline(cin, tglKematian);
    cout << "Lokasi (blok/baris)   : "; getline(cin, lokasi);
    cout << "Penanggung Jawab      : "; getline(cin, pj);
    
    dataPemakaman.tambahData(nama, tglLahir, tglKematian, lokasi, pj);
    cout << "Data berhasil ditambahkan!\n" << endl;
}

void lihatDataPemakaman() {
    dataPemakaman.lihatData();
}

void hapusDataPemakaman() {
    int index;
    
    lihatDataPemakaman();
    if (dataPemakaman.getCount() == 0) return;
    
    cout << "\nMasukkan nomor data yang ingin dihapus: "; cin >> index;
    
    if (dataPemakaman.hapusData(index)) {
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
        
        dataLahan.tambahLahan(kode, agama);
        cout << "Lahan berhasil ditambahkan!" << endl;
    } else if (pilihan == 2) {
        dataLahan.lihatLahan();
    } else if (pilihan == 3) {
        int idx;
        dataLahan.lihatLahan();
        cout << "Masukkan nomor lahan yang ingin diubah statusnya: "; cin >> idx;
        
        if (dataLahan.ubahStatusLahan(idx)) {
            cout << "Status lahan berhasil diubah!" << endl;
        } else {
            cout << "Nomor tidak valid!" << endl;
        }
    } else {
        cout << "Pilihan tidak tersedia." << endl;
    }
}

void laporanKetersediaan() {
    dataLahan.laporanKetersediaan();
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
    string kode, nama, deskripsi;
    
    cout << "\nKode Desain   : "; getline(cin, kode);
    cout << "Nama Desain   : "; getline(cin, nama);
    cout << "Deskripsi     : "; getline(cin, deskripsi);
    
    katalogDesain.tambahDesain(kode, nama, deskripsi);
    cout << "Desain berhasil ditambahkan.\n";
}

void lihatKatalogDesain() {
    katalogDesain.lihatKatalog();
}

void hapusDesainMakam() {
    int index;
    
    lihatKatalogDesain();
    if (katalogDesain.getCount() == 0) return;
    
    cout << "\nMasukkan nomor desain yang ingin dihapus: ";
    cin >> index;
    
    if (katalogDesain.hapusDesain(index)) {
        cout << "Desain berhasil dihapus.\n";
    } else {
        cout << "Nomor tidak valid!" << endl;
    }
}

void lihatPermintaanPembersihan() {
    permintaanPembersihan.lihatPermintaan();
}

// ==================== FITUR USER ====================
void cariDataPemakaman() {
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
    
    dataPemakaman.cariData(namaCari, blokCari);
}

void ajukanPembersihan() {
    string nama, lokasi, catatan;
    
    cout << "\n== Ajukan Permintaan Pembersihan ==" << endl;
    cout << "Nama Pemohon    : "; getline(cin, nama);
    cout << "Lokasi Makam    : "; getline(cin, lokasi);
    cout << "Catatan Tambahan: "; getline(cin, catatan);
    
    permintaanPembersihan.tambahPermintaan(nama, lokasi, catatan);
    cout << "Permintaan berhasil diajukan!\n" << endl;
}