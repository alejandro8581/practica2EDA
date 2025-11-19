#include "Word.h"
using namespace std;
// Constructores
Word::Word() : languages({'I', 'E', 'F'}), translations({"-", "-", "-"}) {

}


Word::Word(vector<char> l) 
    : Word()           //con esto llamaria al constructor que hay arriba, y eso inicializaría languages a I,E,F
    //se tiene que poner al lado del metodo, es una delegación. Se llamará al otro constructor si no se cumple la condición de este (crep)
    {
    if (!l.empty()){
        languages=l; 
        translations.assign(l.size(), "-"); // el assign borra el vector y asigna el string dado a lo largo de todo el tamaño indicado
    }
}


Word::Word(const Word &w) {
    languages=w.languages;
    translations=w.translations;
    //supongo vaya
}


// Destructor
Word::~Word(){
    //aquí c++, que es un chulo, hace por defecto el destructor mandando todos los atributos a tomar por culo. Que majete.
}


// Operadores
Word & Word::operator=(const Word &w) {  
    if (this != &w) { // Con esto evito cosas raras que pasan si se asigna un parametro de un word a el mismo parametro del mismo word
        // Se copian a this lo que sea el lo que sea del parametro
        this->languages = w.languages;
        this->translations = w.translations;
    }
    return *this; // Devuelve la referencia al propio objeto. Porque? Buenos días
}


bool Word::operator!=(const Word &w) {
    return !(this->languages == w.languages && this->translations == w.translations);
}
bool Word::operator==(const Word &w) {
    return (this->languages == w.languages && this->translations == w.translations);
}
// Metodos
vector<string> Word::getTranslations() const { 
    vector<string> t= this->translations;
    return t;
}

string Word::getTranslation(char language) const {
    for (int i=0; i<languages.size();i++){
        if (this->languages.at(i)==language){
            return translations.at(i);
        }
    }
    return "-";
}
int Word::setTranslation(char language, string translation) {
    //segun estoy viendo en stack overflow, la funcion tolower va char a char
    //lo hago primero para no meter demasiadas operaciones en el siguiente for
    for (int j=0; j<translation.length(); j++){
        translation[j] =tolower(translation[j]); //pasamos cada caracter a minuscula
    }
    for (int i=0; i<languages.size();i++){
        if (this->languages.at(i)==language){
            this->translations.at(i)=translation;
            return i;
        }
    }
    return -1;
}
bool Word::isFullyTranslated() const {
    for (int i=0; i<translations.size();i++){
        if (translations.at(i)=="-")
            return false;
       
    }
    return true;
}
char Word::findLanguageByTranslation(string t) const {
    for (int i=0; i<translations.size();i++){
        if (this->translations.at(i)==t)
            return languages.at(i);
       
    }
    return '-'; //aqui importante no poner doble comilla, eso es un string
}
// Sobrecarga operador salida
ostream & operator<<(ostream &os, const Word &c){
for (unsigned int i=0; i<c.languages.size(); i++) {
if (i>0) os << ":";
os << c.translations[i] << "(" << c.languages[i] << ")";
}
os << endl;
return os;
}

