#include<ctype.h>

bool isVowel(char ch){
	ch = tolower(ch);
    if('a' == ch || 'e' == ch || 'i' == ch || 'o' == ch || 'u' == ch) return true;
    return false;        
}
