// DNI XXXXXXXX APELLIDOS, NOMBRE
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>
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
    // Verificar número de argumentos [cite: 187, 191]
    if (argc != 5) {
        cout << "Error: argumentos incorrectos" << endl;
        return 1;
    }

    string textFile = argv[1];
    string dictFile = argv[2];
    char sourceLang = argv[3][0];
    char targetLang = argv[4][0];

    // Cargar el diccionario [cite: 195]
    Dictionary dictionary;
    if (!dictionary.loadFromFile(dictFile)) {
        cout << "Error al abrir el diccionario" << endl;
        return 1;
    }

    // Crear el diccionario ordenado
    OrderedDictionary orderedDict(sourceLang, targetLang);
    
    // Cargar entradas desde el diccionario base [cite: 163]
    int loaded = orderedDict.loadFromDictionary(dictionary);
    
    // Verificar existencia de idiomas [cite: 199, 200]
    if (loaded == 0 || !orderedDict.containsLanguage(sourceLang) || !orderedDict.containsLanguage(targetLang)) {
        cout << "No existe traduccion para esta lengua" << endl;
        return 1;
    }

    // Abrir el archivo de texto [cite: 204]
    ifstream textStream(textFile);
    if (!textStream.is_open()) {
        cout << "Error al abrir el fichero" << endl;
        return 1;
    }

    // Obtener la lista del idioma origen para buscar traducciones
    List& sourceList = orderedDict.getList(sourceLang);

    // Contadores para estadísticas
    int exactMatches = 0;
    int approximateMatches = 0;

    // Procesar el archivo línea por línea [cite: 207]
    string line;
    while (getline(textStream, line)) {
        istringstream iss(line);
        string word;
        bool firstWord = true;

        while (iss >> word) {
            // Convertir a minúsculas para búsqueda y distancia [cite: 221, 222]
            string lowerWord = toLower(word);

            // 1. Buscar traducción exacta [cite: 210]
            DictionaryEntry* entry = sourceList.findExact(lowerWord);
            
            if (entry != nullptr) {
                // Coincidencia exacta
                string translation = entry->getWord().getTranslation(targetLang);
                if (!firstWord) {
                    cout << " ";
                }
                cout << translation;
                entry->incrementUsage(); // Incrementar uso
                exactMatches++;
            } else {
                // 2. Buscar traducción aproximada [cite: 211]
                entry = sourceList.findNearest(lowerWord);
                if (entry != nullptr) {
                    string translation = entry->getWord().getTranslation(targetLang);
                    if (!firstWord) {
                        cout << " ";
                    }
                    cout << translation;
                    entry->incrementUsage(); // Incrementar uso
                    approximateMatches++;
                }
            }
            firstWord = false;
        }
        cout << endl; // Mantener estructura original [cite: 207]
    }

    textStream.close();

    // Mostrar estadísticas finales [cite: 213]
    cout << "Coincidencias exactas: " << exactMatches << endl;
    cout << "Coincidencias aproximadas: " << approximateMatches << endl;

    // --- LÓGICA PARA MOSTRAR CATEGORÍAS EN ORDEN DEL VECTOR ---
    // El enunciado especifica: "Las categorías se mostrarán en el orden en que aparecen 
    // en el vector de entradas del diccionario".
    
    map<string, int> categoryUsage;
    vector<string> categoryOrder; // Para preservar el orden de aparición

    // Iteramos sobre el OrderedDictionary usando el índice para respetar el orden del vector
    // NOTA: Esto requiere que hayas añadido el método getEntry(int index) en OrderedDictionary
    for (int i = 0; i < orderedDict.size(); i++) {
        DictionaryEntry* entry = orderedDict.getEntry(i); 
        
        if (entry != nullptr) {
            string category = entry->getMetadata().getCategory();
            int usage = entry->getMetadata().getUsageCount();
            
            // Si es la primera vez que encontramos esta categoría, guardamos el orden
            if (categoryUsage.find(category) == categoryUsage.end()) {
                categoryOrder.push_back(category);
            }
            // Acumulamos el uso. Nota: entry apunta al mismo objeto que usamos en sourceList,
            // por lo que entry->incrementUsage() arriba ya actualizó este valor.
            categoryUsage[category] += usage;
        }
    }

    // Mostrar usos por categoría en el orden correcto
    cout << "Usos por categoria:" << endl;
    for (unsigned int i = 0; i < categoryOrder.size(); i++) {
        string cat = categoryOrder[i];
        cout << cat << ": " << categoryUsage[cat] << endl;
    }

    return 0;
}