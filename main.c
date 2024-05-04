#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUKU 100
#define MAX_USER 2
#define MAX_BUKU_DIPINJAM 5
#define FILENAME "data_perpustakaan.txt"

// Struktur untuk menyimpan informasi buku
struct Buku
{
    unsigned int id;
    char judul[100];
    char penulis[100];
    char penerbit[100];
    unsigned int jumlah_halaman;
    unsigned int tahun_terbit;
    unsigned int jumlah_tersedia;
};

// Struktur untuk menyimpan informasi pengguna
struct Pengguna
{
    char username[100];
    char password[100];
    int isAdmin;
};

// Deklarasi fungsi
void login();
void menuAdmin();
void menuUser();
void tambahBuku();
void lihatBuku();
void pinjamBuku();
void lihatBukuDipinjam();
void kembalikanBuku();
void hapusBuku();  
void editBuku();  
void simpanDataBuku();
void bacaDataBuku();
void clearBuffer();

// struktur akun login
struct Buku buku[MAX_BUKU];
struct Pengguna user[MAX_USER] = {{"admin", "reyan", 1}, {"user", "reyan", 0}};
int jumlah_buku = 0;
int jumlah_user = 2;
struct Buku buku_dipinjam[MAX_BUKU_DIPINJAM];
int jumlah_buku_dipinjam = 0;

int main()
{
    bacaDataBuku(); // Membaca data buku dari file

    login(); // Masuk ke sistem

    return 0;
}

// Fungsi untuk masuk
void login()
{
    char username[100];
    char password[100];

    printf("Selamat datang di Sistem Peminjaman Buku Perpustakaan\n");
    printf("Silakan login untuk melanjutkan.\n");

    printf("Username: ");
    scanf("%s", username);
    clearBuffer();

    printf("Password: ");
    scanf("%s", password);
    clearBuffer();

    int loggedIn = 0;
    for (int i = 0; i < jumlah_user; ++i)
    {
        if (strcmp(username, user[i].username) == 0 && strcmp(password, user[i].password) == 0)
        {
            printf("Login berhasil!\n");
            if (user[i].isAdmin)
            {
                menuAdmin();
            }
            else
            {
                menuUser();
            }
            loggedIn = 1;
            break;
        }
    }

    if (!loggedIn)
    {
        printf("Login gagal. Silakan coba lagi.\n");
        login();
    }
}

// Fungsi untuk menampilkan menu admin
void menuAdmin()
{
    int choice;
    while (1)
    {
        printf("\nMenu Admin:\n");
        printf("1. Tambah Buku\n");
        printf("2. Lihat Buku\n");
        printf("3. Hapus Buku\n");
        printf("4. Edit Buku\n");
        printf("5. Logout\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice)
        {
        case 1:
            tambahBuku();
            break;
        case 2:
            lihatBuku();
            break;
        case 3:
            hapusBuku(); // Panggil fungsi hapus buku
            break;
        case 4:
            editBuku(); // Panggil fungsi edit buku
            break;
        case 5:
            login();
            return; // Keluar dari fungsi menuAdmin() setelah logout
        default:
            printf("Pilihan tidak valid.\n");
        }
    }
}

// Fungsi untuk menampilkan menu user
void menuUser()
{
    int choice;
    while (1)
    {
        printf("\nMenu User:\n");
        printf("1. Lihat Buku\n");
        printf("2. Pinjam Buku\n");
        printf("3. Lihat Buku yang Dipinjam\n");
        printf("4. Kembalikan Buku\n");
        printf("5. Logout\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice)
        {
        case 1:
            lihatBuku();
            break;
        case 2:
            pinjamBuku();
            break;
        case 3:
            lihatBukuDipinjam();
            break;
        case 4:
            kembalikanBuku();
            break;
        case 5:
            login();
            return; // Keluar dari fungsi menuUser() setelah logout
        default:
            printf("Pilihan tidak valid.\n");
        }
    }
}

// Fungsi untuk menambahkan buku baru
void tambahBuku()
{
    printf("\nTambah Buku\n");
    if (jumlah_buku >= MAX_BUKU)
    {
        printf("Maaf, batas maksimal jumlah buku telah tercapai.\n");
        return;
    }

    printf("Masukkan informasi buku:\n");
    printf("Id Buku: ");
    scanf("%u", &buku[jumlah_buku].id);
    clearBuffer();

    printf("Judul: ");
    fgets(buku[jumlah_buku].judul, sizeof(buku[jumlah_buku].judul), stdin);
    strtok(buku[jumlah_buku].judul, "\n");

    printf("Penulis: ");
    fgets(buku[jumlah_buku].penulis, sizeof(buku[jumlah_buku].penulis), stdin);
    strtok(buku[jumlah_buku].penulis, "\n");

    printf("Penerbit: ");
    fgets(buku[jumlah_buku].penerbit, sizeof(buku[jumlah_buku].penerbit), stdin);
    strtok(buku[jumlah_buku].penerbit, "\n");

    printf("Jumlah Halaman: ");
    scanf("%u", &buku[jumlah_buku].jumlah_halaman);

    printf("Tahun Terbit: ");
    scanf("%u", &buku[jumlah_buku].tahun_terbit);

    printf("Jumlah Tersedia: ");
    scanf("%u", &buku[jumlah_buku].jumlah_tersedia);

    jumlah_buku++;
    printf("Buku berhasil ditambahkan.\n");

    simpanDataBuku(); // Menyimpan data ke file
}

// Fungsi untuk melihat daftar buku
void lihatBuku()
{
    printf("\nDaftar Buku\n");
    for (int i = 0; i < jumlah_buku; ++i)
    {
        int isDipinjam = 0;
        for (int j = 0; j < jumlah_buku_dipinjam; ++j)
        {
            if (buku[i].id == buku_dipinjam[j].id)
            {
                isDipinjam = 1;
                break;
            }
        }
        if (!isDipinjam)
        {
            printf("Id Buku: %u\n", buku[i].id);
            printf("Judul: %s\n", buku[i].judul);
            printf("Penulis: %s\n", buku[i].penulis);
            printf("Penerbit: %s\n", buku[i].penerbit);
            printf("Jumlah Halaman: %u\n", buku[i].jumlah_halaman);
            printf("Tahun Terbit: %u\n", buku[i].tahun_terbit);
            printf("Jumlah Tersedia: %u\n\n", buku[i].jumlah_tersedia);
        }
    }
}

// Fungsi untuk melakukan peminjaman buku
void pinjamBuku()
{
    printf("\nPinjam Buku\n");

    if (jumlah_buku_dipinjam >= MAX_BUKU_DIPINJAM)
    {
        printf("Maaf, Anda telah mencapai batas maksimal peminjaman buku.\n");
        return;
    }

    int id_buku;
    printf("Masukkan ID buku yang ingin dipinjam: ");
    scanf("%d", &id_buku);
    clearBuffer();

    // Cek apakah buku tersedia dan masih bisa dipinjam
    int index_buku = -1;
    for (int i = 0; i < jumlah_buku; ++i)
    {
        if (buku[i].id == id_buku)
        {
            if (buku[i].jumlah_tersedia > 0)
            {
                index_buku = i;
                break;
            }
            else
            {
                printf("Maaf, buku ini tidak tersedia saat ini.\n");
                return;
            }
        }
    }

    if (index_buku == -1)
    {
        printf("Maaf, buku dengan ID tersebut tidak ditemukan.\n");
        return;
    }

    // Tambahkan buku yang dipinjam ke dalam list buku yang sedang dipinjam
    buku_dipinjam[jumlah_buku_dipinjam++] = buku[index_buku];
    buku[index_buku].jumlah_tersedia--;
    printf("Buku berhasil dipinjam.\n");
}

// Fungsi untuk melihat daftar buku yang dipinjam
void lihatBukuDipinjam()
{
    printf("\nBuku yang Dipinjam\n");
    if (jumlah_buku_dipinjam == 0)
    {
        printf("Anda belum meminjam buku apapun.\n");
        return;
    }

    for (int i = 0; i < jumlah_buku_dipinjam; ++i)
    {
        printf("Id Buku: %u\n", buku_dipinjam[i].id);
        printf("Judul: %s\n", buku_dipinjam[i].judul);
        printf("Penulis: %s\n", buku_dipinjam[i].penulis);
        printf("Penerbit: %s\n", buku_dipinjam[i].penerbit);
        printf("Jumlah Halaman: %u\n", buku_dipinjam[i].jumlah_halaman);
        printf("Tahun Terbit: %u\n", buku_dipinjam[i].tahun_terbit);
        printf("\n");
    }
}

// Fungsi untuk mengembalikan buku
void kembalikanBuku()
{
    printf("\nKembalikan Buku\n");
    if (jumlah_buku_dipinjam == 0)
    {
        printf("Anda belum meminjam buku apapun.\n");
        return;
    }

    int id_buku;
    printf("Masukkan ID buku yang ingin dikembalikan: ");
    scanf("%d", &id_buku);
    clearBuffer();

    int index_buku = -1;
    for (int i = 0; i < jumlah_buku_dipinjam; ++i)
    {
        if (buku_dipinjam[i].id == id_buku)
        {
            index_buku = i;
            break;
        }
    }

    if (index_buku == -1)
    {
        printf("Maaf, buku dengan ID tersebut tidak ditemukan dalam daftar buku yang Anda pinjam.\n");
        return;
    }

    // Kembalikan buku ke daftar buku yang tersedia dan hapus dari daftar buku yang dipinjam
    buku[index_buku].jumlah_tersedia++;
    for (int i = index_buku; i < jumlah_buku_dipinjam - 1; ++i)
    {
        buku_dipinjam[i] = buku_dipinjam[i + 1];
    }
    jumlah_buku_dipinjam--;
    printf("Terima kasih, buku telah dikembalikan.\n");

    // Setelah pengembalian buku, tampilkan menu kembali
    menuUser();
}

// Fungsi untuk menghapus buku
void hapusBuku()
{
    printf("\nHapus Buku\n");
    int id_buku;
    printf("Masukkan ID buku yang ingin dihapus: ");
    scanf("%d", &id_buku);
    clearBuffer();

    int index_buku = -1;
    for (int i = 0; i < jumlah_buku; ++i)
    {
        if (buku[i].id == id_buku)
        {
            index_buku = i;
            break;
        }
    }

    if (index_buku == -1)
    {
        printf("Maaf, buku dengan ID tersebut tidak ditemukan.\n");
        return;
    }

    // Geser array untuk menghapus buku
    for (int i = index_buku; i < jumlah_buku - 1; ++i)
    {
        buku[i] = buku[i + 1];
    }
    jumlah_buku--;

    printf("Buku berhasil dihapus.\n");

    // Simpan perubahan ke file
    simpanDataBuku();
}

// Fungsi untuk mengedit buku
void editBuku()
{
    printf("\nEdit Buku\n");
    int id_buku;
    printf("Masukkan ID buku yang ingin diedit: ");
    scanf("%d", &id_buku);
    clearBuffer();

    int index_buku = -1;
    for (int i = 0; i < jumlah_buku; ++i)
    {
        if (buku[i].id == id_buku)
        {
            index_buku = i;
            break;
        }
    }

    if (index_buku == -1)
    {
        printf("Maaf, buku dengan ID tersebut tidak ditemukan.\n");
        return;
    }

    // Memperbarui informasi buku
    printf("Masukkan informasi buku yang baru:\n");
    printf("Judul: ");
    fgets(buku[index_buku].judul, sizeof(buku[index_buku].judul), stdin);
    strtok(buku[index_buku].judul, "\n");

    printf("Penulis: ");
    fgets(buku[index_buku].penulis, sizeof(buku[index_buku].penulis), stdin);
    strtok(buku[index_buku].penulis, "\n");

    printf("Penerbit: ");
    fgets(buku[index_buku].penerbit, sizeof(buku[index_buku].penerbit), stdin);
    strtok(buku[index_buku].penerbit, "\n");

    printf("Jumlah Halaman: ");
    scanf("%u", &buku[index_buku].jumlah_halaman);

    printf("Tahun Terbit: ");
    scanf("%u", &buku[index_buku].tahun_terbit);

    printf("Jumlah Tersedia: ");
    scanf("%u", &buku[index_buku].jumlah_tersedia);

    printf("Buku berhasil diupdate.\n");

    // Simpan perubahan ke file
    simpanDataBuku();
}

// Fungsi untuk menyimpan data buku ke file
void simpanDataBuku()
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk penyimpanan data buku.\n");
        return;
    }

    for (int i = 0; i < jumlah_buku; ++i)
    {
        fprintf(file, "Id Buku: %u\n", buku[i].id);
        fprintf(file, "Judul: %s\n", buku[i].judul);
        fprintf(file, "Penulis: %s\n", buku[i].penulis);
        fprintf(file, "Penerbit: %s\n", buku[i].penerbit);
        fprintf(file, "Jumlah Halaman: %u\n", buku[i].jumlah_halaman);
        fprintf(file, "Tahun Terbit: %u\n", buku[i].tahun_terbit);
        fprintf(file, "Jumlah Tersedia: %u\n", buku[i].jumlah_tersedia);
    }

    fclose(file);
}

// Fungsi untuk membaca data buku dari file
void bacaDataBuku()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Gagal membaca file data buku.\n");
        return;
    }

    while (!feof(file) && jumlah_buku < MAX_BUKU)
    {
        fscanf(file, "Id Buku: %u\n", &buku[jumlah_buku].id);
        fgets(buku[jumlah_buku].judul, sizeof(buku[jumlah_buku].judul), file);
        strtok(buku[jumlah_buku].judul, "\n");
        fgets(buku[jumlah_buku].penulis, sizeof(buku[jumlah_buku].penulis), file);
        strtok(buku[jumlah_buku].penulis, "\n");
        fgets(buku[jumlah_buku].penerbit, sizeof(buku[jumlah_buku].penerbit), file);
        strtok(buku[jumlah_buku].penerbit, "\n");
        fscanf(file, "Jumlah Halaman: %u\n", &buku[jumlah_buku].jumlah_halaman);
        fscanf(file, "Tahun Terbit: %u\n", &buku[jumlah_buku].tahun_terbit);
        fscanf(file, "Jumlah Tersedia: %u\n", &buku[jumlah_buku].jumlah_tersedia);
        jumlah_buku++;
    }

    fclose(file);
}

// Fungsi untuk membersihkan buffer input
void clearBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
