#pragma once
#ifndef Py_Object_H
#define Py_Object_H
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "file_string.h"
#define MAX_LINE 400
#define MAX_FILE 300000 //feel free to change

typedef struct PY_STRING py_string;
struct PY_STRING {
	file_string f_s;
	void * ext; //basically its an object that can hold as much as it needs to hold. always has to be cast
	void(*set_ext)(py_string *, char *); //like member functions of a class (for virtuals)
	void(*set_file_string)(py_string *, const char *); //otherwise you dont need to put the functions in the struct...
};

void py_ext_func(py_string * self, char * i) {
	self->ext = (void *)i;
}

void py_set_new_file_path(py_string * self, const char * new_path) {
	self->f_s.path = new_path;
}

py_string make_py_string(const char * file_path) {
	FILE * fp = fopen(file_path, "r");
	char* all = (char *)malloc(sizeof(char)*MAX_FILE);
	char line[MAX_LINE];
	int i;
	for (i = 0; fgets(line, MAX_LINE, fp) != NULL; ++i) strcat(all, line);
	py_string self = { {file_path, all, strlen(all), i }, (void *)"Py Object", &py_ext_func, &py_set_new_file_path };
	fclose(fp);
	return self;
};

void shift_py_string_default(py_string * self) {
	self->ext = (void *)"Default Py Object"; //C++ requires the cast, C does not
}

void shift_py_string_new(py_string * self, void * new_thing) {
	self->ext = (void *)new_thing;
}
#endif