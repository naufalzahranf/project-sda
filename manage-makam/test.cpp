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

NodePermintaan* headPermintaan = NULL;

void mainMenu();
void menuAdmin();
void menuPengguna();
void tambahDataPemakaman();
void lihatDataPemakaman();
bool parseTanggal(const string& tanggal, int& dd, int& mm, int& yyyy);
bool tanggalKurangSama(int dd1, int mm1, int yyyy1, int dd2, int mm2, int yyyy2);
bool hapusDataPemakaman();
void cariDataPemakaman();
void tambahPermintaan();
void lihatPermintaan();

void mainMenu()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear")
    #endif

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
            menuAdmin();
        }
        else if (pilihan == 2)
        {
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
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

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
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

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
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (jumlahPemakaman >= max_pemakaman)
    {
        cout << "Maaf, data pemakaman sudah penuh!" << endl;
        return;
    }


    string nama, tanggalLahir, tanggalKematian, lokasi, pj;
    int ddLahir, mmLahir, yyyyLahir, ddKematian, mmKematian, yyyyKematian;

    cout << "======== Tambah Data Pemakaman ========" << endl;
    cin.ignore();

    cout << "Nama Jenazah           : "; getline(cin, nama);

    while (true)
    {
        cout << "Tanggal Lahir (dd-mm-yyyy)     : "; getline(cin, tanggalLahir);
        if (!parseTanggal(tanggalLahir, ddLahir, mmLahir, yyyyLahir))
        {
            cout << "Format yang diinput salah. Mohon input ulang." << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Tanggal Kematian (dd-mm-yyyy)  : "; getline(cin, tanggalKematian);
        if (!parseTanggal(tanggalKematian, ddKematian, mmKematian, yyyyKematian))
        {
            cout << "Format yang diinput salah. Mohon input ulang." << endl;
            continue;
        }
        if (!tanggalKurangSama(ddLahir, mmLahir, yyyyLahir, ddKematian, mmKematian, yyyyKematian))
        {
            cout << "Tanggal kematian harus setelah tanggal lahir. Mohon input ulang." << endl;
            continue;
        }
        break;
    }
    
    cout << "Lokasi (blok/baris)    : "; getline(cin, lokasi);
    cout << "Penanggung Jawab       : "; getline(cin, pj);

    dataPemakaman[jumlahPemakaman] = {nama, tanggalLahir, tanggalKematian, lokasi, pj};
    jumlahPemakaman++;
}

bool parseTanggal(const string& tanggal, int& dd, int& mm, int& yyyy)
{
    if (tanggal.length() != 10 || tanggal[2] != '-' || tanggal[5] != '-')
    {
        return false;
    }

    dd = (tanggal[0] - '0') * 10 + (tanggal[1] - '0');
    mm = (tanggal[3] - '0') * 10 + (tanggal[4] - '0');
    yyyy = (tanggal[6] - '0') * 1000 + (tanggal[7] - '0') * 100 + (tanggal[8] - '0') * 10 + (tanggal[9] - '0');

    if (dd < 1 || dd > 31 || mm < 1 || mm > 12 || yyyy < 1900)
    {
        return false;
    }
    return true;
}

bool tanggalKurangSama(int dd1, int mm1, int yyyy1, int dd2, int mm2, int yyyy2)
{
    if (yyyy1 != yyyy2)
    {
        return yyyy1 < yyyy2;
    }
    if (mm1 != mm2)
    {
        return mm1 < mm2;
    }
    return dd1 <= dd2;
}

void lihatDataPemakaman()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (jumlahPemakaman == 0)
    {
        cout << "Maaf, belum ada data yang tersedia." << endl;
        return;
    }

    cout << "Data Pemakaman" << endl;

    for (int i = 0; i < jumlahPemakaman; i++)
    {
        cout << "========== Data Ke-" << i + 1 <<" ================="<< endl;
        cout << "Nama Jenazah       : " << dataPemakaman[i].namaJenazah << endl;
        cout << "Tanggal Lahir      : " << dataPemakaman[i].tanggalLahir << endl;
        cout << "Tanggal Kematian   : " << dataPemakaman[i].tanggalKematian << endl;
        cout << "Lokasi             : " << dataPemakaman[i].lokasi << endl;
        cout << "Penanggung Jawab   : " << dataPemakaman[i].penanggungJawab << endl;
        cout << "=======================================" << endl;
    }
}

bool hapusDataPemakaman()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (jumlahPemakaman == 0)
    {
        cout << "Maaf, belum ada data yang tersedia." << endl;
        return false;
    }

    lihatDataPemakaman();
    int index;
    cout << "Masukkan nomor data yang akan dihapus disini: ";
    cin >> index;

    if (index < 1 || index > jumlahPemakaman)
    {
        cout << "Indeks tidak valid." << endl;
        return false;
    }

    index--;
    for (int i = index; i < jumlahPemakaman - 1; i++)
    {
        dataPemakaman[i] = dataPemakaman[i+1];
    }
    jumlahPemakaman--;
    return true;
}

void cariDataPemakaman()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    string cariNama, cariBlok;

    cout << "========= Cari Data Pemakaman =========" << endl;
    cin.ignore();
    cout << "Masukkan nama jenazah disini (kosongkan jika tidak ingin mencari): ";
    getline(cin, cariNama);
    cout << "Masukkan blok/lokasi disini (kosongkan jika tidak ingin mencari): ";
    getline(cin, cariBlok);

    if (cariNama.empty() && cariBlok.empty())
    {
        cout << "Silakan masukkan minimal satu kriteria pencarian." << endl;
        return;
    }

    if (jumlahPemakaman == 0)
    {
        cout << "Belum ada data pemakaman." << endl;
        return;
    }

    bool ditemukan = false;

    for (int i = 0; i < jumlahPemakaman; i++)
    {
        bool cocokNama = cariNama.empty() || dataPemakaman[i].namaJenazah.find(cariNama) != string::npos;
        bool cocokBlok = cariBlok.empty() || dataPemakaman[i].lokasi.find(cariBlok) != string::npos;

        if (cocokNama && cocokBlok)
        {
            ditemukan = true;
            cout << "======= Data Pemakaman Ditemukan ======="<< endl;
            cout << "Nama Jenazah       : " << dataPemakaman[i].namaJenazah << endl;
            cout << "Tanggal Lahir      : " << dataPemakaman[i].tanggalLahir << endl;
            cout << "Tanggal Kematian   : " << dataPemakaman[i].tanggalKematian << endl;
            cout << "Lokasi             : " << dataPemakaman[i].lokasi << endl;
            cout << "Penanggung Jawab   : " << dataPemakaman[i].penanggungJawab << endl;
            cout << "========================================" << endl;
        }
    }

    if (!ditemukan)
    {
        cout << "Data pemakaman yang dicari tidak ditemukan." << endl;
    }
}

void tambahPermintaan()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    string nama, lokasi, catatan;

    cout << "=========== Tambah Permintaan Pembersihan Makam ===================" << endl;
    cin.ignore();
    cout << "Masukkan nama disini                               : "; getline(cin, nama);
    cout << "Masukkan blok jenazah disini                       : "; getline(cin, lokasi);
    cout << "Masukkan catatan untuk petugas disini (opsional)   : "; getline(cin, catatan);
    cout << "===================================================================" << endl;

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
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

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
        cout << "   Lokasi Makam    : " << current->lokasiMakam << endl;
        cout << "   Catatan         : " << current->catatan << endl;
        cout << "=======================================" << endl;

        current = current -> next;
        i++;
    }
}

int main()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    mainMenu();
}

