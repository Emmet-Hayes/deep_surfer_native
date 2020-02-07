/*              C_DEEP_SURFER
@AUTHOR: Emmet Hayes
Authors Note
 This project is primarily an very high-level interface between C and Python.
 The python scripts run tensorflow neural networks for different applications,
 like text/music/image generation, etc...
 I also implemented a very tiny neural net capable of very basic I/O.
 I was so tempted, but I want to focus on C and not use any C++. 
 I need to get comfortable with void * type and function pointers too.
 Calls neural networks from python, currently no parameters can be passed from C,
 soon that will change.
 I am exploring object-oriented functionality that can be explored with structures,
 functions and function pointers to emulate a class in C.
 The internet doesn't seem to want to give a straight answer as to whether or not
 C is actually faster than C++, but since C has a smaller toolkit it will force me
 to make the neural net logic in a certain way and conserve to keep it super fast..
 It is intended that none of the python scripts require any information from the C
 environment; they are totally encapsulated within themselves, and this way we can utilize
 python scripts using tensorflow in EAGER EXECUTION MODE, and then choose to run a
 different script using GRAPH EXECUTION!!!
 The mininet is crazy fast!!! I'm having trouble with it's back propagation, somewhere
 the gradient isn't working i think... i took this algorithm from an old c++ project
 i made and did a fake OOP thing to it (no polymorphic classes or inheritance, no need
 for c++ really) except that it was using VECTORS and i'm using old fashioned POINTERS
 to STRUCTS BABY
 */

#define PY_SSIZE_T_CLEAN
#include <C:\Users\ehaye\AppData\Local\Continuum\anaconda3\include\Python.h>
#include <time.h>
#include "trainingdata.h"
#include "smallnn.h"
#include "py_string.h" //
#include "polyderivative.c"

#define INPUT_BUFFER 100

void run_py(const char * file_path) {
	//Py_SetProgramName(Py_DecodeLocale("Deep_Surfer_Full", NULL));
	Py_Initialize();
	PyRun_SimpleString(make_py_string(file_path).f_s.content);
}

const char * get_path_from_user(char user_in[]) {
	while (1) { //infinity
		printf("Please enter the AI Functions you would like to open:\nmininet\n"
			"deepdream\ntextgenerator\nmusicgenerator\nimageclassifier\nimagegenerator\n"
			"deepsurfer\nstyletransfer\npolegame\nacrobotgame\nfrozenlakegame\nmountaincargame\n"
      "taxigame\nmariogame\npolynomialderivativeintegral\npokedex\nquit (to exit program)\n\nc_deep_surfer:");
		int o = scanf("%s%*c", user_in); //gets WHOLE LINE are throws out char enter key
		for (char *l = user_in; *l; ++l) *l = tolower(*l); //lower case string
		if (strcmp(user_in, "quit") == 0 || strcmp(user_in, "") == 0) return "quit"; //
		else if (strcmp(user_in, "mininet") == 0 || strcmp(user_in, "datatest") == 0) return user_in;
		else if (strcmp(user_in, "poly") == 0) return "poly";
		else if (strcmp(user_in, "pokedex") == 0) return "pokedex";
		strcat(user_in, ".py"); 
		if (fopen(user_in, "r") != NULL) 
			break; //we can stop asking user to either quit or give a valid file...
		else printf("Didn't understand your command! Starting over.\n");
	}
	return user_in;
}

int test_data() {
	unsigned net_size = 1, trainingStep = 0;
	TrainingData data = makeTrainingData("./text/smallnndata.txt");
	unsigned * topology = getTopology(&data, &net_size);
	Net net = makeNet(topology, net_size);
	printf("topology is:\n");
	for (unsigned i = 0; i < net_size; ++i)
		printf("%d\n", topology[i]);
	unsigned * inputVals = (unsigned *)malloc(sizeof(unsigned) * topology[0]),
		*targetVals = (unsigned *)malloc(sizeof(unsigned) * topology[net_size - 1]);
	float * resultVals = (float *)malloc(sizeof(float) * topology[net_size - 1]);
	clock_t begin = clock();
	while (!feof(data.trainingDataFile)) {
		++trainingStep;
		getNextInputs(&data, inputVals, topology[0]);
		feedForwardNet(&net, inputVals);
		getTargetOutputs(&data, &targetVals, topology[net_size - 1]);
		getResultsNet(&net, &resultVals);
		backPropNet(&net, targetVals);
		if (trainingStep % 100 == 0) {
			printf("Pass #%d\nInputs: ", trainingStep);
			for (unsigned i = 0; i < topology[0]; ++i) printf("%d\t", inputVals[i]);
			printf("\nOutputs: ");
			for (unsigned i = 0; i < topology[net_size - 1]; ++i) printf("%.2f\t", resultVals[i]);
			printf("\nTargets: ");
			for (unsigned i = 0; i < topology[net_size - 1]; ++i) printf("%d\t", targetVals[i]);
			printf("\nNet Recent Average Error: %f\n", net.recentAverageError);
		}
	}
	clock_t end = clock();
	printf("Total time spent learning: %f secs.\n", (float)(end - begin)/CLOCKS_PER_SEC);
	free(topology);
	free(inputVals);
	free(targetVals);
	free(resultVals);
	destroyLayers(&net);
	return 0;
}

int main_menu() {
	char ui[INPUT_BUFFER];
	while (1) { //main program loop
		const char * path = get_path_from_user(ui);
		if (strcmp(path, "quit") == 0)
			break;
		else if (strcmp(path, "mininet") == 0);
			//test_data();
		else if (strcmp(path, "poly") == 0)
			polynomialderivativeintegral();
		else if (strcmp(path, "pokedex") == 0)
			mainPokemonMenu();
		else if (strcmp(path, "deepsurfer.py") == 0 || strcmp(path, "deepdream.py") == 0 ||
			strcmp(path, "imageclassifier.py") == 0 || strcmp(path, "musicgenerator.py") == 0 ||
			strcmp(path, "textgenerator.py") == 0   || strcmp(path, "styletransfer.py") == 0 ||
			strcmp(path, "polegame.py") == 0        || strcmp(path, "acrobotgame.py") == 0 ||
      		strcmp(path, "taxigame.py") == 0        || strcmp(path, "frozenlakegame.py") == 0 ||
      		strcmp(path, "mountaincargame.py") == 0 || strcmp(path, "mariogame.py") == 0 ||
			strcmp(path, "cnnkeras.py") == 0)
             run_py(path);
	}
	printf("Press the enter key to continue...\n");
	scanf("%[^\n]%*c", ui);
	return 0;
}

int main() {
	return main_menu();
}
