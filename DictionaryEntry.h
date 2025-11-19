#ifndef DICTIONARYENTRY_H
#define DICTIONARYENTRY_H
#include "Word.h"
#include "Metadata.h"
#include <iostream>
using namespace std;
class DictionaryEntry{
friend ostream & operator<<(ostream &, const DictionaryEntry &);
private:
    Word word;
    Metadata metadata;
public:
    DictionaryEntry();
    DictionaryEntry(Word word, string category);
    ~DictionaryEntry();
    DictionaryEntry(const DictionaryEntry &entry);
    DictionaryEntry & operator=(const DictionaryEntry &entry);
    Word getWord() const; //is this tuff??
    Metadata getMetadata() const;
    string getCategory() const;
    int getUsageCount() const;
    void incrementUsage();
    bool operator==(const DictionaryEntry &entry) const;
    bool operator!=(const DictionaryEntry &entry) const;
    friend ostream & operator<<(ostream &os, const DictionaryEntry &entry);
};






#endif