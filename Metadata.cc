#include "Word.h"
#include "Metadata.h"
using namespace std;
Metadata::Metadata() : category("unknown"), usageCount(0){}

Metadata::Metadata(string cat):Metadata(){
        if(!cat.empty()){
            category=cat;
            usageCount=0;
        }
}
Metadata::Metadata(const Metadata &m){
    category=m.category;
    usageCount=m.usageCount;
}

Metadata::~Metadata(){
    
}
Metadata & Metadata::operator=(const Metadata &metadata) {
    if (this != &metadata) { // Check for self-assignment
        category = metadata.category;
        usageCount = metadata.usageCount;
    }
    return *this; // Return the current object to allow chaining
}
string Metadata::getCategory() const{
    return this->category;
}
int Metadata::getUsageCount() const{
    return this->usageCount;
}
void Metadata::setCategory(string cat){
    //no se si tendre que comprobar que no sea null o algo, de momento lo hago tal cual
    this->category=cat;
}
void Metadata::incrementUsage(){
    this->usageCount++;
}
ostream & operator<<(ostream &os, const Metadata &metadata) {
    os << "[" << metadata.category << "] used:" << metadata.usageCount << "times";
    return os; // vuelves a retornar lo mismo para encadenar
}
bool Metadata::operator==(const Metadata &metadata) const {
    return (this->getCategory()==metadata.getCategory() && this->getUsageCount()==metadata.getUsageCount());
}
//[verb] used: 0 times

