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
    cout << "В Black Jack правила предельно просты:\n\n";
    cout << "Ваша цель набрать большее кол-во очков чем у диллера. В начале каждого захода вы делаете ставку и получаете\n";
    cout << "на руки две карты, также вы видите одну из двух карт диллера. Далее вы можете сделать одно из двух дейсвтий\n";
    cout << "пас (pass - пропустить карты) / взять карту (берёте дополнительную карту). Ваша цель набрать больше очков чем\n";
    cout << "у диллера, либо 21 очко, тогда у вас будет Black Jack (выигрыш независимо от карт диллера). Но если вы наберете\n";
    cout << "больше 21 очка вы проигрываете свою ставку. После того как вы выберете пас идёт очередь диллера, он открывает вам\n";
    cout << "вторую карту и по надобности берёт дополнительные карты из колоды. Если кол-во очков диллера превышает ваше или\n";
    cout << "набирает Black Jack то вы проигрываете свою ставку. В случае выигрыша ваша ставка возвращается вам в удвоенном виде.";
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
    cout << "1.) Правила игры\n2.) Проверить баланс\n3.) Начать игру\n4.) Выйти из игры\n\n";
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
    char* cards = new char[52]{ 'Т', 'Т', 'Т', 'Т', 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
        4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9,
        'В', 'В', 'В', 'В', 'Д', 'Д', 'Д', 'Д', 'К', 'К', 'К', 'К', 10, 10, 10, 10 };

    cout << "Добро пожаловать в игру Black Jack\nДля продолжения нажмите Enter";

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
            cout << "На вашем балансе: " << balance << endl;
            cout << "Значение баланса находится в файле balance.txt в корневой папке проекта.\nМенять только при необходимости!";
            Sleep(7500);
            break;
        case 3:
            while (z != 1)
            {
                game(balance);
                system("cls");
                cout << "Хотели бы сыграть снова?\n1.) Нет / Либо введите любое другое число чтобы выйти в меню";
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