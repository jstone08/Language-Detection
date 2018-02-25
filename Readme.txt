//////////////////////////////Readme/////////////////////////////////////
Jordan Stone
11/20/15
Language Detection

	This program is a primitive form of Google Translate. It reads
intitial text files and parses them into three character strings, which 
are called trigrams. These initial text files have known languages and 
their relative trigram frequencies for each language are saved to be used 
for comparison later. When unknown-language text files are inputted into 
the program, the relative trigram frequences are compared with the saved
trigram frequencies using cosine similary to determine the language 
probability. The program output produces a table with the percentage 
similarity to the known languages.

Design:

The design of this program has been optimized for comprehension.
	-First, a file is read into the program.
	
	-A TrigramVector class is initilized after every file is inputted.
	 , the constructor initilizes the private members of the class 
 	 for each file. 
	 
	-Each file is  read in character by character.It is then cleaned and 
	 stripped of the non alpha-numeric characters, whitespaces, and 
	 uppercase.

	-This string is then copied into a private variable so it can be 
	 easily manipulated in the rest of the program.
	 
	-The program contains extraction functions that will 
 	 obtain private variables for each file in order to aid in the 
	 development of trigrams for the file or language file.

	-After this, the string is ready to be broken up into trigrams using
	 a dynamic array. 
	 
	-Once the trigrams have been assembled, they are saved. Then the 
	 main function will print the file name then the output of the 
 	 trigram array.
	 
	-Then the program decides if the unputted file is a known language
	 or an unknown language. 
	 
	-If it is a known language the trigam frequencies are counted and
	and the language is saved into its own close and can be augmented
	if more files of the same language type are discovered. The 
	relative frequencies of the trigrams out of all possible 
	combinations are saved for comparing against unknown files.

	-If the language is unknown then the frequencies are calculated
	and then compared against the realtive frequencies of all of the
	inputted languages using cosine similarity
     
	Classes:
	
		TrigramVector
	This class holds an array of trigrams. It holds functions that break
	 apart and comprehend textfiles, as well as functions that develop 
	 trigrams from the text file. It holds many accessor functions that
	the language class will use inorder to develop trigram frequencies 
	and creates the large array of all possible trigram combinations.


		Language
	This class takes the TrigramVector that has been filtered out to
	be a language and then immediately checks if the language exists.
	If it does, it gets added to the existing language class, if its new
	it gets its own language with the name entered with the file. It 
	will also compile the trigram frequencies of the language for 
	comparisons between the language and an unknown file.

Operating Instructions:
	The user simply inputs the text file after starting the program.
	ex: ./trigrams < input_files/phase1_test0.txt
 

	To compile: 

	clang++ -Wall -Wextra -g trigram.cpp classfuncs.cpp language.cpp -o trigrams
