#include "OrderedDictionary.h"

using namespace std;

OrderedDictionary::OrderedDictionary(){
    this->language1='I';
    this->language2='E';
    entries = vector<DictionaryEntry*>();
    list1 = List('I');
    list2 = List('E');
}

OrderedDictionary::OrderedDictionary(char language1, char language2){
    this->language1 = language1;
    this->language2 = language2;
    entries = vector<DictionaryEntry*>();
    list1 = List(language1);
    list2 = List(language2);
}

OrderedDictionary::~OrderedDictionary(){
    // Liberar memoria de todas las entradas
    for(int i = 0; i < entries.size(); i++){
        delete entries[i];
    }
    entries.clear();
}

OrderedDictionary::OrderedDictionary(const OrderedDictionary& od){
    this->language1 = od.language1;
    this->language2 = od.language2;
    entries = vector<DictionaryEntry*>();
    list1 = List(language1);
    list2 = List(language2);
    
    // Copiar cada entrada usando el método add
    for(int i = 0; i < od.entries.size(); i++){
        this->add(*(od.entries.at(i))); // Desreferenciar el puntero para pasar el objeto
    }
}

bool OrderedDictionary::isEmpty() const{
    return entries.empty();
}

int OrderedDictionary::size() const{
    return entries.size();
}

bool OrderedDictionary::add(DictionaryEntry entry){
    // Verificar que tiene traducción para ambos idiomas
    if(entry.getWord().getTranslation(language1) == "-" || entry.getWord().getTranslation(language2) == "-"){
        return false;
    }
    
    // Verificar que no exista entrada duplicada en ninguno de los dos idiomas
    for (int i = 0; i < entries.size(); i++){
        if(entry.getWord().getTranslation(language1) == entries.at(i)->getWord().getTranslation(language1) ||
           entry.getWord().getTranslation(language2) == entries.at(i)->getWord().getTranslation(language2)){
            return false;
        }
    }
    
    // Crear nueva entrada con memoria dinámica
    DictionaryEntry* entryptr = new DictionaryEntry(entry);
    
    // Añadir al vector y a las listas
    entries.push_back(entryptr);
    list1.add(entryptr);
    list2.add(entryptr);
    
    return true;
}

bool OrderedDictionary::remove(string word, char language){
    for(int i = 0; i < entries.size(); i++){
        if(word == entries.at(i)->getWord().getTranslation(language)){
            // Guardar puntero para eliminar de las listas
            DictionaryEntry* toRemove = entries[i];
            
            // Eliminar de las listas (por palabra en cada idioma)
            list1.remove(toRemove->getWord().getTranslation(language1));
            list2.remove(toRemove->getWord().getTranslation(language2));
            
            // Liberar memoria y eliminar del vector
            delete entries[i];
            entries.erase(entries.begin() + i);
            
            return true;
        }
    }
    return false;
}

int OrderedDictionary::loadFromDictionary(const Dictionary &dictionary){
    // Limpiar diccionario actual
    for(int i = 0; i < entries.size(); i++){
        delete entries[i];
    }
    entries.clear();
    
    // Limpiar listas (crear nuevas vacías)
    list1 = List(language1);
    list2 = List(language2);
    
    int added = 0;
    DictionaryEntry entry;
    // Añadir entradas del diccionario que tengan ambos idiomas
    // Usar el método público size() del Dictionary
    for(int i = 0; i < dictionary.entries.size(); i++){
        entry = dictionary.entries.at(i); // Usar método público
       // cout << "DEBUG" << entry.getWord().getTranslation(language1);
       //cout <<"WORD:"<<entry.getWord()<<endl;
       //cout << "DEBUG" << entry<< endl;
        if(entry.getWord().getTranslation(language1) != "-" && 
           entry.getWord().getTranslation(language2) != "-"){
            //cout << "DEBUG(ENTRA)" << entry.getWord().getTranslation(language1);
            if(add(entry)){
                added++;
            }
        }
    }
    
    return added;
}

bool OrderedDictionary::containsLanguage(char language) const{
    return (language == this->language1 || language == this->language2);
}

List& OrderedDictionary::getList(char language){
    if(language == language1)
        return list1;
    if(language == language2)
        return list2;
    
    throw invalid_argument("Idioma no gestionado por el diccionario");
}

ostream& operator<<(ostream &os, const OrderedDictionary &od) {
    // Mostrar lista1
    os << od.language1 << endl;
    List::Node *current = od.list1.head;
    while (current != nullptr) {
        if (current->entry != nullptr) {
            os << current->entry->getWord(); // Sin endl aquí
        }
        current = current->next;
    }
    
    // Mostrar lista2
    os << od.language2 << endl;
    current = od.list2.head;
    while (current != nullptr) {
        if (current->entry != nullptr) {
            os << current->entry->getWord(); // Sin endl aquí
        }
        current = current->next;
    }
    
    return os;
}


DictionaryEntry* OrderedDictionary::getEntry(int index) const {
    if (index < 0 || index >= (int)entries.size()) {
        return nullptr;
    }
    return entries[index];
}
