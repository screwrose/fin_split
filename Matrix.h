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
        Matrix();
        Matrix(int rows, int columns);
        Matrix(const Matrix& other);
        ~Matrix();

        friend istream& operator>>(istream& in, Matrix& matrix);
        friend ostream& operator<<(ostream& out, const Matrix& matrix);

        Matrix& operator=(const Matrix& other);

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator%(const Matrix& other) const;

        double determinant() const;
        Matrix calculateInverse(const Matrix& matrix);
};

#endif  // MATRIX_H
