#include <iostream>
#include <fstream>
using namespace std;

// Struktur untuk menyimpan data KTP
struct KTP {
    string nik;
    string nama;
    string tempat_lahir;
    string tanggal_lahir;
    string jenis_kelamin;
    string alamat;
    string rt_rw;
    string kel_desa;
    string kecamatan;
    string agama;
    string status_perkawinan;
    string pekerjaan;
    string kewarganegaraan;
};

// Struktur untuk menyimpan data barang
struct Barang {
    string kode;
    string tanggal_masuk;
};

// Struktur untuk menyimpan data pembeli
struct Pembeli {
    string ktp;
    string waktu;
    string kode_item;
};

// Node untuk linked list stack (LIFO) - Barang
struct NodeBarang {
    Barang data;
    NodeBarang* next;
    NodeBarang(Barang b) : data(b), next(nullptr) {}
};

// Node untuk linked list queue (FIFO) - Pembeli
struct NodePembeli {
    Pembeli data;
    NodePembeli* next;
    NodePembeli(Pembeli p) : data(p), next(nullptr) {}
};

// Node untuk KTP
struct NodeKTP {
    KTP data;
    NodeKTP* next;
};

// Kelas untuk manajemen barang (LIFO)
class BarangManager {
private:
    NodeBarang* top;
    int count;

public:
    BarangManager() : top(nullptr), count(0) {}

    void tambahBarang(Barang b) {
        NodeBarang* newNode = new NodeBarang(b);
        newNode->next = top;
        top = newNode;
        count++;
    }

    Barang ambilBarang() {
        if (top == nullptr) {
            cout << "Gudang kosong!" << endl;
            return {"", ""};
        }
        NodeBarang* temp = top;
        Barang barang = temp->data;
        top = top->next;
        delete temp;
        count--;
        return barang;
    }

    void cetakDaftar() {
        if (top == nullptr) {
            cout << "Gudang kosong!" << endl;
            return;
        }

        cout << "\nDaftar Barang di Gudang:" << endl;
        NodeBarang* current = top;
        int nomor = 1;
        while (current != nullptr) {
            cout << nomor << ". Kode Item: " << current->data.kode 
                 << ", Tanggal Masuk: " << current->data.tanggal_masuk << endl;
            current = current->next;
            nomor++;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Kelas untuk manajemen pembeli (FIFO)
class PembeliManager {
private:
    NodePembeli *front, *rear;

public:
    PembeliManager() : front(nullptr), rear(nullptr) {}

    void tambahPembeli(Pembeli p) {
        NodePembeli* newNode = new NodePembeli(p);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    Pembeli prosesTransaksi() {
        if (front == nullptr) {
            cout << "Tidak ada pembeli dalam antrian!" << endl;
            return {"", "", ""};
        }
        NodePembeli* temp = front;
        Pembeli pembeli = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return pembeli;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// Fungsi untuk input data KTP
void inputKTP(KTP &ktp) {
    cout << "=== Input KTP ===" << endl;
    cout << "NIK: ";
    cin >> ktp.nik;
    cout << "Nama: ";
    cin.ignore();
    getline(cin, ktp.nama);
    cout << "Tempat Lahir: ";
    getline(cin, ktp.tempat_lahir);
    cout << "Tanggal Lahir (yyyy-mm-dd): ";
    getline(cin, ktp.tanggal_lahir);
    cout << "Jenis Kelamin: ";
    getline(cin, ktp.jenis_kelamin);
    cout << "Alamat: ";
    getline(cin, ktp.alamat);
    cout << "RT/RW: ";
    getline(cin, ktp.rt_rw);
    cout << "Kel/Desa: ";
    getline(cin, ktp.kel_desa);
    cout << "Kecamatan: ";
    getline(cin, ktp.kecamatan);
    cout << "Agama: ";
    getline(cin, ktp.agama);
    cout << "Status Perkawinan: ";
    getline(cin, ktp.status_perkawinan);
    cout << "Pekerjaan: ";
    getline(cin, ktp.pekerjaan);
    cout << "Kewarganegaraan: ";
    getline(cin, ktp.kewarganegaraan);
}

// Fungsi untuk konfirmasi input KTP
void konfirmasiKTP(KTP &ktp) {
    cout << "\n=== KARTU TANDA PENDUDUK ===" << endl;
    cout << "NIK: " << ktp.nik << endl;
    cout << "Nama: " << ktp.nama << endl;
    cout << "Tempat/Tgl Lahir: " << ktp.tempat_lahir << ", " << ktp.tanggal_lahir << endl;
    cout << "Jenis Kelamin: " << ktp.jenis_kelamin << endl;
    cout << "Alamat: " << ktp.alamat << endl;
    cout << "RT/RW: " << ktp.rt_rw << endl;
    cout << "Kel/Desa: " << ktp.kel_desa << endl;
    cout << "Kecamatan: " << ktp.kecamatan << endl;
    cout << "Agama: " << ktp.agama << endl;
    cout << "Status Perkawinan: " << ktp.status_perkawinan << endl;
    cout << "Pekerjaan: " << ktp.pekerjaan << endl;
    cout << "Kewarganegaraan: " << ktp.kewarganegaraan << endl;
    cout << "============================" << endl;
}

// Fungsi untuk menyimpan data KTP ke file
void simpanDataKTP(KTP &ktp) {
    ofstream outFile("data_ktp.txt", ios::app);
    outFile << ktp.nik << endl;
    outFile << ktp.nama << endl;
    outFile << ktp.tempat_lahir << endl;
    outFile << ktp.tanggal_lahir << endl;
    outFile << ktp.jenis_kelamin << endl;
    outFile << ktp.alamat << endl;
    outFile << ktp.rt_rw << endl;
    outFile << ktp.kel_desa << endl;
    outFile << ktp.kecamatan << endl;
    outFile << ktp.agama << endl;
    outFile << ktp.status_perkawinan << endl;
    outFile << ktp.pekerjaan << endl;
    outFile << ktp.kewarganegaraan << endl;
    outFile << "----------------------------" << endl;
    outFile.close();
}

// Fungsi untuk cek NIK terdaftar dalam file
bool cekNikTerdaftar(const string &nik) {
    ifstream inFile("data_ktp.txt");
    string line;
    while (getline(inFile, line)) {
        if (line == nik) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

// Fungsi menu untuk entri barang (LIFO)
void entriBarang(BarangManager& bm) {
    char lanjut;
    do {
        Barang barang;
        cout << "\nMasukkan kode item barang: ";
        cin >> barang.kode;
        cout << "Masukkan tanggal masuk (yyyy-mm-dd): ";
        cin >> barang.tanggal_masuk;

        bm.tambahBarang(barang);

        cout << "\nBarang berhasil ditambahkan!" << endl;
        cout << "Kode Item: " << barang.kode << ", Tanggal Masuk: " << barang.tanggal_masuk << endl;

        cout << "Apakah Anda ingin menambahkan barang lagi? (Y/N): ";
        cin >> lanjut;
    } while (lanjut == 'Y' || lanjut == 'y');
}

// Fungsi menu untuk catat pembeli
void catatPembeli(PembeliManager& pm) {
    char lanjut;
    do {
        Pembeli pembeli;
        cout << "\nMasukkan KTP pembeli: ";
        cin >> pembeli.ktp;
        cout << "Masukkan waktu kedatangan (hh:mm): ";
        cin >> pembeli.waktu;
        cout << "Masukkan kode item yang dibeli: ";
        cin >> pembeli.kode_item;

        pm.tambahPembeli(pembeli);

        cout << "\nPembeli tercatat!" << endl;
        cout << "KTP: " << pembeli.ktp << ", Waktu Kedatangan: " << pembeli.waktu 
             << ", Kode Item: " << pembeli.kode_item << endl;

        cout << "Apakah Anda ingin mencatat pembeli lain? (Y/N): ";
        cin >> lanjut;
    } while (lanjut == 'Y' || lanjut == 'y');
}

// Fungsi menu untuk jual barang (FIFO)
void jualBarang(PembeliManager& pm, BarangManager& bm) {
    char lanjut;
    do {
        if (pm.isEmpty()) {
            cout << "Tidak ada pembeli dalam antrian!" << endl;
            return;
        }
        if (bm.isEmpty()) {
            cout << "Gudang kosong!" << endl;
            return;
        }

        Pembeli pembeli = pm.prosesTransaksi();
        Barang barang = bm.ambilBarang();

        cout << "\nMetode FIFO dipilih." << endl;
        cout << "Pembeli dengan KTP: " << pembeli.ktp << " membeli barang " << pembeli.kode_item << endl;
        cout << "Barang yang dijual: " << barang.kode << ", Tanggal Masuk: " << barang.tanggal_masuk << endl;

        cout << "Apakah Anda ingin melanjutkan transaksi lain? (Y/N): ";
        cin >> lanjut;
    } while (lanjut == 'Y' || lanjut == 'y');
}

// Fungsi menu utama
void tampilkanMenu(BarangManager& bm, PembeliManager& pm) {
    bool sessionActive = true;
    while (sessionActive) {
        cout << "\n===============================" << endl;
        cout << "  Selamat datang di Tugas Proyek!    " << endl;
        cout << "===============================" << endl;
        cout << " [1] Entri Item Barang (Metode LIFO)" << endl;
        cout << " [2] Catat Pembeli               " << endl;
        cout << " [3] Jual Item Barang (Metode FIFO)" << endl;
        cout << " [4] Cetak Daftar Barang          " << endl;
        cout << " [5] Logout                       " << endl;
        cout << "===============================" << endl;
        cout << " Pilih menu [1-5]: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                entriBarang(bm);
                break;
            case 2:
                catatPembeli(pm);
                break;
            case 3:
                jualBarang(pm, bm);
                break;
            case 4:
                bm.cetakDaftar();
                char lanjut;
                cout << "\nApakah Anda ingin mencetak daftar barang lagi? (Y/N): ";
                cin >> lanjut;
                break;
            case 5:
                cout << "Terima kasih! Anda telah logout." << endl;
                cout << "Sampai jumpa kembali." << endl;
                sessionActive = false;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    }
}

int main() {
    // Inisialisasi manager
    BarangManager barangManager;
    PembeliManager pembeliManager;

    // Input data KTP admin
    int jumlahKTP;
    cout << "Selamat datang! Data admin kosong, silakan isi data KTP Anda." << endl;
    cout << "Berapa jumlah KTP yang ingin Anda masukkan? (Maksimal 3): ";
    cin >> jumlahKTP;

    if (jumlahKTP > 3) {
        cout << "Jumlah KTP melebihi batas maksimal!" << endl;
        return 1;
    }

    // Proses input KTP
    for (int i = 0; i < jumlahKTP; i++) {
        KTP ktp;
        inputKTP(ktp);
        konfirmasiKTP(ktp);
        simpanDataKTP(ktp);
    }

    // Menu Login
    string nik;
    bool nikValid = false;
    while (!nikValid) {
        cout << "\n==== LOGIN ==== " << endl;
        cout << "Masukkan NIK yang terdaftar untuk login: ";
        cin >> nik;
        if (cekNikTerdaftar(nik)) {
            nikValid = true;
            cout << "Login berhasil! Selamat datang, " << nik << endl;
        } else {
            cout << "NIK tidak terdaftar, silakan coba lagi." << endl;
        }
    }

    // Masuk ke menu utama
    tampilkanMenu(barangManager, pembeliManager);

    return 0;
}
