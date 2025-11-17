// DNI XXXXXXXX APELLIDOS, NOMBRE
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>
#include "Dictionary.h"
#include "OrderedDictionary.h"
#include "List.h"
#include "DictionaryEntry.h"
#include "Word.h"

using namespace std;

// Función para convertir una cadena a minúsculas
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main(int argc, char* argv[]) {
    // Verificar número de argumentos
    if (argc != 5) {
        cout << "Error: argumentos incorrectos" << endl;
        return 1;
    }

    string textFile = argv[1];
    string dictFile = argv[2];
    char sourceLang = argv[3][0];
    char targetLang = argv[4][0];

    // Cargar el diccionario
    Dictionary dictionary;
    if (!dictionary.load(dictFile)) {
        cout << "Error al abrir el diccionario" << endl;
        return 1;
    }

    // Verificar que los idiomas existen en el diccionario
    if (!dictionary.containsLanguage(sourceLang) || !dictionary.containsLanguage(targetLang)) {
        cout << "No existe traduccion para esta lengua" << endl;
        return 1;
    }

    // Crear el diccionario ordenado
    OrderedDictionary orderedDict(sourceLang, targetLang);
    orderedDict.loadFromDictionary(dictionary);

    // Abrir el archivo de texto
    ifstream textStream(textFile);
    if (!textStream.is_open()) {
        cout << "Error al abrir el fichero" << endl;
        return 1;
    }

    // Obtener la lista del idioma origen
    List& sourceList = orderedDict.getList(sourceLang);

    // Contadores
    int exactMatches = 0;
    int approximateMatches = 0;

    // Procesar el archivo línea por línea
    string line;
    while (getline(textStream, line)) {
        istringstream iss(line);
        string word;
        bool firstWord = true;

        while (iss >> word) {
            // Convertir a minúsculas
            string lowerWord = toLower(word);

            // Buscar traducción exacta
            DictionaryEntry* entry = sourceList.findExact(lowerWord);
            
            if (entry != nullptr) {
                // Coincidencia exacta
                string translation = entry->getWord().getTranslation(targetLang);
                if (!firstWord) {
                    cout << " ";
                }
                cout << translation;
                entry->incrementUsage();
                exactMatches++;
            } else {
                // Buscar palabra más parecida
                entry = sourceList.findNearest(lowerWord);
                if (entry != nullptr) {
                    string translation = entry->getWord().getTranslation(targetLang);
                    if (!firstWord) {
                        cout << " ";
                    }
                    cout << translation;
                    entry->incrementUsage();
                    approximateMatches++;
                }
            }
            firstWord = false;
        }
        cout << endl;
    }

    textStream.close();

    // Mostrar estadísticas
    cout << "Coincidencias exactas: " << exactMatches << endl;
    cout << "Coincidencias aproximadas: " << approximateMatches << endl;

    // Contar usos por categoría
    map<string, int> categoryUsage;
    vector<string> categoryOrder; // Para mantener el orden de aparición

    for (size_t i = 0; i < orderedDict.size(); i++) {
        DictionaryEntry* entry = orderedDict.entries[i];
        if (entry != nullptr) {
            string category = entry->getMetadata().getGrammarCategory();
            int usage = entry->getMetadata().getUsage();
            
            if (categoryUsage.find(category) == categoryUsage.end()) {
                categoryOrder.push_back(category);
                categoryUsage[category] = 0;
            }
            categoryUsage[category] += usage;
        }
    }

    // Mostrar usos por categoría
    cout << "Usos por categoria:" << endl;
    for (const string& category : categoryOrder) {
        cout << category << ": " << categoryUsage[category] << endl;
    }

    return 0;
}