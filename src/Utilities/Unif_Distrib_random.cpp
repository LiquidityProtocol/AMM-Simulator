#include <cmath>
#include <random>

uniform_distribution_generator::uniform_distribution_generator(double mean, double variance, int sample_size)
{
    double lower_bound = mean - sqrt(3 * variance);
    double upper_bound = mean + sqrt(3 * variance);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> d(lower_bound, upper_bound);
    return d(gen);
}






