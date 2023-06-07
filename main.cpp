#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{
    Matrix A;
    cin >> A;
    cout << "Matrix A is: " << A << endl;

    Matrix B;
    cin >> B;
    cout << "Matrix B is: " << B << endl;

    Matrix C = A + B;
    cout << "A + B is: " << C << endl;

    Matrix D = A - B;
    cout << "A - B is: " << D << endl;

    Matrix E = A * B;
    cout << "A * B is: " << E << endl;

    Matrix J = B * A;
    cout << "B * A is: " << J << endl;

    cout << "The determinant of A is: " << A.determinant() << endl << endl;
    cout << "The determinant of B is: " << B.determinant() << endl << endl;
    
    Matrix F = A % A;
    cout << "The inverse matrix of A is: " << F << endl;

    Matrix G = B % B;
    cout << "The inverse matrix of B is: " << G << endl;

    Matrix H = A * G;
    cout << "Matrix A 'divided' by matrix B is: " << H << endl;

    Matrix I = B * F;
    cout << "Matrix B 'divided' by matrix A is: " << I << endl;

    cout << "If only I had used Eigen3 for the matrix inversion.." << endl;

    return 0;
}
