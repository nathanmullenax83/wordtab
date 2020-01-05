#include <iostream>
#include <string>
#include <map>
#include <cctype>

#include "dictionary.tpp"
#include "sequencer.tpp"
#include "formatter.tpp"

using std::cin, std::string;

int main(int argc, char **argv) {

    Dictionary dict;
    Sequencer seq;
    Formatter console;

    vector<string> args = console.parse_args(argc, argv);
    
    // parse arguments
    if( args.size() == 6 && args[1]=="markov" ) {
        size_t prefix_length = console.parse<size_t>(args[2]);
        size_t suffix_length = console.parse<size_t>(args[3]);
        size_t model = seq.define_model( prefix_length, suffix_length );

        if( args[4]=="text" ) {
            console.read( dict, seq, cin );
            size_t length = console.parse<size_t>( args[5] );
            console.print( dict.decode(seq.generate(model,length)));
        } else if( args[4]=="words") {
            console.read_chars( dict, seq, cin );
            size_t length = console.parse<size_t>( args[5]);
            console.print( dict.decode(seq.generate(model,length)),80, "");
        }
    } else if( args.size() == 5 && args[1]=="markov" ) {
        size_t prefix_length = console.parse<size_t>(args[2]);
        size_t suffix_length = console.parse<size_t>(args[3]);
        size_t model = seq.define_model( prefix_length, suffix_length );
        console.read( dict, seq, cin );
        if( args[4]=="table") {
            seq.dump(model);
        }
    } else {
        cout << "Didn't recognize:\n\n";
        console.print(args);
    }

}