#include <iostream>

using namespace std;

struct Kamar
{
    int NomorKamar;
    bool Tersedia;
    Kamar *next;
};

Kamar *head = nullptr;

void Login()
{
    string username, password;

    do
    {
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        if (username.empty() || password.empty())
        {
            cout << "Username dan password harus diisi." << endl;
        }
        else if (username == "admin" && password == "admin")
        {
            system("cls");
            return;
        }
        else
        {
            if (username != "admin" && password != "admin")
            {
                cout << "Username dan password salah." << endl;
            }
            else if (username != "admin")
            {
                cout << "Username salah." << endl;
            }
            else
            {
                cout << "Password salah." << endl;
            }
        }
    } while (true);
}

void Menu()
{
    cout << "=== Sistem Reservasi Hotel ===" << endl;
    cout << "1. Lihat Daftar Kamar Tersedia" << endl;
    cout << "2. Reservasi Kamar" << endl;
    cout << "3. Batalkan Reservasi" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih opsi: ";
}

void KamarTersedia()
{
    system("cls");
    if (head == nullptr)
    {
        cout << "Belum ada kamar yang tersedia." << endl;
        return;
    }

    cout << "Daftar Kamar Tersedia:" << endl;
    Kamar *current = head;

    while (current != nullptr)
    {
        if (current->Tersedia)
        {
            cout << "Kamar " << current->NomorKamar << endl;
        }

        current = current->next;
    }
    cout << endl
         << "Tekan enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

// fungsi ini buat nampilin kamar yang tersedia ke fungsi kamar tersedia
void addKamar(int NomorKamar)
{
    Kamar *newKamar = new Kamar;
    newKamar->NomorKamar = NomorKamar;
    newKamar->Tersedia = true;
    newKamar->next = nullptr;

    if (head == nullptr)
    {
        head = newKamar;
    }
    else
    {
        Kamar *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newKamar;
    }
}

// fungsi ini buat ngasih data kamar ke fungsi reservasi
Kamar *TemukanKamar(int NomorKamar)
{
    Kamar *current = head;

    while (current != nullptr)
    {
        if (current->NomorKamar == NomorKamar)
        {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

void Reservasi()
{
    int NomorKamar;
    string WaktuReservasi;
    string jawaban;

    do {
        system("cls");
        cout << "Masukkan nomor kamar yang ingin dipesan: ";
        cin >> NomorKamar;
        cout << "Masukkan waktu reservasi (hari apa): ";
        cin >> WaktuReservasi;

        Kamar *kamar = TemukanKamar(NomorKamar);

        if (kamar == nullptr)
        {
            cout << "Kamar tidak ditemukan." << endl;
            cout << "Ingin memesan kamar lain atau kembali? (ya/tidak): ";
            cin >> jawaban;
            if (jawaban == "tidak") {
                cout << endl << "Tekan enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
                return;
            }
        }
        else if (!kamar->Tersedia)
        {
            cout << "Kamar sudah dipesan." << endl;
            cout << endl << "Tekan enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
            return;
        }
        else
        {
            kamar->Tersedia = false;
            cout << "Kamar " << NomorKamar << " berhasil dipesan pada " << WaktuReservasi << "." << endl;

            // Menampilkan data reservasi
            cout << "Data Reservasi:" << endl;
            cout << "Nomor Kamar: " << kamar->NomorKamar << endl;
            cout << "Waktu Reservasi: " << WaktuReservasi << endl;

            cout << endl << "Tekan enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
            return;
        }
    } while (jawaban == "ya");
}

void DataReservasi()
{
    if (head == nullptr)
    {
        cout << "Belum ada data reservasi yang disimpan." << endl;
        return;
    }

    cout << "Data Reservasi:" << endl;
    DataReservasi *current = head;
    while (current != nullptr)
    {
        Kamar *kamar = TemukanKamar(current->NomorKamar);
        if (kamar != nullptr)
        {
            cout << "Nomor Kamar: " << kamar->NomorKamar << endl;
            cout << "Waktu Reservasi: " << current->WaktuReservasi << endl;
            cout << endl;
        }
        current = current->next;
    }
}



void BatalkanKamar()
{
    int NomorKamar;
    cout << "Masukkan nomor kamar yang ingin dibatalkan reservasinya: ";
    cin >> NomorKamar;

    Kamar *Kamar = TemukanKamar(NomorKamar);

    if (Kamar == nullptr)
    {
        cout << "Kamar tidak ditemukan." << endl;
        return;
    }

    if (Kamar->Tersedia)
    {
        cout << "Kamar tidak dalam status reservasi." << endl;
        return;
    }

    Kamar->Tersedia = true;
    cout << "Reservasi kamar " << NomorKamar << " berhasil dibatalkan." << endl;
}

int main()
{
    addKamar(1);
    addKamar(3);
    addKamar(4);
    addKamar(5);
    addKamar(6);
    addKamar(7);
    addKamar(8);
    addKamar(9);

    Login();

    int pilihan;

    do
    {
        system("cls");
        Menu();
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            KamarTersedia();
            break;
        case 2:
            Reservasi();
            break;
        case 3:
            BatalkanKamar();
            break;
        case 4:
            cout << "Terima kasih telah menggunakan sistem reservasi ini🙏." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan pilih opsi yang tersedia." << endl;
            break;
        }

        cout << endl;

    } while (pilihan != 4);

    return 0;
}