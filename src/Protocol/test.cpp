#include <iostream>
#include <typeinfo>

using namespace std;

class Combi {};

int main()  {
    Combi *ptr = new Combi();
    cout << typeid(ptr).name();
}