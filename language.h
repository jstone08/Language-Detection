#ifndef LANGUAGE_H
#define LANGUAGE_H
//
// language.h
//
//   Created: Nov 12, 2015
//   Author:  Jordan Stone
//
//
///////////////////////// Language class definition /////////////////////////
class Language
{
    public:
	Language(); //constructor
       	void add_lang(TrigramVector trig1, string lang);//adds a language
	TrigramVector get_langs(int i);//access the language names
	int get_number_of_langs();//acesses the number of langs added
   
    private:
	int capacity;//number of trigrams in the language file
	void expand();//expands the number of languages added
	int number_of_langs;
	TrigramVector *langs;
};
#endif
