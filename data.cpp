#include <iostream>
#include <fstream>
#include "data.h"

using namespace std;

bool strcmp(char* str1, char* str2)
{
    int i;
    for (i = 0; str1[i] != '\0' and str2[i] != '\0'; i++){
        if (str1[i] != str2[i]){
            return false;
        }
    }
    if (str1[i] == str2[i]){
        return true;
    }else{
        return false;
    }
}
bool find(char* str1, char* str2)
{
    for (int i = 0; str1[i] != '\0'; i++){
        if (str1[i] != str2[i]){
            return false;
        }
    }
    return true;
}
Data::Data()
{
    count_elements = 0;
    people = nullptr;
    size = 0;
    file_name = nullptr;
}
Data::Data(char* file)
{
    count_elements = 0;
    file_name = file;
    fstream f(file_name, ios::in|ios::binary);
    if (!f)
        throw 2;
    int buffer_int;
    if (!(f >> buffer_int))
        throw 3;
    size = 1;
    for (int i = 0; i < buffer_int; i++){
        size *= 2;
    }
    people = new Person* [size];
    for (int i = 0; i < size; i++){
        if (!(f >> buffer_int))
            throw 3;
        if (buffer_int == 0){
            people[i] = nullptr;
            continue;
        }
        f.seekg(1, ios::cur);
        char* snils = new char [11];
        f.read(snils, 11);
        char* phone_number = new char [12];
        f.read(phone_number, 12);
        if (!(f >> buffer_int))
            throw 3;
        f.seekg(1, ios::cur);
        char* address = new char [buffer_int + 1];
        f.read(address, buffer_int);
        if (!(f >> buffer_int))
            throw 3;
        f.seekg(1, ios::cur);
        char* name = new char [buffer_int + 1];
        f.read(name, buffer_int);
        Person* pers = new Person(name, phone_number, snils, address);
        people[i] = pers;
        count_elements++;
    }
    f.close();
}
Data::~Data()
{
    for (int i = 0; i < size; i++){
        delete people[i];
        people[i] = nullptr;
    }
    people = nullptr;
    file_name = nullptr;
    size = 0;
    count_elements = 0;
}
int Data::hash(char* key)
{
    int h = 1;
    for (int i = 3; i < 12; i++){
        h = (h * (int)key[i]) % size;
    }
    return h;
}
int Data::hash_func(char* key, int n)
{
    double hF;
    int h = hash(key);
    hF = (double)n * 0.6180339887;
    hF = h * hF - (int)h * hF;
    return (int)(hF * size);
}
int Data::print_all()
{
    int in;
    int* index = new int [count_elements];
    cout << "Вывести всю таблицу" << endl;
    int ind = 1;
    for (int i = 0; i < size; i++){
        Person* pers = people[i];
        if (pers != nullptr){
            cout << ind << ". ";
            pers->print_short();
            index[ind - 1] = i;
            ind++;
        }
    }
    cout << "0. Назад" << endl << endl;
    while (true){
        cout << "> ";
        cin >> in;
        if (in >= 0 and in < ind){
            if (in == 0){
                delete [] index;
                return -1;
            }else{
                in = index[in - 1];
                delete [] index;
                return in;
            }
        }else{
            cout << "Неверное значение" << endl << endl;
            continue;
        }
    }
}
void Data::action_with_a_persone(int id)
{
    int in;
    if (id < 0 or id >= size){
        throw 4;
    }
    Person* pers = people[id];
    if (pers == nullptr){
        throw 4;
    }
    pers->print_all();
    cout << endl << "1. Изменить" << endl;
    cout << "2. Удалить" << endl;
    cout << "0. Назад" << endl << endl;
    while (true){
        cout << "> ";
        cin >> in;
        if (in >= 0 and in < 3){
            switch (in) {
            case 1:

            case 2:

            default:
                return;
            }
        }else{
            cout << "Неверное значение" << endl << endl;
            continue;
        }
    }
}
void Data::search(int mode)
{
    if (mode < 1 or mode > 4){
        throw 4;
    }
    char* in = new char [1024];
    cout << "Поиск" << endl;
    cout << "Введите строку> ";
    cin >> in;
    if (mode == 1){
        for (int i = 0; i < 5; i++){
            int a = hash_func(in, i);
            Person* pers = people[a];
            if (pers == nullptr){
                cout << "Совпадений не найдено" << endl;
                return;
            }
            if (strcmp(pers->get_phone_number(), in)){
                action_with_a_persone(a);
                return;
            }
        }
        cout << "Требуется рехеширование!" << endl;
        return;
    }else{
        for (int i = 0; i < size; i++){
            char* temp;
            Person* pers = people[i];
            switch (mode) {
            case 2:
                temp = pers->get_name();
                break;
            case 3:
                temp = pers->get_snils();
                break;
            case 4:
                temp = pers->get_address();
                break;
            default:
                throw 4;
            }
            if (find(temp, in)){

            }
        }
    }
}
