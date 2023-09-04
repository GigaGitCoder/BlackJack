#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <Windows.h>
#define random(a, b) a + rand() % (b + 1 - a);
const int FPS = 10;
using namespace std;

//keyboard
int keyboard() {
    if (_kbhit())
    {
        return _getch();
    }
}

//game
void game(int& balance) {
    //create cards massive
    char* cards = new char[52] { 'T', 'T', 'T', 'T', 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
        4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9,
        'V', 'V', 'V', 'V', 'D', 'D', 'D', 'D', 'K', 'K', 'K', 'K', 10, 10, 10, 10 };
    char* igrokRuka = new char[11] {};
    char* dilerRuka = new char[11] {};
    int igrokSumma = 0;
    int dilerSumma = 0;
    int stawka = 0;
    int kBuf = 0;
    bool isIgrokBlackJack = false;
    bool isDilerBlackJack = false;

    //shuffle cards
    for (int i = 0; i < 52; i++) {
        int j = random(0, 51);
        char temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

    //get stawka
    system("cls");
    cout << "��� ������: " << balance << endl;
    cout << "������� ������: ";
    cin >> stawka;
    while (stawka > balance) {
        cout << "������ �� ����� ���� ������ ������ �������. ������� ������: ";
        cin >> stawka;
    }
    balance -= stawka;

    //give cards
    igrokRuka[0] = cards[0];
    dilerRuka[0] = cards[1];
    igrokRuka[1] = cards[2];
    dilerRuka[1] = cards[3];

    //calculate summa
    for (int i = 0; i < 2; i++) {
        if (igrokRuka[i] == 'T') {
            igrokSumma += 11;
        }
        else if (igrokRuka[i] == 'V' || igrokRuka[i] == 'D' || igrokRuka[i] == 'K') {
            igrokSumma += 10;
        }
        else {
            igrokSumma += igrokRuka[i];
        }

        if (dilerRuka[i] == 'T') {
            dilerSumma += 11;
        }
        else if (dilerRuka[i] == 'V' || dilerRuka[i] == 'D' || dilerRuka[i] == 'K') {
            dilerSumma += 10;
        }
        else {
            dilerSumma += dilerRuka[i];
        }
    }

    //check black jack
    if (igrokSumma == 21) {
        isIgrokBlackJack = true;
    }
    if (dilerSumma == 21) {
        isDilerBlackJack = true;
    }

    //game process
    while (true) {
        system("cls");
        cout << "���� ����: ";
        for (int i = 0; i < 11; i++) {
            if (igrokRuka[i] != 0 ) {
                if (igrokRuka[i] < 11) {
                    cout << int(igrokRuka[i]) << " ";
                }
                else {
                    cout << igrokRuka[i] << " ";
                }
            }
        }
        cout << endl;
        cout << "����� ����� �����: " << igrokSumma << endl;
        if (dilerRuka[0] < 11) {
            cout << "����� ������: " << int(dilerRuka[0]) << endl;
        }
        else {
            cout << "����� ������: " << dilerRuka[0] << endl;
        }

        //check black jack
        if (isIgrokBlackJack) {
            system("cls");
            cout << "���� �����: ";
            for (int i = 0; i < 11; i++) {
                if (igrokRuka[i] != 0) {
                    if (igrokRuka[i] < 11) {
                        cout << int(igrokRuka[i]) << " ";
                    }
                    else {
                        cout << igrokRuka[i] << " ";
                    }
                }
            }
            cout << endl << "� ��� Black Jack! �� ��������!" << endl;
            balance += stawka * 2;
            Sleep(5000);
            break;
        }
        if (isDilerBlackJack) {
            system("cls");
            cout << "����� ������: ";
            for (int i = 0; i < 11; i++) {
                if (dilerRuka[i] != 0) {
                    if (dilerRuka[i] < 11) {
                        cout << int(dilerRuka[i]) << " ";
                    }
                    else {
                        cout << dilerRuka[i] << " ";
                    }
                }
            }
            cout << endl << "� ������ Black Jack. �� ���������." << endl;
            Sleep(5000);
            break;
        }

        //menu
        cout << "�������� ��������: \n1.) ����� �����\n2.) ���\n";
        int choice = 0;
        while (choice < 1 || choice > 2) {
            cin >> choice;
        }

        if (choice == 1) {
            //give card
            for (int i = 0; i < 11; i++) {
                if (igrokRuka[i] == 0) {
                    igrokRuka[i] = cards[4+kBuf];
                    cards[4+kBuf] = 0;
                    kBuf++;
                    if (igrokRuka[i] == 'T') {
                        if (igrokSumma + 11 > 21) {
                            igrokSumma += 1;
                        }
                        else {
                            igrokSumma += 11;
                        }
                    }
                    else if (igrokRuka[i] == 'V' || igrokRuka[i] == 'D' || igrokRuka[i] == 'K') {
                        igrokSumma += 10;
                    }
                    else {
                        igrokSumma += igrokRuka[i];
                    }
                    break;
                }
            }

            //check bust
            if (igrokSumma > 21) {
                system("cls");
                cout << "�� ����� � ���: " << igrokSumma << endl;
                cout << "� ��� �������. �� ���������." << endl;
                Sleep(5000);
                break;
            }
        }
        else {
            //give cards to diler
            while (dilerSumma < 17) {
                for (int i = 0; i < 11; i++) {
                    if (dilerRuka[i] == 0) {
                        dilerRuka[i] = cards[4+kBuf];
                        cards[4+kBuf] = 0;
                        kBuf++;
                        if (dilerRuka[i] == 'T') {
                            if (dilerSumma + 11 > 21) {
                                dilerSumma += 1;
                            }
                            else {
                                dilerSumma += 11;
                            }
                        }
                        else if (dilerRuka[i] == 'V' || dilerRuka[i] == 'D' || dilerRuka[i] == 'K') {
                            dilerSumma += 10;
                        }
                        else {
                            dilerSumma += dilerRuka[i];
                        }
                        break;
                    }
                }
            }

            //check winner
            if (dilerSumma > 21) {
                cout << "�� ����� � ���: " << igrokSumma << endl;
                cout << "�� ����� � ������: " << dilerSumma << endl;
                cout << "� ������ �������. �� ��������!" << endl;
                balance += stawka * 2;
                Sleep(5000);
                break;
            }
            if (igrokSumma > dilerSumma) {
                cout << "�� ����� � ���: " << igrokSumma << endl;
                cout << "�� ����� � ������: " << dilerSumma << endl;
                cout << "�� ��������!" << endl;
                balance += stawka * 2;
                Sleep(5000);
                break;
            }
            else if (igrokSumma == dilerSumma) {
                cout << "�� ����� � ���: " << igrokSumma << endl;
                cout << "�� ����� � ������: " << dilerSumma << endl;
                cout << "�����." << endl;
                balance += stawka;
                Sleep(5000);
                break;
            }
            else {
                cout << "�� ����� � ���: " << igrokSumma << endl;
                cout << "�� ����� � ������: " << dilerSumma << endl;
                cout << "�� ���������." << endl;
                Sleep(5000);
                break;
            }
        }
    }

    //delete arrays
    delete[] cards;
    delete[] igrokRuka;
    delete[] dilerRuka;

    //update balance
    ofstream fout("balance.txt", ios::out);
    if (fout.is_open()) {
        fout << balance;
    }
}

//rules
void rules() {
    system("cls");
    cout << "� Black Jack ������� ��������� ������:\n\n";
    cout << "���� ���� ������� ������� ���-�� ����� ��� � �������. � ������ ������� ������ �� ������� ������ � ���������\n";
    cout << "�� ���� ��� �����, ����� �� ������ ���� �� ���� ���� �������. ����� �� ������ ������� ���� �� ���� ��������\n";
    cout << "��� (pass - ���������� �����) / ����� ����� (����� �������������� �����). ���� ���� ������� ������ ����� ���\n";
    cout << "� �������, ���� 21 ����, ����� � ��� ����� Black Jack (������� ���������� �� ���� �������). �� ���� �� ��������\n";
    cout << "������ 21 ���� �� ������������ ���� ������. ����� ���� ��� �� �������� ��� ��� ������� �������, �� ��������� ���\n";
    cout << "������ ����� � �� ���������� ���� �������������� ����� �� ������. ���� ���-�� ����� ������� ��������� ���� ���\n";
    cout << "�������� Black Jack �� �� ������������ ���� ������. � ������ �������� ���� ������ ������������ ��� � ��������� ����.\n";
    cout << "T - ���, K - ������, D - ����, V - �����.";
    while (keyboard() != 13)
    {
        //FPS
        Sleep(1000 / FPS);
    }
}

//menu
int menu() {
    int z = 0;
    system("cls");
    cout << "�������� ������ ����� �������� ��������������� �������:\n\n";
    cout << "1.) ������� ����\n2.) ��������� ������\n3.) ������ ����\n4.) ����� �� ����\n\n";
    while (z < 1 || z > 5)
    {
        cin >> z;
    }
    return z;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    string path = "balance.txt";
    int balance;
    string line;

    ifstream in(path);
    if (in.is_open())
    {
        while (getline(in, line)) {
            balance = stoi(line);
        }
    }
    else {
        ofstream fout(path, ios::out);
        if (fout.is_open())
        {
            fout << "2000";
        }
        fout.close();
        cout << "� ��������� ������������ ���� balance.txt � �� ��� ��������, ���������� ����������� � ���������";
        return 0;
    }

    int choice = 0;

    cout << "����� ���������� � ���� Black Jack\n��� ����������� ������� Enter";

    while (keyboard() != 13)
    {
        //FPS
        Sleep(1000 / FPS);
    }
    while (true) {
        int z = 0;
        switch (menu()) {
        case 1:
            rules();
            break;
        case 2:
            system("cls");
            cout << "�� ����� �������: " << balance << endl;
            cout << "�������� ������� ��������� � ����� balance.txt � �������� ����� �������.\n������ ������ ��� �������������!";
            Sleep(7500);
            break;
        case 3:
            while (z != 1)
            {
                game(balance);
                system("cls");
                cout << "������ �� ������� �����?\n1.) ��� / ���� ������� ����� ������ ����� ����� ������� ��� ���";
                cin >> z;
            }
            break;
        case 4:
            choice = 4;
            break;
        }
        if (choice == 4) break;
    }
}