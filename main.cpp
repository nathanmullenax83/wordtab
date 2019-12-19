#include <iostream>
#include <string>
#include <map>

#include "dictionary.tpp"
#include "sequencer.tpp"

using std::cin, std::string;

int main(int argc, char **argv) {
    Dictionary dict;
    Sequencer seq;

    size_t model_1_1 = seq.define_model(1,1);
    size_t model_2_1 = seq.define_model(2,1);
    size_t model_3_2 = seq.define_model(3,2);

    string w;
    while( cin >> w ) {
        size_t W = dict.define(w);
        seq.append(W);
    }
    dict.dump();
    seq.dump( model_3_2 );
    vector< size_t > wids = seq.generate( model_2_1, 100 );
    vector< string > ws = dict.decode(wids);
    
}