#include <iostream>
#include <string>
#include <map>

#include "dictionary.tpp"
#include "sequencer.tpp"
#include "formatter.tpp"

using std::cin, std::string;

int main(int argc, char **argv) {
    

    Dictionary dict;
    Sequencer seq;
    Formatter console;

    vector<string> args = console.parse_args(argc, argv);
    console.print(args);

    
    // parse arguments
    if( args.size() == 6 && args[1]=="markov" ) {
        size_t prefix_length = console.parse<size_t>(args[2]);
        size_t suffix_length = console.parse<size_t>(args[3]);
        size_t model = seq.define_model( prefix_length, suffix_length );
        
        console.read( dict, seq, cin );
        if( args[4]=="text" ) {
            size_t length = console.parse<size_t>( args[5] );
            console.print( dict.decode(seq.generate(model,length)));
        }
    }

}