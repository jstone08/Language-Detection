//
// language.cpp
//   
//   Created: Nov 30, 2015
//   Author: Jordan Stone
//
#include<iostream>
#include<fstream>
#include"trigram.h"
#include"language.h"
using namespace std;

// Name: Language constructor
// Purpose: The cosntructor goes in and initilizes the private variables 
//	    which will later be extracted.
// Arguments: none
// Returns: none
Language::Language()
{
	langs = new TrigramVector[CAP];
	number_of_langs = 0;
	capacity = 0;
}

// Name: add_lang
// Purpose: to add a language into the language class
// Arguments: a TrigramVector instance and a string language
// Returns:none
void Language::add_lang(TrigramVector trig1, string lang)
{
	bool language_known =false;	
	for(int i = 0; i < number_of_langs; i++){
	 	if((lang == langs[i].get_lang_name())){
			langs[i].freq_counter(trig1);
			langs[i].update_used(trig1);
			language_known = true;
		} 
	}
	if(language_known == false){
		expand();		
		langs[number_of_langs].make_lang_name(lang);
		langs[number_of_langs].freq_counter(trig1);
		langs[number_of_langs].update_used(trig1);
		number_of_langs++;
	}		
}

// Name: expand
// Purpose: This function will increase the size of the dynamic array of 
// 	    language names.
// Arguments: none
// Returns: none
void Language::expand()
{
        int newCapacity = 2*capacity + 1;
        TrigramVector *new_arr = new TrigramVector[newCapacity];

        for(int i = 0; i < capacity; i++){
        	new_arr[i] = langs[i];
        }
	delete[] langs;
	langs = new_arr;
        capacity = newCapacity;
}

// Name: get_langs
// Purpose: The purpose of this fucntion is to access the vector of trigrams
//	    for a specified language.
// Arguments: An integer to index the different language trigram vectors.
// Returns: returns a vector of trigrams wich are associated with a lang.
TrigramVector Language::get_langs(int i)
{
	return langs[i];
}

// Name: get_number_of_langs
// Purpose: The purpose of this function is to access the total number of 
//	    languages inputted into the program.
// Arguments: none
// Returns: none
int Language:: get_number_of_langs()
{
	return number_of_langs;
}
