#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
    private:
        double rows;
        double columns;
        vector<vector<double>> data;

    public:

    Matrix();                       //default constructor
    Matrix(int rows, int columns);  //constructor with parameters
    Matrix(const Matrix& other);    //copy constructor
    ~Matrix();                      //destructor

    friend istream& operator>>(istream& in, Matrix& matrix);        //overloaded stream extraction >>, used to get user input
    friend ostream& operator<<(ostream& out, const Matrix& matrix); //overloaded stream insertion <<, used to print matrices

    Matrix &operator=(const Matrix& other); //assignment operator overload

    //overloaded arithmetical operators:
    Matrix operator+(const Matrix& other) const; // +
    Matrix operator-(const Matrix& other) const; // -
    Matrix operator*(const Matrix& other) const; // *
    Matrix operator%(const Matrix& other) const; // %, used for inverse

    double determinant() const;                     //determinant calculation
    Matrix calculateInverse(const Matrix& matrix);  //matrix inversion

};

#endif  // MATRIX_H
