#include <iostream>
#include "person.h"

using namespace std;

Person::Person()
{
    deleted = true;
}
Person::Person(int nbc, char* n, char* p, char* s, int abc, char* a)
{
    name_bcount = nbc;
    name = n;
    phone_number = p;
    snils = s;
    address_bcount = abc;
    company_address = a;
    deleted = false;
}
Person::~Person()
{
    if (deleted){
        deleted = false;
    }else{
        delete name;
        name = nullptr;
        delete phone_number;
        phone_number = nullptr;
        delete snils;
        snils = nullptr;
        delete company_address;
        company_address = nullptr;
        name_bcount = 0;
        company_address = 0;
        deleted = false;
    }
}
void Person::print_short()
{
    if (!deleted){
        cout << name << " " << phone_number << endl;
    }
}
void Person::print_all()
{
    if (!deleted){
        cout << name << endl;
        cout << "Номер телефона: " << phone_number << endl;
        cout << "СНИЛС: " << snils << endl;
        cout << "Адрес: " << company_address << endl;
    }
}
int Person::get_name_bcount()
{
    if (deleted){
        throw 4;
    }
    return name_bcount;
}
char* Person::get_name()
{
    if (deleted){
        throw 4;
    }
    return name;
}
char* Person::get_phone_number()
{
    if (deleted){
        throw 4;
    }
    return phone_number;
}
char* Person::get_snils()
{
    if (deleted){
        throw 4;
    }
    return snils;
}
int Person::get_address_bcount()
{
    if (deleted){
        throw 4;
    }
    return address_bcount;
}
char* Person::get_address()
{
    if (deleted){
        throw 4;
    }
    return company_address;
}
bool Person::is_deleted()
{
    return deleted;
}
void Person::del()
{
    deleted = true;
    delete name;
    name = nullptr;
    delete phone_number;
    phone_number = nullptr;
    delete snils;
    snils = nullptr;
    delete company_address;
    company_address = nullptr;
    name_bcount = 0;
    company_address = 0;
}
