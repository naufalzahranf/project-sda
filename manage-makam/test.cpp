#include <iostream>
#include <string>
using namespace std;

const int max_pemakaman = 100;

struct NodePemakaman
{
    string namaJenazah;
    string tanggalLahir;
    string tanggalKematian;
    string lokasi;
    string penanggungJawab;
    bool statusTerisi;
    NodePemakaman* next;
};

struct NodePermintaan
{
    string namaPeminta;
    string lokasiMakam;
    string catatan;
    NodePermintaan* next;
};

NodePemakaman dataPemakaman[max_pemakaman];
int jumlahPemakaman = 0;
int jumlahPermintaan = 0;

NodePemakaman* headPemakaman = NULL;
NodePermintaan* headPermintaan = NULL;

void mainMenu();
void menuAdmin();
void menuPengguna();
void tambahDataPemakaman();
void lihatDataPemakaman();
bool hapusDataPemakaman();
void cariDataPemakaman();
void tambahPermintaan();
void lihatPermintaan();

void mainMenu()
{
    int pilihan;

    while (true)
    {
        cout << "=======================================" << endl;
        cout << "  SELAMAT DATANG DI SISTEM PEMAKAMAN   " << endl;
        cout << "=======================================" << endl;
        cout << "1) Masuk sebagai Administrator" << endl;
        cout << "2) Masuk sebagai Pengguna" << endl;
        cout << "3) Keluar" << endl;
        cout << "=======================================" << endl;
        cout << "Pilih opsi disini: "; cin >> pilihan;
        if (pilihan == 1)
        {
            cin.ignore();
            menuAdmin();
        }
        else if (pilihan == 2)
        {
            cin.ignore();
            menuPengguna();
        }
        else if (pilihan == 3)
        {
            break;
        }
        else
        {
           cout <<  "Opsi tidak tersedia. Silakan Ulangi." << endl;
        }
    }
}

void menuAdmin()
{
    int pilihan;

    while (true)
    {
        cout << "============= Menu Admin ==============" << endl;
        cout << "1. Tambah Data Pemakaman" << endl;
        cout << "2. Lihat Data Pemakaman" << endl;
        cout << "3. Hapus Data Pemakaman" << endl;
        cout << "4. Lihat Permintaan Pembersihan" << endl;
        cout << "5. Kembali ke Menu Utama" << endl;
        cout << "=======================================" << endl;
        cout << "Pilih opsi disini: "; cin >> pilihan;

        if (pilihan == 1)
        {
            tambahDataPemakaman();
        }
        else if (pilihan == 2)
        {
            lihatDataPemakaman();
        }
        else if (pilihan == 3)
        {
            hapusDataPemakaman();
        }
        else if (pilihan == 4)
        {
            lihatPermintaan();
        }
        else if (pilihan == 5)
        {
            return;
        }
        else
        {
            cout << "Pilihan tidak tersedia. Silakan ulangi." << endl;
        }
    }
}

void menuPengguna()
{
    int pilihan;

    while (true)
    {
        cout << "============ Menu Pengguna ============" << endl;
        cout << "1. Cari Data Pemakaman" << endl;
        cout << "2. Ajukan Permintaan Pembersihan" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "=======================================" << endl;
        cout << "Pilih opsi: "; cin >> pilihan;

        if (pilihan == 1)
        {
            cariDataPemakaman();
        }
        else if (pilihan == 2)
        {
            tambahPermintaan();
        }
        else if (pilihan == 3)
        {
            return;
        }
        else
        {
            cout << "Pilihan tidak tersedia. Silakan Ulangi." << endl;
        }
    }
}

void tambahDataPemakaman()
{
    string nama, tanggalLahir, tanggalKematian, lokasi, pj;

    cout << "======== Tambah Data Pemakaman ========" << endl;
    cin.ignore();

    cout << "Nama Jenazah           : "; getline(cin, nama);
    cout << "Tanggal Lahir          : "; getline(cin, tanggalLahir);
    cout << "Tanggal Kematian       : "; getline(cin, tanggalKematian);
    cout << "Lokasi (blok/baris)    : "; getline(cin, lokasi);
    cout << "Penanggung Jawab       : "; getline(cin, pj);

    NodePemakaman* new_node;
    new_node = new NodePemakaman();
    new_node -> namaJenazah = nama;
    new_node -> tanggalLahir = tanggalLahir;
    new_node -> tanggalKematian = tanggalKematian;
    new_node -> lokasi = lokasi;
    new_node -> penanggungJawab = pj;
    new_node -> statusTerisi = true;
    new_node -> next = NULL;

    if (headPemakaman == NULL)
    {
        headPemakaman = new_node;
    }
    else
    {
        NodePemakaman *current;
        current = headPemakaman;
        while (current -> next != NULL)
        {
            current = current -> next;
        }
        current -> next = new_node;
    }
    jumlahPemakaman++;
}

void lihatDataPemakaman()
{
    if (headPemakaman == NULL)
    {
        cout << "Maaf, belum ada data yang tersedia." << endl;
        return;
    }

    cout << "Data Pemakaman" << endl;
    NodePemakaman* current;
    current = headPemakaman;
    int i = 1;

    while (current != NULL)
    {
        cout << "========== Data Ke-" << i <<" ================="<< endl;
        cout << "Nama Jenazah       : " << current -> namaJenazah << endl;
        cout << "Tanggal Lahir      : " << current -> tanggalLahir << endl;
        cout << "Tanggal Kematian   : " << current -> tanggalKematian << endl;
        cout << "Lokasi             : " << current -> lokasi << endl;
        cout << "Penanggung Jawab   : " << current -> penanggungJawab << endl;
        cout << "Status             : " << (current -> statusTerisi ? "Terisi" : "Kosong") << endl;
        cout << "=======================================" << endl;

        current = current -> next;
        i++;
    }
}

bool hapusDataPemakaman()
{
    int index;
    lihatDataPemakaman();
    if (jumlahPemakaman == 0)
    {
        return false;
    }

    cout << "Masukkan nomor data yang ingin dihapus disini: "; cin >> index;

    if (headPemakaman == NULL || index < 1 || index > jumlahPemakaman)
    {
        return false;
    }

    NodePemakaman* temp;
    temp = headPemakaman;

    if (index == 1)
    {
        headPemakaman = headPemakaman -> next;
        delete temp;
        jumlahPemakaman--;
        return true;
    }

    NodePemakaman* current;
    current = headPemakaman;
    for (int i = 1; i < index - 1; i++)
    {
        current = current -> next;
    }

    temp = current -> next;
    current -> next = temp -> next;
    delete temp;
    jumlahPemakaman--;
    return true;
}

void cariDataPemakaman()
{
    string cariNama, cariBlok;

    cout << "========= Cari Data Pemakaman =========" << endl;
    cout << "Masukkan nama jenazah disini (kosongkan jika tidak ingin mencari): ";
    getline(cin, cariNama);
    cout << "Masukkan blok/lokasi disini (kosongkan jika tidak ingin mencari): ";
    getline(cin, cariBlok);
    cin.ignore();

    if (cariNama.empty() && cariBlok.empty())
    {
        cout << "Silakan masukkan minimal satu kriteria pencarian." << endl;
        return;
    }

    if (headPemakaman == NULL)
    {
        cout << "Belum ada data pemakaman." << endl;
        return;
    }

    NodePemakaman* current;
    current = headPemakaman;
    bool ditemukan = false;

    while (current != NULL)
    {
        bool cocokNama = cariNama.empty() ||
            current -> namaJenazah.find(cariNama) != string::npos;
        bool cocokBlok = cariBlok.empty() ||
            current -> lokasi.find(cariBlok) != string::npos;

        if (cocokNama && cocokBlok)
        {
            ditemukan = true;
            cout << "======= Data Pemakaman Ditemukan ======="<< endl;
            cout << "Nama Jenazah       : " << current -> namaJenazah << endl;
            cout << "Tanggal Lahir      : " << current -> tanggalLahir << endl;
            cout << "Tanggal Kematian   : " << current -> tanggalKematian << endl;
            cout << "Lokasi             : " << current -> lokasi << endl;
            cout << "Penanggung Jawab   : " << current -> penanggungJawab << endl;
            cout << "Status             : " << (current -> statusTerisi ? "Terisi" : "Kosong") << endl;
            cout << "========================================" << endl;
        }

        current = current -> next;
    }

    if (!ditemukan)
    {
        cout << "Data pemakaman yang dicari tidak ditemukan." << endl;
    }
}

void tambahPermintaan()
{
    string nama, lokasi, catatan;

    cout << "=========== Tambah Permintaan Pembersihan Makam ===================" << endl;
    cout << "Masukkan nama disini: "; getline(cin, nama);
    cout << "Masukkan blok jenazah disini: "; getline(cin, lokasi);
    cout << "Masukkan catatan untuk petugas disini (opsional): "; getline(cin, catatan);
    cout << "===================================================================" << endl;

    cin.ignore();

    NodePermintaan* new_node;
    new_node = new NodePermintaan;
    new_node -> namaPeminta = nama;
    new_node -> lokasiMakam = lokasi;
    new_node -> catatan = catatan;
    new_node -> next = NULL;

    if (headPermintaan == NULL)
    {
        headPermintaan = new_node;
    }
    else
    {
        NodePermintaan* current;
        current = headPermintaan;
        while (current->next != NULL)
        {
            current = current -> next;
        }
        current -> next = new_node;
    }
    jumlahPermintaan++;
}

void lihatPermintaan()
{
    if (headPermintaan == NULL)
    {
        cout << "Belum ada data permintaan." << endl;
        return;
    }

    cout << "Daftar Permintaan Pembersihan Makam" << endl;
    NodePermintaan* current;
    current = headPermintaan;
    int i = 1;

    while (current != NULL)
    {
        cout << i << ") Nama Peminta    : " << current->namaPeminta << endl;
        cout << "   Lokasi Makam        : " << current->lokasiMakam << endl;
        cout << "   Catatan             : " << current->catatan << endl;
        cout << "=======================================" << endl;

        current = current -> next;
        i++;
    }
}

int main()
{
    mainMenu();
}

