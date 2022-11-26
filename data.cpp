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
    for (int i = 0; str2[i] != '\0'; i++){
        if (str1[0] == str2[i]){
            bool flag = true;
            for (int j = 1; str1[j] != '\0'; j++){
                if (str1[j] != str2[i + j]){
                    flag = false;
                    break;
                }
            }
            if (flag){
                return true;
            }
        }
    }
    return false;
}
int choice(int* indices, int max_ind)
{
    int in;
    cout << "0. Назад" << endl << endl;
    while (true){
        cout << "> ";
        if ((cin >> in).good() and in >= 0 and in < max_ind){
            if (in == 0){
                delete [] indices;
                return -1;
            }else{
                in = indices[in - 1];
                delete [] indices;
                return in;
            }
        }
        if (cin.fail()){
            cin.clear();
        }
        cout << "Неверное значение" << endl << endl;
        cin.ignore(100, '\n');
    }
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
        int address_bcount;
        if (!(f >> address_bcount))
            throw 3;
        f.seekg(1, ios::cur);
        char* address = new char [address_bcount + 1];
        f.read(address, address_bcount);
        int name_bcount;
        if (!(f >> name_bcount))
            throw 3;
        f.seekg(1, ios::cur);
        char* name = new char [name_bcount + 1];
        f.read(name, name_bcount);
        Person* pers = new Person(name_bcount, name, phone_number, snils, address_bcount, address);
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
void Data::save_in_file()
{
    fstream f(file_name, ios::out|ios::trunc|ios::binary);
    if (!f)
        throw 2;
    int buffer_int = 0;
    float new_size = size;
    while (new_size > 1){
        buffer_int++;
        new_size /= 2;
    }
    f << buffer_int << '\n';
    for (int i = 0; i < size; i++){
        Person* pers = people[i];
        if (pers == nullptr){
            f << "0\n";
            continue;
        }
        f << "1 " << pers->get_snils() << pers->get_phone_number() <<
             " " << pers->get_address_bcount() << " " << pers->get_address() <<
             " " << pers->get_name_bcount() << " " << pers->get_name() << '\n';
    }
    f.close();
}
void Data::print_all()
{
    int* indices = new int [count_elements];
    cout << "Вывести всю таблицу" << endl;
    int ind = 1;
    for (int i = 0; i < size; i++){
        Person* pers = people[i];
        if (pers != nullptr){
            cout << ind << ". ";
            pers->print_short();
            indices[ind - 1] = i;
            ind++;
        }
    }
    ind = choice(indices, ind);
    if (ind != -1){
        action_with_a_persone(ind);
    }
    return;
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
        if ((cin >> in).good() and in >= 0 and in < 3){
            switch (in) {
            case 1:

            case 2:

            default:
                return;
            }
        }
        if (cin.fail()){
            cin.clear();
        }
        cout << "Неверное значение" << endl << endl;
        cin.ignore(100, '\n');
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
        int* indices = new int [count_elements];
        int ind = 1;
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
            if (find(in, temp)){
                cout << ind << ". ";
                pers->print_short();
                indices[ind - 1] = i;
                ind++;
            }
        }
        if (ind == 1){
            cout << "Совпадений не найдено" << endl;
            delete [] indices;
            return;
        }
        ind = choice(indices, ind);
        if (ind != -1){
            action_with_a_persone(ind);
        }
        return;
    }
}
void Data::append(Person* pers)
{

}
