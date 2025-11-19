//DNI 48785534G ORTEGA PEREZ, ALEJANDRO
#ifndef WORD_H // Directiva de preprocesamiento para evitar errores
#define WORD_H // si se incluye dos veces el fichero
#include <iostream>
#include <vector>
using namespace std;
class Word {
// Funciones amigas (friend)
friend ostream & operator<<(ostream &, const Word &);
private:
// Atributos y metodos privados
    vector<char> languages;
    vector<string> translations;
public:
// Declaracion de operaciones canonicas, operadores y metodos
      Word();
    Word(vector<char> languages);
    Word(const Word &word);
    ~Word();
    Word & operator=(const Word &word); //vale esto es para que puedas asignar words a otros, porque te has inventado el tipo. Cool.
    bool operator!=(const Word &w);
    bool operator==(const Word &w);
    vector<string> getTranslations() const ;
    string getTranslation(char language) const;
    int setTranslation(char language, string translation);
    bool isFullyTranslated() const;
    char findLanguageByTranslation(string t) const;


        // NUEVO: Devuelve la palabra principal (primer idioma no vacío)
    string getWord() const;
    
    // NUEVO: Devuelve el idioma de la palabra principal
    char getLanguage() const;
};
#endif
