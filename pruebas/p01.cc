/*
 Se crea un objeto List, se añaden tres entradas y se prueban algunos getters 
 y el operador de salida 
 */
 
#include <iostream>
#include "../List.h"

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

  List l;
  
  cout << "isEmpty? " << l.isEmpty() << endl;
  cout << "size: "    << l.size() << endl;
  
  cout << "l.add(run)= " << l.add(&deRun) << endl;  
  cout << "l.add(garage)= " << l.add(&deGarage) << endl;  
  cout << "l.add(fly)= " << l.add(&deFly) << endl;  

  cout << "despues de add:" << endl;  
  cout << "isEmpty? " << l.isEmpty() << endl;
  cout << "size: "    << l.size() << endl;

  cout << endl;
  DictionaryEntry *deg = l.get(1);
  if (deg != nullptr)
      cout << "l.get(1)= " << deg->getWord();
  
  deg = l.findNearest("race");
  if (deg != nullptr)
      cout << "l.findNearest(\"race\")= " << deg->getWord();
  
  
  cout << endl
       << l ;
}

