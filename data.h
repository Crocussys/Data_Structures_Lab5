#ifndef DATA_H
#define DATA_H
#include "person.h"


class Data
{
private:
    int count_elements;
    Person** people;
    int size;
    char* file_name;

    int hash(char* key);
    int hash_func(char* key, int n);
public:
    Data();
    Data(char* file);
    ~Data();
    void search(int mode);
    void append(Person* pers);
    void remove();
    int print_all();
    void rehashing();
    void action_with_a_persone(int id);
};

#endif // DATA_H
