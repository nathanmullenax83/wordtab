#ifndef SEQUENCER_TPP
#define SEQUENCER_TPP

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <deque>
#include <algorithm>
#include <random>
#include <cstdlib>
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
                //cout << compact_vector(prefix) << " => " << compact_vector(suffix) << std::endl;
            }
        }
    }

    vector<size_t> right( vector<size_t> const &es, size_t n ) {
        vector<size_t> vs;
        for( size_t i=es.size()-n; i<es.size(); ++i ) {
            vs.push_back( es[i]);
        }
        return vs;
    }

    vector<size_t> random_prefix() {
        auto a = data.begin();
        size_t width = data.size();
        size_t elem = rand()%width;
        while( elem-- > 0) {
            ++a;
        }
        return a->first;
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
        pair<size_t, size_t> m = models[model];
        for( auto it=data.begin(); it != data.end(); ++it) {
            // prefix length matches
            if( it->first.size()==m.first ) {
                // get all suffixes
                vector<size_t> prefix = it->first;
                for( size_t i=0; i<it->second.size(); ++i) {
                    vector<size_t> suffix = it->second[i];
                    if( suffix.size() == m.second ) {
                        cout << compact_vector(prefix) << "\t" << compact_vector(suffix) << "\n";
                    }
                }
            }
        }
    }

    vector<size_t> random_rule( vector<size_t> const &prefix ) {
        if( data.count(prefix) ) {
            // table contains rules for prefix
            vector< vector<size_t> > rhss = data[prefix];
            return rhss[std::rand()%rhss.size()];
        } else {
            // no applicable rule. Returning empty set.
            return vector<size_t>();
        }
    }

    

    vector<size_t> generate( size_t model, size_t length ) {
        if( model >= models.size() ) { throw 1; }
        pair<size_t, size_t> m = models[model];
        vector<size_t> prefix;
        while( prefix.size() != m.first ) {
            prefix = random_prefix();
        }
        vector<size_t> generated;
        for( size_t w: prefix ) {
            generated.push_back(w);
        }
        while( generated.size() < length ) {
            vector<size_t> suffix = random_rule(prefix);
            // if we run out of rules, append a valid prefix
            // and continue.
            if( suffix.size()==0 ) {
                suffix = random_prefix();
            }
            size_t psize = prefix.size();
            for(size_t w:suffix) {
                generated.push_back(w);
                prefix.push_back(w);
            }
            prefix = right( prefix, m.first );
        }
        return generated;
    }
};

#endif
