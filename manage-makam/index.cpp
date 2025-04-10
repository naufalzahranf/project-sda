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