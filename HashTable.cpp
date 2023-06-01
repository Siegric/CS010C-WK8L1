#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "HashTable.h"
#include "WordEntry.h"

// Default constructor
HashTable::HashTable(int s) {
    size = s;
    hashTable = new list<WordEntry>[size]; // Makes a new list of WordEntry for the hash table
}

// Destructor
HashTable::~HashTable() {
    size = 0;
    delete[] hashTable; // Deallocates the dynamically allocated hash table
}

// Function to compute the hash value for a given input string
int HashTable::computeHash(const string &s) {
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
        hash = hash + (int)s[i];
    return hash % size; // Makes sure the hash value is not greater than the given size
}

// Insert operation to add a word and its score to the hash table
void HashTable::put(const string &s, int score) {
    int hash = computeHash(s);
    for (auto &it : hashTable[hash]) {
        if (it.getWord() == s) {
            it.addNewAppearance(score); // If the word already exists, update its appearance with the new score
            return;
        }
    }
    hashTable[hash].push_back(WordEntry(s, score)); // If the word doesn't exist, create a new WordEntry and add it to the bucket
}

// Function to get the average score of a given word
double HashTable::getAverage(const string &s) {
    if (contains(s)) {
        int hash = computeHash(s);
        for (auto &it : hashTable[hash]) {
            if (it.getWord() == s)
                return it.getAverage(); // If the word is found, return its average score
        }
    }
    return 2.0; // If the word is not found, return a default average score of 2.0
}

// Function to check if a given word exists in the hash table
bool HashTable::contains(const string &s) {
    int hash = computeHash(s);
    for (auto &it : hashTable[hash]) {
        if (it.getWord() == s)
            return true; // If the word is found, return true
    }
    return false; // If the word is not found, return false
}

int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}
