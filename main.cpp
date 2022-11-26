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

Person* new_pers()
{
    int name_bcount = 0;
    char* name_buffer  = new char [1024];
    char* phone_number = new char [12];
    char* snils = new char [11];
    int address_bcount = 0;
    char* company_address_buffer = new char [1024];

    cout << "Введите имя> ";
    while (!(cin >> name_buffer)){
        cin.clear();
        cout << "Попробуйте ещё раз" << endl;
        cin.ignore(100, '\n');
        cout << "Введите имя> ";
    }
    while (name_buffer[name_bcount] != '\0'){
        name_bcount++;
    }
    char* name = new char [name_bcount + 1];
    for (int i = 0; i < name_bcount; i++){
        name[i] = name_buffer[i];
    }
    delete [] name_buffer;

    cout << "Введите номер телефона (+79..)> ";
    while (!(cin >> phone_number)){
        cin.clear();
        cout << "Попробуйте ещё раз" << endl;
        cin.ignore(100, '\n');
        cout << "Введите номер телефона (+79..)> ";
    }

    cout << "Введите СНИЛС> ";
    while (!(cin >> snils)){
        cin.clear();
        cout << "Попробуйте ещё раз" << endl;
        cin.ignore(100, '\n');
        cout << "Введите СНИЛС> ";
    }

    cout << "Введите адрес> ";
    while (!(cin >> company_address_buffer)){
        cin.clear();
        cout << "Попробуйте ещё раз" << endl;
        cin.ignore(100, '\n');
        cout << "Введите адрес> ";
    }
    while (company_address_buffer[address_bcount] != '\0'){
        address_bcount++;
    }
    char* company_address = new char [address_bcount + 1];
    for (int i = 0; i < address_bcount; i++){
        company_address[i] = company_address_buffer[i];
    }
    delete [] company_address_buffer;

    Person* pers = new Person(name_bcount, name, phone_number,
                              snils, address_bcount, company_address);
    int in;
    bool inv_val = false;
    while (true){
        cout << endl << "Вы уверены, что хотите добавить эту запись?" << endl;
        pers->print_all();
        cout << endl << "0. Да" << endl << "1. Нет" << endl << endl;
        cout << "> ";
        if (inv_val){
            cout << "Неверное значение" << endl << endl;
        }
        cout << "> ";
        if ((cin >> in).good() and in >= 0 and in < 2){
            break;
        }
        if (cin.fail()){
            cin.clear();
        }
        inv_val = true;
        cin.ignore(100, '\n');
    }
    if (in == 0){
        return pers;
    }else{
        delete pers;
        return nullptr;
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
            int m = menu();
            if (m == 0){
                delete db;
                return 0;
            }else if (m == 1){
                db->search(mode_selection());
            }else if (m == 2){
                Person* pers = new_pers();
                if (pers != nullptr){
                    db->append(pers);
                }
            }else if (m == 3){
                db->print_all();
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
