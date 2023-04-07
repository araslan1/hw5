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



string alphabet = "abcdefghijklmnopqrstuvwxyz"; 

// Add prototypes of helper functions here
void combos(set<string> &return_set,
     std::string in,
    std::string floating,
    const std::set<std::string>& dict, int location, std::string next, int number_of_any_letters);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> myset; 
    string next = in; 
    int number_of_dashes = 0; 
    int number_of_any_letters = 0; 
    for (int i = 0; i < in.size(); i++){
        if (in[i] == '-') number_of_dashes++; 
    }
    number_of_any_letters = number_of_dashes - floating.size(); 
    combos(myset, in, floating, dict, 0, next, number_of_any_letters);
    return myset; 

}

void combos(set<string> &return_set,
     std::string in,
    std::string floating,
    const std::set<std::string> &dict, int location, std::string next, int number_of_any_letters)
{   
    if (location == in.size()){
      return; 
    }
    if (next[location] != '-'){
        if (location == in.size()-1){
          if (dict.find(next) != dict.end()) return_set.insert(next); 
        }
        int x = location + 1;
        combos(return_set, in, floating, dict, x, next, number_of_any_letters); 
    }else{
      if (number_of_any_letters > 0){
        for (int i = 0; i < alphabet.size(); i++){
          next[location] = alphabet[i]; 
          if (location == in.size()-1){
            if (dict.find(next) != dict.end()) return_set.insert(next); 

          }
          int x = location + 1; 
          int z = number_of_any_letters -1;
          combos(return_set, in, floating, dict, x, next, z); 
        }
      }

      for (int i = 0; i < floating.size(); i++){
        string temp = floating; 
          next[location] = temp[i]; 
          temp.erase(i, 1); 
          if (location == in.size()-1){
            if (dict.find(next) != dict.end()) return_set.insert(next); 
          }
          int x = location + 1; 
          combos(return_set, in, temp, dict, x, next, number_of_any_letters); 
        
        
        
      }
    }
}


// Define any helper functions here
