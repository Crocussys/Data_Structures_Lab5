#include <iostream>
#include "person.h"

using namespace std;

Person::Person(char n[], char p[], char s[], char a[])
{
    name = n;
    phone_number = p;
    snils = s;
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
char* Person::get_address()
{
    return company_address;
}
