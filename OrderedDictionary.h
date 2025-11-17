#ifndef ORDEREDDICTIONARY_H
#define ORDEREDDICTIONARY_H
#include <iostream>
using namespace std;
class OrderedDictionary{
    private:
    char language1;
    char language2;
    vector<DictionaryEntry*> entries;
    List list1;
    List list2;
    public:
    OrderedDictionary();
    OrderedDictionary(char language1, char language2);
    ~OrderedDictionary();
    OrderedDictionary(const OrderedDictionary& od);
    bool isEmpty() const;
    int size() const;
    bool add(DictionaryEntry entry);
    bool remove(string word, char language);
    int loadFromDictionary(const Dictionary &dictionary);
    bool containsLanguage(char language) const;
    List& getList(char language);
    friend ostream& operator<<(ostream &os, const OrderedDictionary &od);
}