#include <cmath>
#include <random>
#include <iostream>

double uniform_distribution_generator(double mean, double variance, std::string identifier)
{
    double lower_bound = mean - sqrt(3 * variance);
    double upper_bound = mean + sqrt(3 * variance);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lower_bound, upper_bound);
    double random_number = dis(gen);
    std::cout << "Generated a random number with identifier: " << identifier << std::endl;
    return random_number;
}






