#include <iostream>
#include "data.h"

using namespace std;

int menu()
{
    bool inv_val = false;
    while (true){
        int in;
        cout << "Главное меню" << endl;
        cout << "1. Найти" << endl;
        cout << "2. Добавить" << endl;
        cout << "3. Вывести всю таблицу" << endl;
        cout << "4. Рехешировать" << endl;
        cout << "0. Выйти" << endl << endl;
        if (inv_val){
            cout << "Неверное значение" << endl << endl;
        }
        cout << "> ";
        if ((cin >> in).good() and in >= 0 and in < 5){
            return in;
        }
        if (cin.fail()){
            cin.clear();
        }
        inv_val = true;
        cin.ignore(100, '\n');
    }
}

int mode_selection()
{
    bool inv_val = false;
    while (true){
        int in;
        cout << "Поиск" << endl;
        cout << "1. По телефону (быстро)" << endl;
        cout << "2. По имени" << endl;
        cout << "3. По СНИЛСу" << endl;
        cout << "4. По адресу" << endl;
        cout << "0. Назад" << endl << endl;
        if (inv_val){
            cout << "Неверное значение" << endl << endl;
        }
        cout << "> ";
        if ((cin >> in).good() and in >= 0 and in < 5){
            return in;
        }
        if (cin.fail()){
            cin.clear();
        }
        inv_val = true;
        cin.ignore(100, '\n');
    }
}

int main(int argc, char* argv[])
{
//    try{
        if (argc < 2){
            throw 1;
        }
        Data* db = new Data(argv[1]);
        while (true){
            switch (menu()) {
            case 0:
                delete db;
                return 0;
            case 1:
                db->search(mode_selection());
                break;
            case 2:
                db->append();
                break;
            case 3:
                db->print_all();
                break;
            case 4:
                db->rehashing();
                break;
            default:
                throw 4;
            }
        }
//    }catch (int err){
//        switch (err) {
//        case 1:
//            cout << "Not enough arguments" << endl;
//            break;
//        case 2:
//            cout << "File error" << endl;
//            break;
//        case 3:
//            cout << "Invalid value" << endl;
//            break;
//        default:
//            cout << "Unknown error" << endl;
//            return -1;
//        }
//        return err;
//    }
    return 0;
}
