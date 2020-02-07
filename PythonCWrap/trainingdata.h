#pragma once
#ifndef TrainingData_H
#define TrainingData_H
#include <stdio.h>
#include <stdlib.h>
#include "py_string.h"
/* */

struct TRAININGDATA {
	FILE * trainingDataFile;
}; typedef struct TRAININGDATA TrainingData;

TrainingData makeTrainingData(const char * filePath) {
	TrainingData t = { fopen(filePath, "r") };
	return t;
}

unsigned * getTopology(TrainingData * t, unsigned * layerCount) {
	char line[MAX_LINE];
	unsigned * readTopology;
	fgets(line, MAX_LINE, t->trainingDataFile);
	if (strncmp(line, "topology_size:", 14) == 0)
		*layerCount = line[15] - '0';
	readTopology = (unsigned *)malloc(sizeof(unsigned) * *layerCount);
	fgets(line, MAX_LINE, t->trainingDataFile);
	if (strncmp(line, "topology:", 9) == 0) {
		strcpy(line, line + 9);
		for (unsigned i = 0; i < *layerCount; ++i)
			sscanf(line + (i * 2), "%d", &readTopology[i]);
	}
	return readTopology;
}

void getNextInputs(TrainingData * t, unsigned * inputVals, unsigned size) {
  	char * line = (char *)malloc(MAX_LINE);
	fgets(line, MAX_LINE, t->trainingDataFile);
  	printf("got the line %s\n", line);
	if (strncmp(line, "in:", 3) == 0) {
    char * line_chop = line + 3; //point past first 3 chars!
		for (unsigned i = 0; i < size; ++i)
			sscanf(line_chop + (i * 2), "%d", &inputVals[i]);
	}
  free(line);
}

void getTargetOutputs(TrainingData * t, unsigned * targetVals, unsigned size) {
	char * line = (char *)malloc(MAX_LINE);
	fgets(line, MAX_LINE, t->trainingDataFile);
  	printf("got the line %s\n", line);
	if (strncmp(line, "out:", 4) == 0) {
    char * line_chop = line + 4; //point past first 4 characters
		for (unsigned i = 0; i < size; ++i)
			sscanf(line_chop + (i * 2), "%d", &targetVals[i]);
  }
  free(line);
}
#endif
