#include <iostream> 
#include "linear_algebra.h"
#include <random>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    Matrix M(2,2);
    float mas[2] = {1,2};
    Vector v(mas, 2);
    v(0, (float)exp(1));

    show(v);


}