#include "normal_distribution_generator.h"
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

normal_distribution_generator::normal_distribution_generator(double mean, double variance, int sample_size)
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<>d(mean, sqrt(variance) );
    return d(gen);
};


// example test:  double sample = normal_distribution_generator(0, 1, 10);
