#ifndef DICTIONARY_TPP
#define DICTIONARY_TPP

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using std::map, std::vector, std::string;

class Dictionary {
private:
    map< string, size_t > indeces;
    vector<string> words;
    vector<size_t> counts;

public:
    Dictionary() {
        
    }

    /** define a word and return its ID **/
    size_t define( string const &w  ) {
        if( indeces.count(w)==0 ) {
            words.push_back(w);
            counts.push_back(1);
            indeces[w] = words.size()-1;
        } else {
            counts[indeces[w]]++;
        }
        return indeces[w];
    }

    size_t operator[] ( string const &w ) {
        if( indeces.count(w) ) {
            return indeces[w];
        }
        return 0;
    }

    void dump() {
        for( auto it=indeces.begin(); it!=indeces.end(); ++it) {
            std::cout << std::setw(8) << std::left << it->second << "\t";
            std::cout << std::setw(40) << std::left << it->first << "\t";
            std::cout << std::setw(8) << std::left << counts[it->second] << std::endl;
        }
    }

};

#endif