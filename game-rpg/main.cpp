#include "header.h"
using namespace std;

const int ukuran = 5;
struct Antrian
{
    int top;
    string isi[ukuran];
} antrian;

void createAntrian()
{
    antrian.top = 0;
}

bool isEmpty()
{
    if (antrian.top == 0)
    {
        return true;
    }
    return false;
}

bool isFull()
{
    if (antrian.top >= ukuran)
    {
        return true;
    }
    return false;
}

void insertAntrian(string data)
{
    if (isFull())
    {
        cout << data << "tidak dapat ditambahkan karena tim sudah penuh" << endl;
    }
    else
    {
        antrian.isi[antrian.top] = data;
        cout << antrian.isi[antrian.top] << " berhasil masuk ke tim" << endl;
        antrian.top++;
    }
}

void deleteAntrian()
{
    if (isEmpty())
    {
        cout << "Tidak ada karakter dalam queue" << endl;
    }
    else
    {
        string pop = antrian.isi[0];
        cout << pop << " sudah keluar dari tim" << endl;

        for (int i = 1; i < antrian.top; i++)
        {
            antrian.isi[i - 1] = antrian.isi[i];
        }
        antrian.top--;
        insertAntrian(pop);
    }
}

void displayAntrian()
{
    if (isEmpty())
    {
        cout << "Menampilkan isi antrian: " << endl;
        for (int i = 0; i < antrian.top; i++)
        {
            cout << antrian.isi[i] << " berada di posisi ke-" << i << endl;
        }
    }
    else
    {
        cout << "Tidak ada karakter pada tim" << endl;
    }
}