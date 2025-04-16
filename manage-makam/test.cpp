#include <iostream>
#include <string>
using namespace std;

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

NodePemakaman* headPemakaman = NULL;
int countPemakaman = 1;

int main()
{
    tampilWelcome();
}

void tampilWelcome()
{
    int pilihan;

    cout << "======================================" << endl;
    cout << "  Selamat Datang di Sistem Pemakaman  " << endl;
    cout << "======================================" << endl;
    cout << "1) Masuk sebagai Admin" << endl;
    cout << "2) Masuk sebagai Pengguna" << endl;
    cout << "3) Keluar" << endl;
    cout << "======================================" << endl;

    while (true)
    {
        cout << "Pilih opsi disini (1/2/3): ";
        cin >> pilihan;

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
            cout << "Terimakasih telah menggunakan aplikasi ini." << endl;
            break;
        }
        else
        {
            cout << "Pilihan tidak tersedia. Silakan ulangi." << endl;
        }
    }
}

void menuAdmin()
{
    int pilihan;

    cout << "==== Menu Admin Sistem Pemakaman ====" << endl;
    cout << "1) Tambah Data Pemakaman" << endl;
    cout << "2) Lihat Data Pemakaman" << endl;
    cout << "3) Hapus Data Pemakaman" << endl;
    cout << "4) Kelola Lahan Pemakaman" << endl;
    cout << "5) Laporan Ketersediaan Lahan" << endl;
    cout << "6) Kelola Katalog Desain Makam" << endl;
    cout << "7) Lihat Permintaan Pembersihan" << endl;
    cout << "8) Kembali ke Menu Awal" << endl;
    cout << "=====================================" << endl;
    
    while (true)
    {
        cout << "Pilih opsi disini (1/2/3/4): ";
        cin >> pilihan;

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
            kelolaLahan();
        }
        else if (pilihan == 5)
        {
            laporanKetersediaan();
        }
        else if (pilihan == 6)
        {
            kelolaKatalogDesain();
        }
        else if (pilihan == 7)
        {
            lihatPermintaanPembersihan();
        }
        else if (pilihan == 8)
        {
            tampilWelcome();
        }
        else
        {
            cout << "Opsi tidak tersedia. Silakan Ulangi." << endl;
        }
    }
}

void menuPengguna()
{
    int pilihan;

    cout << "Menu Pengguna Sistem Pemakaman" << endl;
    cout << "1) Cari Data Pemakaman" << endl;
    cout << "2) Lihat Katalog Desain Makam" << endl;
    cout << "3) Lihat Ketersediaan Lahan" << endl;
    cout << "4) Ajukan Permintaan Pembersihan" << endl;
    cout << "5) Kembali ke Menu Utama" << endl;

    while (true)
    {
        cout << "Pilih opsi disini (1/2/3/4/5): ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            cariDataPemakaman();
        }
        else if (pilihan == 2)
        {
            lihatKatalogDesainMakam();
        }
        else if (pilihan == 3)
        {
            lihatKetersediaan();
        }
        else if (pilihan == 4)
        {
            ajukanPembersihan();
        }
        else if (pilihan == 5)
        {
            tampilWelcome();
        }
        else
        {
            cout << "Opsi tidak tersedia. Silakan Ulangi." << endl;
        }
    }
}

void tambahDataPemakaman()
{
    string nama, tglLahir, tglKematian, lokasi, pj;

    cout << "\n== Tambah Data Pemakaman ==" << endl;
    cout << "Nama Jenazah        : "; getline(cin, nama);
    cout << "Tanggal Lahir       : "; getline(cin, tglLahir);
    cout << "Tanggal Kematian    : "; getline(cin, tglKematian);
    cout << "Lokasi Makam        : "; getline(cin, lokasi);
    cout << "Penanggung Jawab    : "; getline(cin, pj);

    NodePemakaman* new_node;

    new_node = new NodePemakaman();
    new_node -> namaJenazah = nama;
    new_node -> tanggalLahir = tglLahir;
    new_node -> tanggalKematian = tglKematian;
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
        NodePemakaman* current;
        current = headPemakaman;
        while (current->next != NULL)
        {
            current = current -> next;
        }
        current -> next = new_node;
    }

    cout << "Data pemakaman berhasil ditambahkan." << endl;
    countPemakaman++;
}

void lihatDataPemakaman()
{
    if (headPemakaman == NULL)
    {
        cout << "Belum ada data pemakaman disini." << endl;
        return;
    }

    NodePemakaman* current = headPemakaman;
    int i = 1;

    while (current != NULL)
    {
        cout << "================================================" << endl;
        cout << "Data ke-" << i++ << endl;
        cout << "Nama Jenazah        : " << current -> namaJenazah << endl;
        cout << "Tanggal Lahir       : " << current -> tanggalLahir << endl;
        cout << "Tanggal Kematian    : " << current -> tanggalKematian << endl;
        cout << "Lokasi Makam        : " << current -> lokasi << endl;
        cout << "Penanggung Jawab    : " << current -> penanggungJawab << endl;
        cout << "Status              : " << (current -> statusTerisi ? "Terisi" : "Kosong") << endl;
        cout << "================================================" << endl;
    }
}


bool hapusDataPemakaman(int data)
{
    if (headPemakaman == NULL || data < 1 || data > countPemakaman)
    {
        return false
    }

    NodePemakaman* temp = headPemakaman;
    if (index == 1)
    {
        headPemakaman = temp->next;
        delete temp;
        countPemakaman--;
        return true;
    }

    NodePemakaman* current = headPemakaman;
    for (int i = 1; i < data - 1; i++)
    {
        current = current -> next;
    }

    temp = current -> next;
    current -> next = temp -> next;
    delete temp;
    countPemakaman--;
    return true;
}

void cariDataPemakaman()
{
    string nama, blok;
    cout << "Masukkan Nama Jenazah disini (boleh kosong): ";
    getline(cin, nama);
    cout << "Masukkan Lokasi/Blok Makam (boleh kosong): ";
    getline(cin, blok);

    NodePemakaman* current;
    current = headPemakaman;
    bool ditemukan = false;

    while (current != NULL)
    {
        bool cariNama = nama.empty() || current -> namaJenazah.find(nama) != string::npos;
        bool cariBlok = blok.empty() || current -> lokasi.find(blok) != string::npos;

        if (cariNama && cariBlok)
        {
            ditemukan = true;
            cout << "Data Ditemukan" << endl;
            cout << "Nama Jenazah        : " << current -> namaJenazah << endl;
            cout << "Tanggal Lahir       : " << current -> tanggalLahir << endl;
            cout << "Tanggal Kematian    : " << current -> tanggalKematian << endl;
            cout << "Lokasi Makam        : " << current -> lokasi << endl;
            cout << "Penanggung Jawab    : " << current -> penanggungJawab << endl;
        }
    }
}