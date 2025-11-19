#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "Word.h"
#include "Metadata.h"
#include "DictionaryEntry.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Dictionary{
    private:
        vector<char> languages;
        vector<DictionaryEntry> entries;
         friend class OrderedDictionary;
    public:
        Dictionary();
        Dictionary(const vector<char> &languages);
        void addEntry(const DictionaryEntry &entry);
        int findEntry(string word, char lang) const;
        string translate(string word, char source, char target);
        vector<DictionaryEntry> getEntriesByCategory(string category) const;
        vector<DictionaryEntry> getEntries() const;
        vector<char> getLanguages() const;
        bool loadFromFile(string filename);
        friend ostream & operator<<(ostream &os, const Dictionary &dictionary);
};


#endif