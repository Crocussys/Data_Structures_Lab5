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
Person* new_pers()
{
    int name_bcount = 0;
    char* name_buffer  = new char [1024];
    char* phone_number = new char [12];
    char* snils = new char [11];
    int address_bcount = 0;
    char* company_address_buffer = new char [1024];

    cout << "Введите имя> ";
    cin.ignore(100, '\n');
    cin.getline(name_buffer, 1024);
    while (name_buffer[name_bcount] != '\0'){
        name_bcount++;
    }
    char* name = new char [name_bcount + 1];
    for (int i = 0; i < name_bcount; i++){
        name[i] = name_buffer[i];
    }
    name[name_bcount] = '\0';
    delete [] name_buffer;

    cout << "Введите номер телефона (+79..)> ";
    cin.getline(phone_number, 13);

    cout << "Введите СНИЛС> ";
    cin.getline(snils, 12);

    cout << "Введите адрес> ";
    cin.getline(company_address_buffer, 1024);
    while (company_address_buffer[address_bcount] != '\0'){
        address_bcount++;
    }
    char* company_address = new char [address_bcount + 1];
    for (int i = 0; i < address_bcount; i++){
        company_address[i] = company_address_buffer[i];
    }
    company_address[address_bcount] = '\0';
    delete [] company_address_buffer;

    Person* pers = new Person(name_bcount, name, phone_number,
                              snils, address_bcount, company_address);
    int in;
    bool inv_val = false;
    while (true){
        cout << endl << "Вы уверены, что хотите добавить эту запись?" << endl;
        pers->print_all();
        cout << endl << "0. Да" << endl << "1. Нет" << endl << endl;
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
        if (buffer_int == 2){
            Person* pers = new Person();
            people[i] = pers;
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
int Data::hash_func(char* key)
{
    int h = 1;
    for (int i = 3; i < 12; i++){
        h *= (int)key[i];
        h %= size;
        if (h == 0){
            h = 1;
        }
    }
    double hF = h * 0.6180339887;
    hF -= (int) hF;
    return (int)(hF * size);
}
int Data::collision(int prev, int i)
{
    return (prev + 2 * i + i * i) % size;
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
        if (pers->is_deleted()){
            f << "2\n";
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
        if (pers != nullptr and !pers->is_deleted()){
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
    cout << endl << "1. Удалить" << endl;
    cout << "0. Назад" << endl << endl;
    while (true){
        cout << "> ";
        if ((cin >> in).good() and in >= 0 and in < 3){
            if (in == 1){
                remove(id);
                return;
            }else if (in == 0){
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
        int ind = hash_func(in);
        int i = 0;
        while (true){
            Person* pers = people[ind];
            if (pers == nullptr){
                cout << "Совпадений не найдено" << endl;
                return;
            }
            if (!pers->is_deleted() and strcmp(pers->get_phone_number(), in)){
                action_with_a_persone(ind);
                return;
            }
            i++;
            ind = collision(ind, i);
        }
        cout << "Требуется рехеширование!" << endl;
        return;
    }else{
        int* indices = new int [count_elements];
        int ind = 1;
        for (int i = 0; i < size; i++){
            Person* pers = people[i];
            if (pers != nullptr){
                char* temp;
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
void Data::append()
{
    if (count_elements >= size){
        cout << "Ошибка!" << endl;
        cout << "Требуется рехеширование!" << endl;
        return;
    }
    Person* pers = new_pers();
    if (pers == nullptr){
        return;
    }
    int ind = hash_func(pers->get_phone_number());
    int i = 0;
    while (true) {
        Person* p = people[ind];
        bool flag = false;
        if (p == nullptr){
            flag = true;
        }else if (p->is_deleted()){
            flag = true;
        }
        if (flag){
            people[ind] = pers;
            count_elements++;
            save_in_file();
            break;
        }
        i++;
        ind = collision(ind, i);
    }
    if (i > 4){
        cout << "Требуется рехеширование!" << endl;
    }
}
void Data::rehashing()
{
    size *= 2;
    Person** new_array = new Person* [size];
    for (int i = 0; i < size / 2; i++){
        Person* pers = people[i];
        if (pers != nullptr){
            int ind = hash_func(pers->get_phone_number());
            int j = 0;
            while (true) {
                Person* p = new_array[ind];
                bool flag = false;
                if (p == nullptr){
                    flag = true;
                }else if (p->is_deleted()){
                    flag = true;
                }
                if (flag){
                    new_array[ind] = pers;
                    break;
                }
                j++;
                ind = collision(ind, j);
            }
        }
    }
    delete [] people;
    people = new_array;
    save_in_file();
}
void Data::remove(int id)
{
    if (id < 0 or id >= size){
        throw 4;
    }
    Person* pers = people[id];
    if (pers != nullptr and !pers->is_deleted()){
        pers->del();
        count_elements--;
        save_in_file();
    }
}
