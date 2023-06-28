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
void game(int &balance) {

}

//play again?
void replay() {

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
    cout << "�������� Black Jack �� �� ������������ ���� ������. � ������ �������� ���� ������ ������������ ��� � ��������� ����.";
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
    int balance;
    string line;

    ifstream in("balance.txt");
    if (in.is_open())
    {
        while (getline(in, line)) {
            balance = stoi(line);
        }
    }



    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    int choice = 0;

    //create cards massive
    char* cards = new char[52]{ '�', '�', '�', '�', 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
        4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9,
        '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', 10, 10, 10, 10 };

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
                cout << "������ �� ������� �����?\n1.) ��� / ���� ������� ����� ������ ����� ����� ����� � ����";
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