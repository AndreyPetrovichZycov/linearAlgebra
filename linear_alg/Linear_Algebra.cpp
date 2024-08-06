#include <iostream> 
#include "Linear.h"

using namespace std;


int main() {
    setlocale(LC_ALL, "RU");
    Matrix matr1(2, 3) ,matr2(3, 2);
    matr1(0, 0, 1), matr1(1, 0, 3), matr1(1, 1, 2), matr1(1, 2, 4), matr1(0, 2, 2);
    matr2(0, 0, 1), matr2(1, 0, 3), matr2(1, 1, 2), matr2(2, 1, 4), matr2(2, 0, 2);
    float mas[] = { 1,2,3};
    Vector vect1(mas, 3), vect2(2);
    cout << "matr1\n";
    show(matr1);
    cout << "matr2\n";
    show(matr2);
    cout << "vect1\n";
    show(vect1);
    //cout << "vect2\n";
    //vect2 = matr1 * vect1;
    //show(vect2);
    cout << "произведение вектора на матрицу v1 * matr2\n";
    //show(vect1 * matr2);
    cout << "определитель: \n";
    //cout<<det(matr1);
}