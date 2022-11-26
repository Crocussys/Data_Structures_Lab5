#ifndef PERSON_H
#define PERSON_H


class Person
{
private:
    char* name;
    int name_bcount;
    char* phone_number;
    char* snils;
    char* company_address;
    int address_bcount;
public:
    Person(int nbc, char* n, char* p, char* s, int abc, char* a);
    ~Person();
    void print_all();
    void print_short();
    int get_name_bcount();
    char* get_name();
    char* get_phone_number();
    char* get_snils();
    int get_address_bcount();
    char* get_address();
};

#endif // PERSON_H
