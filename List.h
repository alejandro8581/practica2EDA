#ifndef LIST_H
#define LIST_H
#include "DictionaryEntry.h"

#include <cmath>
using namespace std;

// Declaración anticipada
class OrderedDictionary;  

class List{
    private:
        class Node{
            friend class List;
            friend ostream& operator<<(ostream &os, List &list);  
            friend ostream& operator<<(ostream &os, const OrderedDictionary &od);  
            private:
                DictionaryEntry *entry;
                Node *next;
            public:
                Node();
                Node(DictionaryEntry *entry);
                friend ostream& operator<<(ostream &os, Node &node);
                
        };
        
        char language;
        Node *head;
        Node *tail;
        
        // IMPORTANTE: Añadir friend aquí también para que OrderedDictionary pueda acceder a head/tail
        friend ostream& operator<<(ostream &os, const OrderedDictionary &od);
        
    public:
        List();
        List(char languages);
        ~List();
        List(const List& list);
        List& operator=(const List& list); 
        bool isEmpty() const;
        int size() const;
        bool add(DictionaryEntry *entry);
        bool remove(string word);
        bool remove(int index);
        void clear();
        DictionaryEntry* get(int index) const;
        DictionaryEntry* findExact(string word) const;
        DictionaryEntry* findNearest(string word) const;
        friend ostream& operator<<(ostream &os, List &list);
        
};
#endif