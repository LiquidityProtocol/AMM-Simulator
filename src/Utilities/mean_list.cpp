#include "mean_list.h"
#include <iostream>
#include <vector>

using namespace std;

mean_list::mean_list(const std::vector<double> &list)
{
    int n = list.size()  ;
        int m = std::min(10, n) ;  // take the minimum of 10 and the size of the list
        double sum = 0 ;
        for (int i = n - m; i < n; i++)
            {
            sum +=  list[i] ;
            }
        return  sum / m ;


}
