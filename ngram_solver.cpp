#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "ngram_solver.h"

using namespace std;

ngram_solver::ngram_solver(int num) {
    if (num <= 0) {
        throw runtime_error("n must be greater than 0");
    }
    n = num;
    srand(time(nullptr));
}

void ngram_solver::read_file(const string& filename) {
    ngram_map.clear();
    words.clear();
    
    ifstream input(filename);
    if (!input.is_open()) {
        throw runtime_error("cannot open file");
    }
    
    // Read all words into a vector
    string word;
    while (input >> word) {
        words.push_back(word);
    }
    
    if (words.size() < static_cast<size_t>(n)) {
        throw runtime_error("file input size < n");
    }
    
    // Build n-gram map using words
    // Seed = first (n-1) words, next word = nth word
    for (size_t i = 0; i + n <= words.size(); i++) {
        // Build seed from n-1 words
        string seed = "";
        for (int j = 0; j < n - 1; j++) {
            if (j > 0) seed += " ";
            seed += words[i + j];
        }
        // Store the next word
        string next_word = words[i + n - 1];
        ngram_map[seed].push_back(next_word);
    }
    
    // Initialize with random seed
    size_t rand_start = rand() % (words.size() - n + 1);
    curr_seed = "";
    for (int j = 0; j < n - 1; j++) {
        if (j > 0) curr_seed += " ";
        curr_seed += words[rand_start + j];
    }
}

string ngram_solver::current_seed() const {
    if (curr_seed.empty() && n != 1) {
        throw runtime_error("seed not initialized yet");
    }
    return curr_seed;
}

string ngram_solver::next_word() {
    if (curr_seed.empty() && n != 1) {
        throw runtime_error("seed not initialized yet");
    }
    
    // If current seed has no next words, pick new random seed
    while (ngram_map.find(curr_seed) == ngram_map.end() || 
           ngram_map[curr_seed].empty()) {
        size_t rand_start = rand() % (words.size() - n + 1);
        curr_seed = "";
        for (int j = 0; j < n - 1; j++) {
            if (j > 0) curr_seed += " ";
            curr_seed += words[rand_start + j];
        }
    }
    
    // Pick random next word from possibilities
    vector<string>& possibilities = ngram_map[curr_seed];
    string next = possibilities[rand() % possibilities.size()];
    
    // Update seed: remove first word, add new word
    if (n > 1) {
        size_t space_pos = curr_seed.find(' ');
        if (space_pos != string::npos) {
            curr_seed = curr_seed.substr(space_pos + 1) + " " + next;
        } else {
            curr_seed = next;
        }
    }
    
    return next;
}