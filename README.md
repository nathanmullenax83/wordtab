# Wordtab - Create data structures from text.
## Installing:
There is no install target, so you can only 'make' and not 'make install.'

$> make

Should produce the wordtab executable. 

## Usage:
Wordtab reads from standard input. 

Examples:

1. Generate Markov text from source text.
    
    markov <prefix_length> <suffix_length> text <word_count>

    $> cat file.txt | ./wordtab markov 2 2 text 1000

    Generates 1000 words of text with a Markov model with a prefix length of 2 and a suffix length of 2.

2. Generate table of rules from source text.
    
    markov <prefix_length> <suffix_length> table

## Example target:
The 'trotsky' folder contains a makefile that downloads some public domain text for generating tables. Pre-processing is a work in progress...
