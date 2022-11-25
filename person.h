#ifndef PERSON_H
#define PERSON_H


class Person
{
private:
    char* name;
    char* phone_number;
    char* snils;
    char* company_address;
public:
    Person(char n[], char p[], char s[], char a[]);
    ~Person();
    void print_all();
    void print_short();
    char* get_name();
    char* get_phone_number();
    char* get_snils();
    char* get_address();
};

#endif // PERSON_H
