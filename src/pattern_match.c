#include <string.h>

#include "utils.h"

bool pattern_match(const char* string, const char* pattern){
    /*
        Checks whether a given string matches a given pattern.
        Returns true if it matches, false otherwise.
        
        The pattern is a string composed by letters and characters.
        Case-sensitive (for now)
        Allowed wildcards are:
        ? - which stands for one single character, can be anything
        * - which stands for any possible sub-string, even an empty one
    */

    if(check_empty_string(string) || check_empty_string(pattern)) return false;
    
    unsigned int slen = strlen(string);
    unsigned int plen = strlen(pattern);
    unsigned int s_index = 0;
    unsigned int p_index = 0;
    
    while(s_index<slen || p_index<plen){

        // Each time a '?' occurs, skip a character in the string
        if(pattern[p_index] == '?'){
            p_index++;
            s_index++;
        }
        // Each time a '*' occurs, look for the next character (not '*')
        else if(pattern[p_index] == '*'){
            while(p_index<plen && (pattern[p_index]=='*' || pattern[p_index]=='?')) p_index++;
            if(p_index >= plen) return true;

            while(s_index < slen) {
                while(s_index<slen && string[s_index]!=pattern[p_index]) s_index++;
                
                if(!pattern_match(&string[s_index], &pattern[p_index])) s_index++;
                else return true;
            }
        }
        // Each time a 'normal character' occurs, check if equal: if not, return false
        else{
            if(string[s_index] != pattern[p_index]) return false;
            p_index++;
            s_index++;
        }
    }
    
    return s_index>=slen && p_index>=plen;
}