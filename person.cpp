#include <iostream>
#include "person.h"

using namespace std;

Person::Person(int nbc, char* n, char* p, char* s, int abc, char* a)
{
    name_bcount = nbc;
    name = n;
    phone_number = p;
    snils = s;
    address_bcount = abc;
    company_address = a;
}
Person::~Person()
{
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
void Person::print_short()
{
    cout << name << " " << phone_number << endl;
}
void Person::print_all()
{
    cout << name << endl;
    cout << "Номер телефона: " << phone_number << endl;
    cout << "СНИЛС: " << snils << endl;
    cout << "Адрес: " << company_address << endl;
}
int Person::get_name_bcount()
{
    return name_bcount;
}
char* Person::get_name()
{
    return name;
}
char* Person::get_phone_number()
{
    return phone_number;
}
char* Person::get_snils()
{
    return snils;
}
int Person::get_address_bcount()
{
    return address_bcount;
}
char* Person::get_address()
{
    return company_address;
}
