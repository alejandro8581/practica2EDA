#include "Dictionary.h"
using namespace std;

    Dictionary::Dictionary(): entries{},languages{'I','E','F'}{}

    Dictionary::Dictionary(const vector<char> &languages):Dictionary(){
        if (!languages.empty()){
            this->languages=languages;
        }
    }

    void Dictionary::addEntry(const DictionaryEntry &entry){
        this->entries.push_back(entry); //no hago mas comprobaciones de momento porque me da igual que ya este
    }

    int Dictionary::findEntry(string word, char lang) const{
        /*
        Toda esta funcion es una paranoia de meterse en arrays, loopearlos y luego volver a loopearlos para devolver el indice
        */
        for (int i=0;i<entries.size();i++){
            if(this->entries.at(i).getWord().getTranslation(lang)==word){
                for (int j=0;j<this->entries.at(i).getWord().getTranslations().size();j++){
                    if (this->entries.at(i).getWord().getTranslation(lang)==this->entries.at(i).getWord().getTranslations().at(j))
                        return j;
                }
            }
        }
        return -1;
    }

 
    string Dictionary::translate(string word, char source, char target){

    if (findEntry(word,source)<0)
        return "-"; //si no lo encuentra devuelve -1
    return entries.at(findEntry(word,source)).getWord().getTranslation(target);
    //encuentra la posición de la palabra en el idioma fuente y devuelve la traducción en el idioma destino
    // entries(j)->word->traduccion del idioma target
}
vector<DictionaryEntry> Dictionary::getEntriesByCategory(string category) const{
        vector<DictionaryEntry> entriesByCategory;
        for (int i=0;i<entries.size();i++){
            if (entries.at(i).getCategory()==category){
                entriesByCategory.push_back(entries.at(i));
            }
        }
        return entriesByCategory;
    }
    vector<DictionaryEntry> Dictionary::getEntries() const{
        return this->entries;
    }
    vector<char> Dictionary::getLanguages() const{
        return this->languages;
    }
bool Dictionary::loadFromFile(string filename) {
    ifstream file(filename);
    
    // Si no se puede abrir el archivo, devolver false
    if (!file.is_open()) {
        return false;
    }
    
    // Limpiar contenido previo del diccionario
    entries.clear();
    languages.clear();
    
    // Leer número de idiomas
    int numLanguages;
    file >> numLanguages;
    file.ignore(); // Ignorar el salto de línea
    
    // Leer las iniciales de los idiomas
    string langLine;
    getline(file, langLine);
    stringstream langStream(langLine);
    char lang;
    while (langStream >> lang) {
        languages.push_back(lang);
    }
    
    // Procesar el resto del archivo por líneas
    string line;
    string currentCategory = "unknown";
    
    while (getline(file, line)) {
        // Ignorar líneas vacías
        if (line.empty()) {
            continue;
        }
        
        // Comprobar si es una etiqueta de categoría
        if (line[0] == '<' && line[line.length() - 1] == '>') {
            // Extraer la categoría sin los signos < > y convertir a minúsculas
            currentCategory = line.substr(1, line.length() - 2);
            // Convertir a minúsculas
            for (char &c : currentCategory) {
                c = tolower(c);
            }
        } else {
            // Es una entrada del diccionario
            vector<string> translations;
            stringstream ss(line);
            string temp;
            
            // Separar por el delimitador '*'
            while (getline(ss, temp, '*')) {
                translations.push_back(temp);
            }
            
            // CRÍTICO: Crear el objeto Word con los idiomas del diccionario
            Word word(languages);  // ← Esto crea un Word con {I, E, F}
            
            // Establecer cada traducción en su idioma correspondiente
            for (int i = 0; i < translations.size() && i < languages.size(); i++) {
                word.setTranslation(languages[i], translations[i]);
            }
            
            // Crear la entrada del diccionario con la categoría actual
            DictionaryEntry entry(word, currentCategory);
            
            // Añadir la entrada al diccionario
            addEntry(entry);
        }
    }
    
    file.close();
    return true;
}
ostream & operator<<(ostream &os, const Dictionary &dictionary) {
    string lastCategory = "";
    
    for (int i = 0; i < dictionary.entries.size(); i++) {
        string currentCategory = dictionary.entries[i].getCategory();
        
        // Si cambia la categoría, imprime el encabezado
        if (currentCategory != lastCategory) {
            os << "<" << currentCategory << ">" << endl;
            lastCategory = currentCategory;
        }
        
        // Imprime la entrada completa (usa el operator<< de DictionaryEntry)
        os << dictionary.entries[i];
    }
    
    return os;
}