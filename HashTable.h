#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
	list<WordEntry> *hashTable;
	int size;

 public:
	HashTable(int);//Constuctor
	~HashTable(); //Destructor
	bool contains(const string &);//Search if the table contains given element
	double getAverage(const string &);
	void put(const string &, int);//Insert
 
 private:
	int computeHash(const string &);//Computes the hash for given input
	HashTable* operator=(const HashTable* rhs);//Assignment operator
	HashTable(HashTable* rhs);//Copy Constructor
};

#endif
