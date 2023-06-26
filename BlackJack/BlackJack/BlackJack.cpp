#include <iostream>
#include <conio.h>
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

//rules
void rules() {
    system("cls");
    cout << "";
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
    cout << "Выберите нужный пункт нажатием соответствующей клавиши:\n\n";
    cout << "1.) Правила игры\n2.) Рекорды\n3.) Зайти под другим именем\n4.) Начать игру\n\n";
    while (z != 1 && z != 2 && z != 3 && z != 4)
    {
        cin >> z;
    }
    return z;
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    int choice = 0;

    //create cards massive
    int* cards = new int[52] {11, 11, 11, 11, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 
        4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 
        10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    cout << "Добро пожаловать в игру Black Jack\nДля продолжения нажмите Enter";

    while (keyboard() != 13)
    {
        //FPS
        Sleep(1000 / FPS);
    }
    while (true) {
        switch (menu()) {
        case 1:
            rules();
            break;
        case 2:
            cout << 2;
            break;
        case 3:
            cout << 3;
            break;
        case 4:
            choice = 4;
            break;
        }
        if (choice == 4) break;
    }
}