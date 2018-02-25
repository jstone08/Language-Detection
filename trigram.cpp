//
// trigram.cpp
//
//   Created: Nov 12, 2015
//   Author: Jordan Stone
//
//   purpose: The purpose of this program is to analyze text files and break
//     	      them down into "trigrams", which are three-character snippets 
//	      of text. Using these trigrams, the program will learn which 
//	      trigrams are associated with different languages and then will
//	      be able to detect languages by comparing the realtive
//	      frequencies of trigrams out of all possible combinations of
//	      trigrams to determine the likelihood that it is a certain 
//	      language.  

#include<iostream>
#include<fstream>
#include "trigram.h"
#include "language.h"
#include <math.h>
using namespace std;

void similarity(TrigramVector trig1, Language lang1);

int main()
{
	string fName,lang,fText;
	Language lang1;
	while (cin >> lang >> fName){
	       	TrigramVector trig1;
       		trig1.file_decode(fName, lang);
		fText = trig1.get_text();
       		fText = trig1.big_cleaner(fText);
       		trig1.create_gram(fText);
       		trig1.count_grams(trig1);
//             	trig1.print_freq();
		if(lang != "Unknown"){
			lang1.add_lang(trig1, lang);
		}else{
			trig1.freq_counter(trig1);
		      	similarity(trig1,lang1);
		}
	}
}
///////////////////////////important note/////////////////////////////////
// -this function is greater than 30 lines long, I was unable to decipher 
//  how to break it up without compleetly altering the rest of my math part
//  or violating the 80-char width line rule. I decided this was the lesser
//  of two evils.

// Name: similarity
// Purpose: The purpose of this function is to get the value of the 
//	    cosine similarity between the unknown file and a language.
// Arguments: none
// Returns: none
void similarity(TrigramVector trig1, Language lang1)
{
	int number_of_langs = lang1.get_number_of_langs();
	double similarity_vec[number_of_langs];
	TrigramVector *langs;
	langs  = new TrigramVector[number_of_langs];
	for(int i = 0; i < number_of_langs; i++){
		langs[i] = lang1.get_langs(i);
	}
       	for(int i = 0; i < number_of_langs; i++){
		double numerator=0.0000;
		double denom_lang=0.0000;
	        double denom_textFile=0.0000;
		for (int y = 0; y < GRAM_CAP ; y++){ 
	       		numerator += ((double)trig1.get_all_freqs(y) / 
	       		     (double)trig1.get_capacity())
     	     		* ((double)langs[i].get_all_freqs(y) /
	       		   (double)langs[i].get_capacity());
	       		denom_textFile +=pow(((double)trig1.get_all_freqs(y)
      			       /(double)trig1.get_capacity()),2);
	       		denom_lang +=pow((((double)langs[i].get_all_freqs(y)
				      )/(double)langs[i].get_capacity()),2);
		}
		denom_textFile = sqrt(denom_textFile);
		denom_lang = sqrt(denom_lang);
		similarity_vec[i] = numerator/(denom_lang * denom_textFile);
	}
	double x_sim;
	TrigramVector x_lang;
	for(int i = 0; i < number_of_langs; i++){
		for(int j = 0; j < number_of_langs-1; j++){
			if(similarity_vec[j+1] > similarity_vec[j]){
				x_sim = similarity_vec[j];
				x_lang = langs[j];
				similarity_vec[j] = similarity_vec[j+1];
				langs[j] = langs[j+1];
				similarity_vec[j+1] = x_sim;
				langs[j+1] = x_lang;
			}
		}
	}
	cout<< trig1.get_file_name() << endl;
       	for(int i = 0; i < number_of_langs;i++){
	       	cout << langs[i].get_lang_name() << ": " << 
	       		similarity_vec[i] << endl;
	}		
}

