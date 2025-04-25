#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(string& candidate, const string& in, string remaining_floating, size_t pos, const set<string>& dict, set<string>& results);



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string candidate = in;
    wordleHelper(candidate, in, floating, 0, dict, results);

    return results;

}

// Define any helper functions here
void wordleHelper(string& candidate, const string& in, string remaining_floating, size_t pos, const set<string>& dict, set<string>& results){

    if(pos == in.length()){
        if(remaining_floating.empty()){

             if(dict.find(candidate)!=dict.end()){
                results.insert(candidate);
                }

        return;

        }
    }
       

    if(in[pos]!='-'){
        candidate[pos] = in[pos];
        wordleHelper(candidate, in, remaining_floating, pos+1, dict, results);
        return;
    }

    size_t remaining_blanks = 0;
    for(size_t i=pos; i<in.length(); i++){

        if(in[i] == '-'){
            remaining_blanks++;
        }
    }

    for(size_t i=0; i<remaining_floating.length(); i++){


        char floatChar = remaining_floating[i];
        candidate[pos] = floatChar;

        string new_remaining = remaining_floating;
        new_remaining.erase(i,1);

        wordleHelper(candidate, in, new_remaining, pos+1, dict, results);

    }

    if(remaining_blanks>remaining_floating.length()){

        for(char c='a'; c<='z'; c++){

            bool skip = false;
            for(size_t j =-0; j<remaining_floating.length(); j++){

                if(c==remaining_floating[j]){

                    skip = true;
                    break;
                }
            }

            if(!skip){
                candidate[pos] = c;
                wordleHelper(candidate, in, remaining_floating, pos+1, dict, results);
            }
        }
    }

    }
