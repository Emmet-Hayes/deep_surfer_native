#pragma once
#ifndef File_String_H
#define File_String_H
/* C almost like OOP
 - make structures to hold data members like classes
 - use typedef to sidestep the struct keyword every time you want to make a struct
 - make constructor functions like a class would have near the struct definition
 - write functions that would normally be encapsulated in the class taking a pointer to structure reference (self)
 - use function pointers to emulate polymorphism, can create other initializer functions calling different functions
 - another plus of doing that is that when calling the function the struct must reference itself in the call
 - however you must pass a pointer to the structure itself
 - you must pass the size of an array as an argument to a function, no STL C++ .size() .push_back() magic stuff
 */
struct FILE_STRING {
	const char * path;
	const char * content;
	size_t length;
	int lines;
};
typedef struct FILE_STRING file_string;
#endif