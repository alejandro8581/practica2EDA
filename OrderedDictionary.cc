#include "OrderedDictionary.h"

using namespace std;

OrderedDictionary::OrderedDictionary(){
    this.language1='I';
    this.language2='E';
    entries=[];
    list1=List('I');
    list2=List('E');

}

OrderedDictionary::OrderedDictionary(char language1, char language2){
    this.language1=language1;
    this.language2=language2;
    entries=[];
    lsit1=List(language1);
    list2=List(language2);
}

OrderedDictionary::~OrderedDictionary(){}

OrderedDictionary::OrderedDictionary(const OrderedDictionary& od){
    this.language1=od.language1;
    this.language2=od.language2;
    for(int i=0;i<entries.size();i++){
        this.add(od.entries.get(i)); //esto lo gestionará luego el add de esta clase
    }
}

OrderedDictionary::bool isEmpty() const{
    if(entries.empty())
        return true; 
    return false;
}
OrderedDictionary::int size() const{
    return entries.size();
}

OrderedDictionary::bool add(DictionaryEntry entry){
    //con entry.getTranslation(languageX) tengo la traduccion en cada idioma, tengo que recorrer entries comprobando ambos idiomas
    for (int i=0;i<entries.size();i++){
        if(entry.getTranslation(language1)==entries.at(i).getTranslation(language1) ||entry.getTranslation(language2)==entries.at(i).getTranslation(language2)){
            //alguna de las traducciones es entrada repetida
            //no se agrega
            return false;
        }
    }
    //aqui ya se ha comprobado que no se repita la entrada
    Dictionaryentry* entryptr = new DictionaryEntry(entry);
    //lo paso a un nuevo puntero
    entries.push_back(entryptr);
    list1.add(entryptr);
    list2.add(entryptr);
    //ya el metodo add debe procurar orden y la correcta adicion de las entradas
    return true;
}

OrderedDictionary::bool remove(string word, char language){
    
    for(int i=0;i<entries.size();i++){
        if(word==entries.at(i).getTranslation(language)){
            delete entries[i];//como hay punteros, la memoria se vuelve crazy y paranoica
            entries.erase(entries.begin() + i);
            list1.remove(word);
            list2.remove(word);
            //ya list gestiona con su metodo todo lo extravagante
            return true;
        }
    }
    return false;
}

OrderedDictionary::int loadFromDictionary(const Dictionary &dictionary){
    this->entries.clear();
    list1.clear();//he creado un clear para list
    list2.clear();
    //ahora deberia de estar todo vacio
    int added=0;
    for(int i=0;i<dictionary.entries.size();i++){
        if(entries.at(i).getTranslation(language1)!='-' &&entries.at(i).getTranslation(language2)!='-' ){//existe traduccion para ambos idiomas
            add(entries.at(i));//esto ya gestiona todo con el m etodo de arriba
            added++;
        }
    }
    return added;
}
bool OrderedDictionary::containsLanguage(char language) const{
    if(language==language1 || language==language2){
        return true;
    }
    return false;
}
List& OrderedDictionary::getList(char language){
    if(language==language1)
        return list1;
    if(language==language2)
        return list2;
}
ostream& operator<<(ostream &os, const OrderedDictionary &od) {
    // Mostrar el idioma de la lista1
    os << od.language1 << endl;
    
    // Recorrer y mostrar todas las entradas de la lista1 sin metadatos
    Node *current = od.list1.head;
    while (current != nullptr) {
        if (current->entry != nullptr) {
            // Mostrar la entrada sin los metadatos
            os << current->entry->getWord();
            current->entry->showTranslations(os);
            os << endl;
        }
        current = current->next;
    }
    
    // Mostrar el idioma de la lista2
    os << od.language2 << endl;
    
    // Recorrer y mostrar todas las entradas de la lista2 sin metadatos
    current = od.list2.head;
    while (current != nullptr) {
        if (current->entry != nullptr) {
            // Mostrar la entrada sin los metadatos
            os << current->entry->getWord();
            current->entry->showTranslations(os);
            os << endl;
        }
        current = current->next;
    }
    
    return os;
}
