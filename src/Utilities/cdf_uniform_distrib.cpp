#include <cmath>

double uniform_cdf(double x, double mean, double variance) {
  // Calculate the standard deviation of the uniform distribution
  double std_dev = sqrt(variance);

  // Calculate the lower and upper bounds of the uniform distribution
  double lower_bound = mean - std_dev;
  double upper_bound = mean + std_dev;

  // Return the CDF of the uniform distribution
  if (x < lower_bound) {
    return 0.0;
  } else if (x >= upper_bound) {
    return 1.0;
  } else {
    return (x - lower_bound) / (upper_bound - lower_bound);
  }
}

