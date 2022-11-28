/* Student Info
    Email: hjiang86@usc.edu
    Name: Hao Jiang
*/

#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "../lib/util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    /* Note:
    this function will only be called for product name, book author, and clothing brand, which contains only
    characters or other punctuations without numbers. So in this function, I consider anything other than a
    character as a punctuation.
    */

    // trim and make the rawWords lowercase
    rawWords = trim(rawWords);
    rawWords = convToLower(rawWords);

    // storage set
    set<string> s;

    // variable to store substring
    string keyword = "";

    for(string::iterator it = rawWords.begin(); it != rawWords.end(); ++it){
        // if it's a character (already lowercase)
        if(*it >= 'a' && *it <= 'z'){
            keyword += *it; // add to the string
        }

        // if it's punctuations
        else{
            // if keyword is valid and doesn't exist in set
            if(keyword.size() >= 2 && s.find(keyword) == s.end()){
                s.insert(keyword); // add keyword
            }
            keyword = "";
        }
    }
    // add the last one
    if(keyword.size() >= 2 && s.find(keyword) == s.end()){
        s.insert(keyword); // add keyword
    }

    return s;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
