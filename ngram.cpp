#include <iostream>
#include <string>
#include "ngram_solver.h"

using namespace std;

void give_intro();
void read_file(ngram_solver & solver);
void generate_text(ngram_solver & solver, int num_words);

int main() {
    give_intro();
    cout << "What value of n do you want to use? ";
    int n;
    cin >> n;
    ngram_solver solver(n);
    read_file(solver);
    cout << "How many words of output do you want? ";
    int num_words;
    cin >> num_words;
    generate_text(solver, num_words);
    return 0;
}

void give_intro() {
    cout << "Welcome to the N-gram Solver.  You specify" << endl;
    cout << "the file to sample, the ngram size, and the" << endl;
    cout << "desired number of words of output and I'll" << endl;
    cout << "randomly generate some text." << endl;
    cout << endl;
}

void read_file(ngram_solver & solver) {
    cout << "What is the name of the text file? ";
    string file_name;
    cin >> file_name;
    solver.read_file(file_name);
}

void generate_text(ngram_solver & solver, int num_words) {
    cout << endl;
    
    // Print the initial seed
    string seed = solver.current_seed();
    cout << seed;
    int column = seed.length();
    int words_printed = 0;
    
    // Count words in seed
    for (char c : seed) {
        if (c == ' ') words_printed++;
    }
    words_printed++; // Add 1 for the last word
    
    // Generate remaining words
    for (int i = words_printed; i < num_words; i++) {
        string next = solver.next_word();
        
        // Insert line break after 65 characters when adding next word
        if (column + next.length() + 1 > 65) {
            cout << endl;
            cout << next;
            column = next.length();
        } else {
            cout << " " << next;
            column += next.length() + 1;
        }
    }
    cout << endl;
}