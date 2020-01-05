#ifndef FORMATTER_TPP
#define FORMATTER_TPP
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "dictionary.tpp"
#include "sequencer.tpp"

using std::vector, std::cout, std::string, std::stringstream, std::cin;

class Formatter {
private:
public:
    static void print( vector<string> const &ws, size_t target_width=60, string const &space=" ") {
        size_t len(0); // length of the current line.
        for( string w:ws ) {
            if( len + w.size() < target_width ) {
                cout << w;
                cout << space;
                len += w.size() + 1;
            } else {
                cout << "\n" << w << space;
                len = w.size()+1;
            }
        }
    }

    template< class T>
    static T parse( string const &s ) {
        stringstream vs;
        vs << s;
        T v;
        vs >> v;
        return v;
    }

    

    static vector<string> parse_args( int argc, char **argv ) {
        vector<string> args;
        for( int i=0; i<argc; ++i) {
            args.push_back( argv[i] );
        }
        return args;
    }

    void read( Dictionary &dict, Sequencer &seq, std::istream &in ) {
        string w;
        while( in >> w ) {
            size_t W = dict.define(w);
            seq.append(W);
        }
    }

    void read_chars( Dictionary &dict, Sequencer &seq, std::istream &in ) {
        string w(".");
        char c;
        while( (c = in.get()) !=EOF ) {
            w[0] = c;
            seq.append(dict.define(w));
        }
    }
};

#endif