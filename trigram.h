#ifndef TRIGRAM_H
#define TRIGRAM_H

// trigram.h
//
//    Created: Nov 15, 2015
//    Author: Jordan Stone
//
///////////////////////// TrigramVector class definition ///////////////////
using namespace std;
 
const string EMPTY = "";
const char ONE_SPACE = ' ';
const int CAP = 1000;
const int GRAM_CAP = 19683;


class TrigramVector
{
    public:
	void file_decode(string fName, string lang); //reads in the text 
	//						file and builds str
	string get_text(); 
	string big_cleaner(string textLine);//cleans string for A/N,uppercase
	//				    and whitespaces
	void create_gram(string textLine);// creates trigrams from string
	TrigramVector(); //constructor
	string get_file_name();// accesses the file name
	string get_lang_name();// access the associated language name
	void make_lang_name(string str);//sets the language name
	int get_capacity();//access the number of trigrams used
	
	string get_grams(int i);//access the individual trigrams
	void create_reference_vec();//creates an alphabet
	int get_count(int i);//access the number of individual trigram 
//				frequency
	void count_grams(TrigramVector trig1);//calucates indivudal freqs
	void create_all_grams();//creates 27^3 possible trgigrams
	string all_grams[GRAM_CAP];// intiialize all grams array
	int  all_freqs[GRAM_CAP];// initilizes all freqs array
	void print_freq();//////////////print freq///////////////////////
    	void freq_counter(TrigramVector trig1);//calulates the frequnceis 
//		       of 27^3 trigrams in the input files
	void update_used(TrigramVector trig1);// incriments used
	int get_all_freqs(int i);//access the individual frequencies bigarr
	char reference_vec[27];// intiilizes alphabet

    private:
	int capacity;//capacity of starting dynamic array
	string *trigrams;// vector of trigrams
	string fileName;
	string langName;
	string textLine;//broken up string into arr of chars
	int used;//number of trigrams in file
	void expand();//dynamic array func
	int *gram_counts;
	int warning; //gets rid of warnings
};

#endif
