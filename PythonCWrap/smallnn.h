#pragma once
#ifndef Net_H
#define Net_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           psuedoclass Neuron                                                      //
//-------------------------------------------------------------------------------------------------------------------//
// members: outputValue (float) - pretty much self-explanatory, the Neurons outputted value                          //
//          outputWeights  (Connection *) -- weights are multiplied to output, delta                                 //
//          index (Unsigned) -- index of the neuron in array                                                         //
//          gradient (float) -- computed with derivative to learn                                                    //
//  static  eta (float) -- Neural Network learning rate                                                              //
//  static  alpha (float) -- Momentum (fraction of previous delta weight)                                            //
// functions: Net makeNeuron (unsigned, unsigned) -- fully-initialized Neuron object just like a C++ constructor     //
//           void feedForward (Neuron *, Neuron *, unsigned) -- forward propagates the neuron                        //
//           float transferFunction (float) -- returns the tanh of the input                                         //
//           float transferFunctionDerivative (float) -- returns the 1 - input squared                               //
//           void calcOutputGradients (Neuron *, float) -- based on output change (delta) gradient                   //
//           void calcHiddenGradients (Neuron *, Neuron *, unsigned) -- based on dow gradient                        //
//          float sumDOW(Neuron *, Neuron *, unsigned) -- return sum of weights of next layer                        //
//           void updateInputWeights (Neuron *, Neuron *, unsigned) -- changes in weights                            //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float randomWeight() {
	return rand() / (float)RAND_MAX;
}

struct CONNECTION {
	float weight;
	float deltaweight;
}; typedef struct CONNECTION Connection;

struct NEURON {
	float outputValue;
	Connection * outputWeights;
	unsigned index;
	float gradient;
}; typedef struct NEURON Neuron;

const float eta = 0.15f; //tunables
const float alpha = 0.55f;

Neuron makeNeuron(unsigned numOutputs, unsigned index) {
	unsigned c;
	Neuron n = { 0.f, (Connection *)malloc(sizeof(Connection)*numOutputs), index, 0.f };// , &feedForwardNeuron};
	for (c = 0; c < numOutputs; ++c) {
		n.outputWeights[c].weight = randomWeight();
		n.outputWeights[c].deltaweight = 0.f;
	}
	return n;
}

float transferFunction(float s) {
	return (float)tanh(s); //tanh range output range -1 to 1
}

float transferFunctionDerivative(float s) {
	return 1.f - (s * s);
}

void feedForwardNeuron(Neuron * const self, Neuron * prevLayer, unsigned plsize) {
	float sum = 0.0f;
	for (unsigned m = 0; m < plsize + 1; ++m)
		sum += prevLayer[m].outputValue * prevLayer[m].outputWeights[self->index].weight;
	self->outputValue = transferFunction(sum);
}



float sumDOW(Neuron * const self, Neuron * nextLayer, unsigned nlsize) {
	float sum = 0.f;
	for (unsigned n = 0; n < nlsize; ++n)
		sum += self->outputWeights[n].weight * nextLayer[n].gradient;
	return sum;
}

void calcOutputGradients(Neuron * const self, float * targetVal) {
	float delta = *targetVal - self->outputValue;
	self->gradient = delta * transferFunctionDerivative(self->outputValue);
	printf("new OP gradient: %f - %f = %f\n", *targetVal, self->outputValue, self->gradient);
}
void calcHiddenGradients(Neuron * const self, Neuron * nextLayer, unsigned nlsize) {
	float dow = sumDOW(self, nextLayer, nlsize);
	self->gradient = dow * transferFunctionDerivative(self->outputValue);
	printf("new Hidden gradient: %f\n", self->gradient);
}

void updateInputWeights(Neuron * const self, Neuron * prevLayer, unsigned plsize) {
	for (unsigned n = 0; n < plsize + 1; ++n) {
		Neuron neuron = prevLayer[n];
    float oldDeltaWeight = neuron.outputWeights[self->index].deltaweight;
		float newDeltaWeight =
			eta // Learning rate
			* neuron.outputValue //
			* self->gradient
			+ alpha //Also add momentum = a fraction of the previous delta weight
			* oldDeltaWeight;
		neuron.outputWeights[self->index].deltaweight = newDeltaWeight;
		neuron.outputWeights[self->index].weight += newDeltaWeight; //i am dumb... wow
    //printf("New DeltaWeight for neuron #%d: %.2f\nNew Weight for neuron #%d: %.2f\n", self->index, newDeltaWeight, self->index,);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           psuedoclass Net                                                         //
//-------------------------------------------------------------------------------------------------------------------//
// members: layers (Neuron **) --was implemented previously as a vector<vector<Neuron>>                              //
//          top  (Unsigned *) -- was a vector<unsigned>                                                              //
//          size (Unsigned) -- size for topology pointer                                                             //
//          error, recentAverageError, recentAverageSmoothingFactor (float) -- used to calculate gradient descent    //
// functions: Net makeNet (unsigned *, unsigned) -- fully-initialized Net object just like a C++ constructor         //
//           void feedForward (Net *, const float[], unsigned) -- forward propagates the network                     //
//           void backProp (Net *, const float[], unsigned) -- adjusts all neurons in network                        //
//           void getResults (Net *, float *, unsigned) -- stores the networks results in float *                    //
//           void destroyLayers (Net *) -- frees memory allocated from makeNet                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct NET Net; //Following a C++ tutorial, tring to make objects in C... lets do it
struct NET {
	Neuron ** layers;
	unsigned size;
	unsigned * top;
	float error, recentAverageError, recentAverageSmoothingFactor;
};

Net makeNet(unsigned * top, unsigned size) {
	unsigned i;
	Neuron ** layers = (Neuron **)malloc(size * sizeof(Neuron *));
	for (i = 0; i < size; ++i)
		layers[i] = (Neuron *)malloc((top[i] + 1) * sizeof(Neuron)); //+1 for bias neuron
	for (unsigned layerNum = 0; layerNum < size; ++layerNum) {
		unsigned numOutputs = layerNum == size - 1 ? 0 : top[layerNum + 1];
		for (unsigned neuronNum = 0; neuronNum <= top[layerNum]; ++neuronNum)
			layers[layerNum][neuronNum] = makeNeuron(numOutputs, neuronNum);
		layers[size-1][top[layerNum]-1].outputValue = 1.0f; //force the bias node's output
	}
	Net self = { layers , size, top, 0.f, 0.f, 100.f }; //, &feedForwardNet, &backPropNet, &getResultsNet };
	return self;
}

void destroyLayers(Net * self) {
	for (unsigned i = 0; i < self->size - 1; ++i) free(self->layers[i]);
	free(self->layers);
}
void feedForwardNet(Net * const self, const unsigned * inputVals) {
	for (unsigned i = 0; i < self->top[0]; ++i)
		self->layers[0][i].outputValue = (float)inputVals[i];
	for (unsigned layerNum = 1; layerNum < self->size; ++layerNum) {
		for (unsigned n = 0; n < self->top[layerNum]; ++n)
			feedForwardNeuron(&self->layers[layerNum][n], self->layers[layerNum -1], self->top[layerNum -1]);
	}
}

void backPropNet(Net * const self, const unsigned * targetVals) {
	Neuron * outputLayer = self->layers[self->size - 1];
  //RMS of output neuron errors
	self->error = 0.f;
	for (unsigned n = 0; n < self->top[self->size - 1]; ++n) {
		float delta = targetVals[n] - outputLayer[n].outputValue;
		self->error += delta * delta;
	} //error is now sum of the squares
	self->error /= self->top[self->size - 1]; //get average
	self->error = (float)sqrt(self->error); //RMS
	self->recentAverageError = (self->recentAverageError * self->recentAverageSmoothingFactor
		+ self->error) / (self->recentAverageSmoothingFactor + 1.0f); //help keep track of shit
	printf("recentAverageError: %f\n", self->recentAverageError);
  //calc output and hidden gradients
	for (unsigned n = 0; n < self->top[self->size - 1]; ++n)
		calcOutputGradients(&outputLayer[n], (float *)&targetVals[n]); //take address to avoid warning casting pointer to smaller integer type
	for (unsigned l = self->size - 2; l > 0; --l) {
		Neuron * hiddenLayer = self->layers[l];
		Neuron * nextLayer = self->layers[l + 1];
		for (unsigned n = 0; n < self->top[l] + 1; ++n)
			calcHiddenGradients(&hiddenLayer[n], nextLayer, self->top[l + 1]);
	}
	for (unsigned l = self->size - 1; l > 0; --l) {
		Neuron * currLayer = self->layers[l];
		Neuron * prevLayer = self->layers[l - 1];
		for (unsigned n = 0; n < self->top[l] + 1; ++n)
			updateInputWeights(&currLayer[n], prevLayer, self->top[l - 1]);
	}
}

void getResultsNet(Net * const self, float * resultVals) {
	for (unsigned n = 0; n < self->top[self->size - 1]; ++n)
		resultVals[n] = self->layers[self->size - 1][n].outputValue;
}
#endif
