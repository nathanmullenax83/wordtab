#ifndef FORMATTER_TPP
#define FORMATTER_TPP
#include <vector>
#include <string>
#include <iostream>

using std::vector, std::cout, std::string;

class Formatter {
private:
public:
    static void print( vector<string> const &ws, size_t target_width=60) {
        size_t len(0); // length of the current line.
        for( string w:ws ) {
            if( len + w.size() < target_width ) {
                cout << w;
                cout << " ";
                len += w.size() + 1;
            } else {
                cout << "\n" << w << " ";
                len = w.size()+1;
            }
        }
    }
};

#endif