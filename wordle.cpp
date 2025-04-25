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
void wordleHelper(string& currentWord, const string& in, string unusedLetters, size_t pos, const set<string>& dict, set<string>& validWords);



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> validWords; 

    string currentWord = in;
    wordleHelper(currentWord, in, floating, 0, dict, validWords);//recursively searching

    return validWords;

}

// Define any helper functions here
void wordleHelper(string& currentWord, const string& in, string unusedLetters, size_t pos, const set<string>& dict, set<string>& validWords){

    if(pos == in.length()){ // when filled all psotions
        if(unusedLetters.empty()){ //if we used all the unused letters

             if(dict.find(currentWord)!=dict.end()){ //if word is valid

                validWords.insert(currentWord); //insert to results

                }

        return;

        }
    }
       

    if(in[pos]!='-'){ //if current position has a letter
        currentWord[pos] = in[pos];
        wordleHelper(currentWord, in, unusedLetters, pos+1, dict, validWords);
        return;
    }

    size_t remaining_blanks = 0;

    for(size_t i=pos; i<in.length(); i++){ //count the remaining blanks

        if(in[i] == '-'){
            remaining_blanks++;
        }
    }

    for(size_t i=0; i<unusedLetters.length(); i++){ //for each remaining letters


        char floatChar = unusedLetters[i];
        currentWord[pos] = floatChar;

        string new_remaining = unusedLetters;
        new_remaining.erase(i,1); //remove letter form unused letters

        wordleHelper(currentWord, in, new_remaining, pos+1, dict, validWords); //recursively fill next pos

    }

    if(remaining_blanks>unusedLetters.length()){ //if more balnks than floating letters

        for(char c='a'; c<='z'; c++){

            bool skip = false;
						
            for(size_t j =-0; j<unusedLetters.length(); j++){
                if(c==unusedLetters[j]){ //if letter is already in the floating letters
                    skip = true;
                    break;
                }
            }

            if(!skip){
                currentWord[pos] = c; //try current letter for pos
                wordleHelper(currentWord, in, unusedLetters, pos+1, dict, validWords); //recursively fill next pos
            }
        }
    }

    }
