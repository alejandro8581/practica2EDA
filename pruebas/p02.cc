/*
 Se crea un objeto OrderedDictionary, se añaden tres entradas y se prueban 
 algunos getters y el operador de salida 
 */
 
#include <iostream>
#include "../OrderedDictionary.h"

int main()
{
  vector<char> languages={'F','I','E'};
  Word wordRun(languages);
  wordRun.setTranslation('I',"run");
  wordRun.setTranslation('E',"correr");
  
  DictionaryEntry deRun(wordRun,"verb");

  Word wordGarage(languages);
  wordGarage.setTranslation('I',"garage");
  wordGarage.setTranslation('F',"garage");
  wordGarage.setTranslation('E',"garaje");
  
  DictionaryEntry deGarage(wordGarage,"noun");
  
  Word wordFly(languages);
  wordFly.setTranslation('I',"fly");
  wordFly.setTranslation('E',"volar");
  
  DictionaryEntry deFly(wordFly,"verb");
  
  
  
  OrderedDictionary dict('E','I');
  
  cout << "isEmpty? " << dict.isEmpty() << endl;
  cout << "size: "    << dict.size() << endl;
  
  cout << "dict.add(run)= " << dict.add(deRun) << endl;  
  cout << "dict.add(garage)= " << dict.add(deGarage) << endl;  
  cout << "dict.add(fly)= " << dict.add(deFly) << endl;  

  cout << "despues de add:" << endl;  
  cout << "isEmpty? " << dict.isEmpty() << endl;
  cout << "size: "    << dict.size() << endl;

  cout << "Diccionario:" << endl 
       << dict ;
}
