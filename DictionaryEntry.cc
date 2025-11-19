#include "Word.h"
#include "Metadata.h"
#include "DictionaryEntry.h"


    DictionaryEntry::DictionaryEntry(): word(), metadata(){};

    DictionaryEntry:: DictionaryEntry(Word word, string category):DictionaryEntry(){
        if (word!=Word() && !category.empty()){ //al comparar Word con un constructor cualquiera (objeto vacio) se compureba que no esta vacio
            this->word=word;
            this->metadata = Metadata(category);
        }
    }

    DictionaryEntry::DictionaryEntry(const DictionaryEntry &entry){
        this->word=entry.getWord();
        this->metadata.setCategory(entry.getCategory());
    }

    DictionaryEntry& DictionaryEntry::operator=(const DictionaryEntry &entry){
        if (this != &entry){
            this->word=entry.getWord();
            this->metadata.setCategory(entry.getCategory());
        }
        return *this;
    }

    DictionaryEntry::~DictionaryEntry(){}


    Word DictionaryEntry::getWord() const{
        return this->word;
    }
    Metadata DictionaryEntry::getMetadata() const {
        return this->metadata; 
    }
    string DictionaryEntry::getCategory() const {
        return this->metadata.getCategory();
    }
    int DictionaryEntry::getUsageCount() const{
        return this->metadata.getUsageCount();
    }
    void DictionaryEntry::incrementUsage(){
        this->metadata.incrementUsage();
    }
    bool DictionaryEntry::operator==(const DictionaryEntry &entry) const{
        return (this->metadata==entry.getMetadata() && this->getWord()==entry.getWord());
    }
    bool DictionaryEntry::operator!=(const DictionaryEntry &entry) const{
        return (!(this->metadata==entry.getMetadata() || this->getWord()==entry.getWord()));
    }
    ostream & operator<<(ostream &os, const DictionaryEntry &entry) {
        os << entry.word << " " << entry.metadata; // Usa los operadores << de Word y Metadata
        return os; // Retorna el stream para permitir encadenamiento
    }