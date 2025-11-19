#ifndef METADATA_H
#define METADATA_H
#include "Word.h"
#include <iostream>
using namespace std;
class Metadata{
friend ostream & operator<<(ostream &, const Metadata &);
private:
    string category;
    int usageCount;
public:
    Metadata();
    Metadata(string category);
    ~Metadata();
    Metadata(const Metadata &metadata);
    Metadata & operator=(const Metadata &metadata);
    string getCategory() const;
    int getUsageCount() const;
    void setCategory(string category);
    void incrementUsage();
    bool operator==(const Metadata &metadata) const;
    friend ostream & operator<<(ostream &os, const Metadata &metadata);



};
#endif