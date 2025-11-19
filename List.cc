#include "List.h"
using namespace std;

List::List(){
    language='I';
    head=nullptr;
    tail=nullptr;
}
List::List(char language){
    this->language=language;
    head=nullptr;
    tail=nullptr;
}
List::Node::Node(DictionaryEntry *entry) {
    this->entry = entry;
    this->next = nullptr;
}
List::Node::Node() {
    this->entry = nullptr;
    this->next = nullptr;
}


List::~List(){
    Node* current = head;
    while(current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

List::List(const List &list){
    language = list.language;
    head = nullptr;
    tail = nullptr;
    
    Node* current = list.head;
    while(current != nullptr){
        add(current->entry);
        current = current->next;
    }
}

List& List::operator=(const List& list){
    if(this == &list) return *this;
    
    // Liberar memoria actual
    Node* current = head;
    while(current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    
    // Copiar del otro
    language = list.language;
    current = list.head;
    while(current != nullptr){
        add(current->entry);
        current = current->next;
    }
    
    return *this;
}

bool List::isEmpty() const{
    if(head==nullptr&&tail==nullptr)
        return true;
    return false;
}

int List::size() const{
    int cont=0;
    Node* currentNode=head;
    while(currentNode != nullptr){
        cont++;
        currentNode=currentNode->next;
    }
    
    return cont;
}

bool List::add(DictionaryEntry *entry){
    /*
    Ok let's see, we have a language 'X' right.
    So we extract from the entry the trasnlation that coinides w/that shi
    The missile knows where it is extracting that information from wher it isn't
    Now we have strings, maybe I can do an array of these strings so as to have it more confortable when comparing, it ain't necessary
    THen I compare with a for character by character, I'll look up if there's some library or some shi that makes it easier, if not
    maybe I can create an array with all letters in order, but that's fucking unbearable and has a time complexity of O(fucking forever)

    So, we now theoritaclly have a way of knowing if this word comes before or after any word.
    We find the first position in which the word would come before, and use that number to asign it that position. 
    With that first word, we need to create a new Node that points toward it, and is pointed by what it used to be the previous one

    Holy mother of fuck
    */
    if(entry==nullptr)
        return false;
    string tsWord=entry->getWord().getTranslation(this->language);
    if(tsWord=="-")
        return false;
    /*
    Ok I may have overestimated my own knowlegde on linked lists
    How the fuck did I run through it again?
    So I have the head, cool, and the head has a next. Cool cool cool
    Now I knoe how to go from 0 to 1, aight I had an idea
    */
    Node* currentNode = this->head;
    vector<string> alldeer;
    for(int i=0;i<size();i++){
        alldeer.push_back(currentNode->entry->getWord().getTranslation(this->language));
        currentNode=currentNode->next;
    }

    //ok this might just work and everyone is happy
    //So now I have the word and the words, now I need to order ts. FUck me man.
    //OK WE ARE SO IN. Por primera vez C++ no da puto sífilis, y ya implementa esto de base
    //I used to pray for times like this
    int pos=0;
    for(int i=0;i<alldeer.size();i++){
        if(tsWord==alldeer.at(i)){//aqui no seguira con el resto de la logica, porque no se anade
            return false;
        }
        if(tsWord>alldeer.at(i)){//la primera vez qu esto se cumpla, es la posicion en la que quiero meterlo.
            //de momento me lo voy a guardar fuera del bucle
            pos=i+1;
        }
    }
    //ahora puedo hacer un bucle para llegar a currentNode=el puto nodo que quiero
    //tiene que haber una forma mejor, pero como no se PUTO LEER, it is what it is nigga
    Node* desiredNode = this->head;
    Node* prevNode = nullptr;//aqui guardamos el anterior, para no hacer otro for. Esto VA A FALLAR SEGURÍSIMO
    for(int i=0;i<pos;i++){
        prevNode=desiredNode;
        desiredNode=desiredNode->next;//creo que con esto ya tengo el nodo que toca
    }
    //Ahora viene lo complicado
    Node* entrante = new Node(entry);
    entrante->next=desiredNode;
    if(prevNode != nullptr){
        prevNode->next=entrante;
    } else {
        head = entrante;
    }
    if(entrante->next == nullptr){
        tail = entrante;
    }
    //no ha sido tan complicado. (ESTO SEGURO QUE NO FUNCIONA NI POR ACCIDENTE, YO CREO QUE NI COMPILA)
    return true;
}




bool List::remove(string word){
    //utilizo findexact para comparar cada entry
    Node* currentNode=head;
    Node* nextNode;
    Node* prevNode=nullptr;
    for (int i=0;i<size();i++){
        nextNode=currentNode->next;
        if (currentNode->entry == findExact(word)){//este es el que hay que eliminar
            if(prevNode != nullptr){
                prevNode->next=nextNode;
            } else {
                head = nextNode;
            }
            if(currentNode == tail){
                tail = prevNode;
            }
            delete currentNode;//zamn
            return true;
        }
        prevNode=currentNode;
        currentNode=currentNode->next;
    }
    return false;
}

bool List::remove(int index){
    Node* currentNode=head;
    Node* nextNode;
    Node* prevNode=nullptr;
    if(index>=size())
        return false;
    for(int i=0;i<index;i++){
        prevNode=currentNode;
        currentNode=currentNode->next;
    }
    //despues del for las variables de nodo deberian de estar correctamente posicionadas, igulmente voy a meterlo dentro con un if
    nextNode=currentNode->next;
    if(prevNode != nullptr){
        prevNode->next=nextNode;
    } else {
        head = nextNode;
    }
    if(currentNode == tail){
        tail = prevNode;
    }
    delete currentNode;//zamn
    return true;
}

DictionaryEntry* List::get(int index) const{
    Node* currentNode=head;
    for(int i=0;i<index;i++){
        if(currentNode == nullptr) return nullptr;
        currentNode=currentNode->next;
    }
    if(currentNode == nullptr) return nullptr;
    return currentNode->entry;
}

DictionaryEntry* List::findExact(string word) const{
    Node* currentNode=head;

    while(currentNode != nullptr){
        if(currentNode->entry->getWord().getTranslation(this->language)==word){
            return currentNode->entry;
        }
        currentNode=currentNode->next;
    }
    return nullptr;
}

int calcularDistancia(const string &p, const string &q) {
    int sumaP = 0, sumaQ = 0;

    // Sumar ASCII de la cadena p
    for(char c : p) {
        sumaP += int(c);
    }
    // Sumar ASCII de la cadena q
    for(char c : q) {
        sumaQ += int(c);
    }

    long long cuadradoP = 1LL * sumaP * sumaP;
    long long cuadradoQ = 1LL * sumaQ * sumaQ;

    double numerador = sqrt(abs(cuadradoP - cuadradoQ));
    int denominador = p.length() + q.length();

    if (denominador == 0) return 0; // Evitar división por cero

    return static_cast<int>(numerador / denominador); // División entera
}

DictionaryEntry* List::findNearest(string word) const{
    if(head==nullptr)
        return nullptr;
    
    DictionaryEntry* closest=head->entry;
    Node* currentNode=head;
    int shortest=calcularDistancia(head->entry->getWord().getTranslation(language),word);
    
    while(currentNode != nullptr){
        int dist = calcularDistancia(currentNode->entry->getWord().getTranslation(language), word);
        if(dist < shortest){
            shortest = dist;
            closest = currentNode->entry;
        }
        currentNode=currentNode->next;
    }
    return closest;
}

ostream& operator<<(ostream &os, List &list) {
    // Mostrar el idioma de la lista
    os << list.language << endl;
    
    // Recorrer la lista desde el inicio
    List::Node* current = list.head;
    while (current != nullptr) {
        // Mostrar la entrada del nodo actual
        if (current->entry != nullptr) {
            os << *(current->entry) << endl;
        }
        current = current->next;
    }
    
    return os;
}
void List::clear(){
    List::Node* current = head;
    while(current != nullptr){
        List::Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}