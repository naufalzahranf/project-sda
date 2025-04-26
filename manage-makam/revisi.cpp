#include <iostream>
#include <string>
using namespace std;

const int max_pemakaman = 100;

struct Akun
{
    string username;
    string password;
    string role;
};

Akun akunAdmin = {"admin", "admin123", "admin"};

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
    string namaKeluarga;
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

void login()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    string username, password;

    cout << "======= Login Sistem Pemakaman ========" << endl;
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;

    if (username == akunAdmin.username && password == akunAdmin.password)
    {
        cout << "Login sebagai administrator berhasil!" << endl;
        menuAdmin();
    }
    else
    {
        cout << "Login berhasil!" << endl;
        menuPengguna();
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
        cout << "3. Cari Data Pemakaman" << endl;
        cout << "4. Hapus Data Pemakaman" << endl;
        cout << "5. Lihat Permintaan Pembersihan" << endl;
        cout << "6. Kembali ke Halaman Login" << endl;
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
            cariDataPemakaman();
        }
        else if (pilihan == 4)
        {
            hapusDataPemakaman();
        }
        else if (pilihan == 5)
        {
            lihatPermintaan();
        }
        else if (pilihan == 6)
        {
            login();
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
        cout << "3. Kembali ke Halaman Login" << endl;
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
            login();
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

    string cariNama, cariTglLahir, cariTglKematian;

    cout << "========= Cari Data Pemakaman =========" << endl;
    cin.ignore();
    cout << "Masukkan nama lengkap jenazah disini       : ";
    getline(cin, cariNama);
    cout << "Masukkan tanggal lahir jenazah disini      : ";
    getline(cin, cariTglLahir);
    cout << "Masukkan tanggal kematian jenazah disini   : ";
    getline(cin, cariTglKematian);

    if(cariNama.empty())
    {
        cout << "Nama jenazah wajib diisi." << endl;
        return;
    }

    if ((!cariTglLahir.empty() && !cariTglKematian.empty()) || (cariTglLahir.empty() && cariTglKematian.empty()))
    {
        cout << "Anda harus megisi salah satu antara tanggal lahir atau tanggal kematian jenazah." << endl;
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
        bool cocokNama = dataPemakaman[i].namaJenazah.find(cariNama) != string::npos;
        bool cocokTanggal = false;

        if (!cariTglLahir.empty())
        {
            cocokTanggal = dataPemakaman[i].tanggalLahir == cariTglLahir;
        }
        else if (!cariTglKematian.empty())
        {
            cocokTanggal = dataPemakaman[i].tanggalKematian == cariTglKematian;
        }

        if (cocokNama && cocokTanggal)
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
    new_node -> namaKeluarga = nama;
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
        cout << i << ") Nama Keluarga    : " << current->namaKeluarga << endl;
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

    login();
}

