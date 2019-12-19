#ifndef SEQUENCER_TPP
#define SEQUENCER_TPP

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <deque>
#include <algorithm>
#include "dictionary.tpp"

using std::vector, std::pair, std::deque, std::max, std::cout;

string compact_vector( vector<size_t> const &vs ) {
    std::stringstream ss;
    ss << "< ";
    for( auto v: vs ) {
        ss << v << " ";
    }
    ss << ">";
    return ss.str();
}

class Sequencer {
private:
    vector< pair< size_t, size_t > > models;
    map< vector<size_t>, vector< vector< size_t> > > data;
    deque< size_t > window;

    size_t window_size() {
        size_t M(0);
        for( auto m : models ) {
            M = max( M, (m.first + m.second) );
        }
        return M;
    }

    void process_window() {
        for( auto m : models ) {
            if( m.first + m.second <= window.size() ) {
                vector<size_t> prefix;
                vector<size_t> suffix;

                for(size_t i=0; i<m.first; ++i) {
                    prefix.push_back(window[i]);
                }
                for(size_t j=m.first; j<m.first+m.second; ++j) {
                    suffix.push_back( window[j]);
                }
                data[prefix].push_back(suffix);
                cout << compact_vector(prefix) << " => " << compact_vector(suffix) << std::endl;
            }
        }
    }
public:
    size_t define_model( size_t prefix_len, size_t suffix_len ) {
        models.push_back( pair<size_t,size_t>(prefix_len,suffix_len));
        return models.size()-1;
    }

    void append( size_t w ) {
        window.push_back(w);
        if( window.size() > window_size() ) {
            window.pop_front();
        }
        process_window();
    }

    void dump( size_t model ) {

    }
};

#endif
