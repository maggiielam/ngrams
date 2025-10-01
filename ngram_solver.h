#ifndef NGRAM_SOLVER_H
#define NGRAM_SOLVER_H

#include <string>
#include <map>

using namespace std;

// this class is an ngram solver than can generate n-grams,
//      which generates a sequence of n characters randomly from characters
//      from an input file
class ngram_solver {
 public:
    // constructs an ngram_solver for the given value of n.
    // throws a runtime error if n is <= 0
    ngram_solver(int n);

    // reads given file and intializes seed
    // throws a runtime error if the filename is invalid
    //      or the input size < n
    void read_file(const string& filename);

    // returns the current seed of the generator
    // throws a runtime error if seed is not initialized yet
    string current_seed() const;

    // returns a word that completes an ngram using the current seed,
    //      then updates the seed
    // throws a runtime error if seed has not been initialized yet
    string next_word();

 private:
    // the value of n we want to generate ngrams for
    int n;

    // map storing seeds as keys and values as characters completing the ngram
    map<string, vector<string> > ngram_map;

    // current seed
    string curr_seed;

    // text of file as a vector
    vector<string> words;
};

#endif
