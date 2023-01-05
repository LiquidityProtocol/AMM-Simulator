#include <cmath>
#include <random>

double sample_uniform_distribution(double mean, double variance) {
  // Create a uniform distribution with the given mean and variance
  std::uniform_real_distribution<double> distribution(mean - variance / 2, mean + variance / 2);

  // Get a random number generator
  std::random_device rd;
  std::mt19937 generator(rd());

  // Generate and return a sample from the distribution
  return distribution(generator);
}

