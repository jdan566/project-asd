#include <iostream>
#include <string>
using namespace std;

struct Barang {
    int id;
    string nama;
    int jumlah;
    Barang* left;
    Barang* right;
};

// Fungsi membuat node baru
Barang* createNode(int id, string nama, int jumlah) {
    Barang* newNode = new Barang();
    newNode->id = id;
    newNode->nama = nama;
    newNode->jumlah = jumlah;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Fungsi menambahkan node
Barang* insert(Barang* root, int id, string nama, int jumlah) {
    if (root == nullptr)
        return createNode(id, nama, jumlah);
    if (id < root->id)
        root->left = insert(root->left, id, nama, jumlah);
    else if (id > root->id)
        root->right = insert(root->right, id, nama, jumlah);
    else
        cout << "ID sudah digunakan!\n";
    return root;
}

// Fungsi mencari data
Barang* search(Barang* root, int id) {
    if (root == nullptr || root->id == id)
        return root;
    if (id < root->id)
        return search(root->left, id);
    return search(root->right, id);
}

// Fungsi menampilkan semua data (in-order)
void tampilkanData(Barang* root) {
    if (root != nullptr) {
        tampilkanData(root->left);
        cout << "ID: " << root->id << ", Nama: " << root->nama << ", Jumlah: " << root->jumlah << endl;
        tampilkanData(root->right);
    }
}

// Fungsi mencari node terkecil (untuk delete)
Barang* minValueNode(Barang* node) {
    Barang* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Fungsi menghapus data
Barang* deleteNode(Barang* root, int id) {
    if (root == nullptr) return root;
    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        // Node dengan satu anak atau tidak ada
        if (root->left == nullptr) {
            Barang* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Barang* temp = root->left;
            delete root;
            return temp;
        }
        // Node dengan dua anak
        Barang* temp = minValueNode(root->right);
        root->id = temp->id;
        root->nama = temp->nama;
        root->jumlah = temp->jumlah;
        root->right = deleteNode(root->right, temp->id);
    }
    return root;
}

// Fungsi memperbarui data
void updateData(Barang* root, int id) {
    Barang* node = search(root, id);
    if (node == nullptr) {
        cout << "Data tidak ditemukan.\n";
        return;
    }
    cout << "Masukkan nama baru: ";
    cin.ignore();
    getline(cin, node->nama);
    cout << "Masukkan jumlah baru: ";
    cin >> node->jumlah;
    cout << "Data berhasil diperbarui.\n";
}

// Menu utama
int main() {
    Barang* root = nullptr;
    int pilihan, id, jumlah;
    string nama;

    do {
        cout << "\n=== Menu Manajemen Inventaris Barang (BST) ===\n";
        cout << "1. Tambah Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Perbarui Data\n";
        cout << "4. Hapus Data\n";
        cout << "5. Cari Data\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Barang: ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Nama Barang: ";
                getline(cin, nama);
                cout << "Masukkan Jumlah: ";
                cin >> jumlah;
                root = insert(root, id, nama, jumlah);
                break;
            case 2:
                cout << "\nData Inventaris:\n";
                tampilkanData(root);
                break;
            case 3:
                cout << "Masukkan ID yang akan diperbarui: ";
                cin >> id;
                updateData(root, id);
                break;
            case 4:
                cout << "Masukkan ID yang akan dihapus: ";
                cin >> id;
                root = deleteNode(root, id);
                cout << "Data berhasil dihapus (jika ditemukan).\n";
                break;
            case 5:
                cout << "Masukkan ID yang dicari: ";
                cin >> id;
                {
                    Barang* hasil = search(root, id);
                    if (hasil != nullptr) {
                        cout << "Ditemukan - ID: " << hasil->id << ", Nama: " << hasil->nama << ", Jumlah: " << hasil->jumlah << endl;
                    } else {
                        cout << "Data tidak ditemukan.\n";
                    }
                }
                break;
            case 6:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}