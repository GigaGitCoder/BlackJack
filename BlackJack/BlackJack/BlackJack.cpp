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
    cout << "Ваш баланс: " << balance << endl;
    cout << "Введите ставку: ";
    cin >> stawka;
    while (stawka > balance) {
        cout << "Ставка не может быть больше вашего баланса. Введите ставку: ";
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
        cout << "Ваша рука: ";
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
        cout << "Сумма ваших очков: " << igrokSumma << endl;
        if (dilerRuka[0] < 11) {
            cout << "Карта дилера: " << int(dilerRuka[0]) << endl;
        }
        else {
            cout << "Карта дилера: " << dilerRuka[0] << endl;
        }

        //check black jack
        if (isIgrokBlackJack) {
            system("cls");
            cout << "Ваши карты: ";
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
            cout << endl << "У вас Black Jack! Вы выиграли!" << endl;
            balance += stawka * 2;
            Sleep(5000);
            break;
        }
        if (isDilerBlackJack) {
            system("cls");
            cout << "Карты дилера: ";
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
            cout << endl << "У дилера Black Jack. Вы проиграли." << endl;
            Sleep(5000);
            break;
        }

        //menu
        cout << "Выберите действие: \n1.) Взять карту\n2.) Пас\n";
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
                cout << "На руках у вас: " << igrokSumma << endl;
                cout << "У вас перебор. Вы проиграли." << endl;
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
                cout << "На руках у вас: " << igrokSumma << endl;
                cout << "На руках у дилера: " << dilerSumma << endl;
                cout << "У дилера перебор. Вы выиграли!" << endl;
                balance += stawka * 2;
                Sleep(5000);
                break;
            }
            if (igrokSumma > dilerSumma) {
                cout << "На руках у вас: " << igrokSumma << endl;
                cout << "На руках у дилера: " << dilerSumma << endl;
                cout << "Вы выиграли!" << endl;
                balance += stawka * 2;
                Sleep(5000);
                break;
            }
            else if (igrokSumma == dilerSumma) {
                cout << "На руках у вас: " << igrokSumma << endl;
                cout << "На руках у дилера: " << dilerSumma << endl;
                cout << "Ничья." << endl;
                balance += stawka;
                Sleep(5000);
                break;
            }
            else {
                cout << "На руках у вас: " << igrokSumma << endl;
                cout << "На руках у дилера: " << dilerSumma << endl;
                cout << "Вы проиграли." << endl;
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
    cout << "В Black Jack правила предельно просты:\n\n";
    cout << "Ваша цель набрать большее кол-во очков чем у диллера. В начале каждого захода вы делаете ставку и получаете\n";
    cout << "на руки две карты, также вы видите одну из двух карт диллера. Далее вы можете сделать одно из двух дейсвтий\n";
    cout << "пас (pass - пропустить карты) / взять карту (берёте дополнительную карту). Ваша цель набрать больше очков чем\n";
    cout << "у диллера, либо 21 очко, тогда у вас будет Black Jack (выигрыш независимо от карт диллера). Но если вы наберете\n";
    cout << "больше 21 очка вы проигрываете свою ставку. После того как вы выберете пас идёт очередь диллера, он открывает вам\n";
    cout << "вторую карту и по надобности берёт дополнительные карты из колоды. Если кол-во очков диллера превышает ваше или\n";
    cout << "набирает Black Jack то вы проигрываете свою ставку. В случае выигрыша ваша ставка возвращается вам в удвоенном виде.\n";
    cout << "T - туз, K - король, D - дама, V - валет.";
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
        cout << "В программе отсутствовал файл balance.txt и он был добавлен, пожалуйста перезайдите в программу";
        return 0;
    }

    int choice = 0;

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
                cout << "Хотели бы сыграть снова?\n1.) Нет / Либо введите любое другое число чтобы сыграть еще раз";
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