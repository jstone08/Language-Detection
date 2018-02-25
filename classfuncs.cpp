//
// classfuncs.cpp
//
//
//    Created: Nov 15, 2015
//    Authority: Jordan Stone
//
//

#include<iostream>
#include<fstream>
#include "trigram.h"
#include "language.h"
using namespace std;

// Name: TrigramVector constructor
// Purpose: The cosntructor goes in and initilizes the private variables 
//	    which will later be extracted.
// Arguments: none
// Returns: none
TrigramVector::TrigramVector()
{
	capacity = CAP;
	used = 0;
	create_reference_vec();
	create_all_grams();
	trigrams = new string[capacity];
	gram_counts = new int[capacity];
	for(int i = 0; i < capacity; i++){
		trigrams[i] = EMPTY;
		gram_counts[i] = 0;
	}
	for(int i=0; i < GRAM_CAP; i++){
		all_freqs[i] = 0;
	}
}

// Name: file_decode
// Purpose: The purpose of this funciton is to read in the text file and 
// 	    then break up the text file into individual characters that is 
//	    then added to the private string textLine array. 
// Arguments: The file name, string fName
// Returns: This function does not return any values. It modifies the 
// 	    private variable textLine
void TrigramVector::file_decode(string fName, string lName)
{
	char c;
	ifstream finput;
	string text = EMPTY;
       	fileName = fName;
	langName = lName;
	finput.open(fName.c_str());
	if (!finput.is_open()){
		cout << "Cannot open" << " doc1" << endl;
	}
       	while (finput.get(c)){
		text += c;
	}
	textLine = text;
	finput.close();
}

// Name: get_text
// Purpose: The purpose of this function is to extract the private variable
//	    that will store the large string of clean text.
// Arguments: none
// Returns: none
string TrigramVector::get_text()
{
	return textLine;
}

// Name: big_cleaner
// Purpose: The purpose of this function is to clean the textLine string 
//	    more indepth than the quick cleaner. This function will remove
//	    large whitespaces, and will make all chars lowercase.
// Arguments: the large textLine string
// Returns: returns the completely cleaned textLine string
string TrigramVector::big_cleaner(string textLine)
{
	char a;
	string cleanLine ="";
	int len = textLine.length();
	for(int i=0; i < len; i++){
		a = textLine[i];
		if(isalpha(a)){
		       	a = tolower(a);
	       		cleanLine += a;
		} 
		else if (isspace(a)){
			if ((i == len-1) || isalpha(textLine[i+1]))
			cleanLine += ONE_SPACE; 
		}
       	}
	return cleanLine;	
}

// Name: create_gram
// Purpose: This function creates the trigrams from the textLine string, 
//	    stores them in a dynamic array.
// Arguments: the textLine string cleaned from the text file
// Returns: none
void TrigramVector::create_gram(string textLine)
{
	int length = textLine.length();
	for (int i = 0; i < length - 2; i++){
		for (int j = 0; j < 3; j++){
			trigrams[i] += textLine[i+j];
		}
		used++;
		if (used == capacity){
			expand();
		}
	} 
} 	       

// Name: expand
// Purpose: This function is the keystone fucntion for the dynamic array 
//	    and provides the trigram array with its flexibility.
// Arguments: none
// Returns: none, mods the private variables of the TrigramVector
void TrigramVector::expand()
{
	int newCapacity = 2*capacity + 1;
	string *new_arr = new string[newCapacity];
	int *new_arr2 = new int[newCapacity];
	for(int i = 0; i < capacity; i++){
		new_arr[i] = trigrams[i];
		new_arr2[i] = gram_counts[i];
	}
        delete[] trigrams;
	delete[] gram_counts;
	trigrams = new_arr;
	gram_counts = new_arr2;
	capacity = newCapacity;
}


// Name: get_file
// Purpose: The purpose of this function is to extract the private variable
//	    file to store the file name.
// Arguments: none 
// Returns: none
string TrigramVector::get_file_name()
{
	return fileName;
}

// Name: get_lang_name
// Arguments: none
// Purpose: the purpose of this function is to access the language name 
// Returns: a string, the inputted language name
string TrigramVector::get_lang_name()
{
	return langName;
}
// Name: make_lang_name
// Arguments: a string, the language
// Purpose: The purpose of this function is to set the language name
// Returns: none
void TrigramVector::make_lang_name(string str)
{
	langName = str;
}


// Name: get_capacity
// Purpose: The purpose of this function is to extract the private variable
//	    used to discern the number of trigrams stored.
// Arguments: none
// Returns: none
int TrigramVector::get_capacity()
{
	return used;
}

// Name: get_grams
// Purpose: The purpose of this function is to extract the private variable
//	    trigrams to print the trigrams to the screen.
// Arguments: none
// Returns: none
string TrigramVector::get_grams(int i)
{
	return trigrams[i];
}

// Name: get_count
// Arguments: integer i, the index in the file trigram array
// Purpose: The purpose of this function is to get the file trigram 
//	    frequencies
// Returns: int i, the individual trigram frequency in the file
int TrigramVector::get_count(int i)
{
	return gram_counts[i];
}

// Name: count_grams
// Arguments: an instance of a trigram vector class, a language
// Purpose: the purpose of this function is to allow individual language
//          files to access the TV class function to get trigram frequencies
// Returns: none
void TrigramVector::count_grams(TrigramVector trig1)
{
	trig1.warning = 0;
	for(int i=0; i < used ; i++){
		for(int j = 0; j < used; j++){
			if(trigrams[i] == trigrams[j])
				gram_counts[i]++;
		}
	}
}

// Name: print_freq
// Arguments: none
// Purpose:prints out the trigram frequenciess for a file
// Returns:none
void TrigramVector::print_freq()
{
	cout << "Frequency for " << get_file_name() << endl;
	int len = get_capacity();
	for(int i = 0; i < len; i++){
		cout << gram_counts[i] << " " << trigrams[i] << endl;
	}
	cout << "total trigrams " << used << endl;
}

// Name:create_all_grams
// Arguments: none
// Purpose: the purpose of this function is to create the 27^3 vector of tri
//	    grams to compare other vectors of frequenceis to get.
// Returns:none
void TrigramVector::create_all_grams()
{	
	int iter = 0;
	int i,j,k;
	for(i=0; i< 27; i++){
		for(j=0; j<27; j++){
			for(k=0; k<27; k++){
				all_grams[iter] += reference_vec[i];
				all_grams[iter] += reference_vec[j];
				all_grams[iter] += reference_vec[k];
			        iter++;
			}
		}
	}
}

// Name:create_reference_vec
// Purpose: create a vector of chars(alphabet)
// Arguments: none
// Returns:none
void TrigramVector :: create_reference_vec()
{
	reference_vec[0] = ONE_SPACE;
	reference_vec[1] = 'a';

	for(int i = 2; i < 27; i++){
		reference_vec[i] = reference_vec[i-1] +1;
	}
}

// Name: freq_counter
// Arguments: an instance of a trigramvector class, to be used by the lang
//	      class.
// Purpose: The purpose of this function is to develop the frequenices of 
// 	    trigrams out of all possibilities for comaprisons in similarity
// Returns: none
void TrigramVector::freq_counter(TrigramVector trig1)
{
	
	int limit = trig1.get_capacity();
	for(int i = 0; i < GRAM_CAP; i++){	
		for(int j =0; j< limit; j++){
			if(all_grams[i] == trig1.get_grams(j)){
				all_freqs[i]++;
			}
		}
	}
}

// Name: get_all_freqs
// Arguments: an integer i for indexing purposes
// Purpose: this is an accessor function to get the frequencies of the large
//	    trigram vector for analysis in similarity
// Returns:an integer, the frequenceis of the trigram out of all pos t.g.'s
int TrigramVector::get_all_freqs(int i)
{
	return all_freqs[i];
}

// Name: update_used
// Arguments: an instance of a trigramvector, to be used by the language
//	      class.
// Purpose: The purpose of this function is to update the number of trigrams
//	    after each file has been analyzed
// Returns: none
void TrigramVector::update_used(TrigramVector trig1)
{
	used += trig1.get_capacity();
}
