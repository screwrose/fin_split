#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

Matrix::Matrix() : rows(0), columns(0) {}                                                                       //default constructor
Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns), data(rows, vector<double>(columns)) {}    //constructor with parameters
Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns), data(other.data) {}             //copy constructor
Matrix::~Matrix() {}                                                                                            //destructor

//get user input
istream& operator>>(istream& in, Matrix& matrix)
{
    cout << "Enter the amount of rows: ";
    in >> matrix.rows;
    cout << "Enter the amount of columns: ";
    in >> matrix.columns;

    matrix.data.resize(matrix.rows, vector<double>(matrix.columns));

    cout << "Enter the matrix elements:" << endl;
    for (int i = 0; i < matrix.rows; i++) 
    {
        for (int j = 0; j < matrix.columns; j++) 
        {
            in >> matrix.data[i][j];
        }
    }
    return in;
}

//print matrices
ostream& operator<<(ostream& out, const Matrix& matrix) 
{
    out << "Matrix Size: " << matrix.rows << " x " << matrix.columns << endl;
    for (int i = 0; i < matrix.rows; i++) 
    {
        for (int j = 0; j < matrix.columns; j++) 
        {
            out << matrix.data[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

//assignment operator
Matrix&Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        rows = other.rows;
        columns = other.columns;
        data = other.data;
    }
    return *this;
}

//matrix sum
Matrix Matrix::operator+(const Matrix& other) const 
{
    Matrix result(rows, columns);
    if (rows != other.rows || columns != other.columns) 
    {
        cout << "Error: The dimension of the matrices do not match, therefore they cannot be summed" << endl;
        return result;
    }
    result.data.resize(rows, vector<double>(columns));
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

//matrix subtract
Matrix Matrix::operator-(const Matrix& other) const 
{
    Matrix result(rows, columns);
    if (rows != other.rows || columns != other.columns) 
    {
        cout << "Error: The dimension of the matrices do not match, therefore they cannot be subtracted" << endl;
        return result;
    }
    result.data.resize(rows, vector<double>(columns));
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

//matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const
{
    Matrix result(rows, other.columns);
    if (columns != other.rows) {
        cout << "Error: The amount of columns of matrix A is not equivalent to the amount of rows of matrix B. They cannot be multiplied." << endl;
        return result;
    }
    result.data.resize(rows, vector<double>(other.columns));
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < other.columns; j++) 
        {
            for (int k = 0; k < columns; k++) 
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

//determinant
double Matrix::determinant() const
{
    if ( rows != columns )
    {
        cout << "The matrix is not square, therefore a determinant cannot be calculated.";
        return 0.0;
    }

    vector<vector<double>> tempData = data; //clone the vector holding the values of the matrix
    int n = rows;
    double det = 1.0;
    for (int i=0; i<n; i++) 
    {
        int maxRow = i;
        for (int j= i+1 ; j< n; j++) 
        {
            if (abs(tempData[j][i]) > abs(tempData[maxRow][i])) 
            {
                maxRow = j;
            }
        }
        if (maxRow != i) 
        {
            swap(tempData[i], tempData[maxRow]);
            det *= -1.0;
        }
        if (tempData[i][i] == 0.0) 
        {
            return 0.0;
        }
        det *= tempData[i][i];
        for (int j = i + 1; j < n; j++) 
        {
            double factor = tempData[j][i] / tempData[i][i];
            for (int k = i + 1; k < n; k++) 
            {
                tempData[j][k] -= factor * tempData[i][k];
            }
        }
    }
    return det;
}

//matrix inversion
Matrix Matrix::operator%(const Matrix& other) const
{
    //check if the matrix is square
    if (rows != columns)
    {
        throw runtime_error("Matrix must be square to calculate its inverse.");
    }

    //create an identity matrix of the same size as the original matrix
    Matrix identity(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            identity.data[i][j] = (i == j) ? 1.0 : 0.0; // enters 1s on the main diagonal
        }
    }

    //create a copy of the original matrix to perform the operations
    Matrix matrix = other;

    //perform Gaussian elimination to obtain an upper triangular matrix
    for (int i = 0; i < rows; i++)
    {
        //find the pivot row
        int pivotRow = i;
        for (int j = i + 1; j < rows; j++)
        {
            if (abs(matrix.data[j][i]) > abs(matrix.data[pivotRow][i]))
            {
                pivotRow = j;
            }
        }

        //swap the current row with the pivot row
        if (pivotRow != i)
        {
            swap(matrix.data[i], matrix.data[pivotRow]);
            swap(identity.data[i], identity.data[pivotRow]);
        }

        //check if the matrix is singular (no inverse exists)
        if (matrix.data[i][i] == 0.0)
        {
            throw runtime_error("Matrix is singular. Inverse does not exist.");
        }

        //scale the current row to make the pivot element equal to 1
        double scale = matrix.data[i][i];
        for (int j = 0; j < columns; j++)
        {
            matrix.data[i][j] /= scale;
            identity.data[i][j] /= scale;
        }

        //eliminate the elements below the pivot
        for (int j = i + 1; j < rows; j++)
        {
            double factor = matrix.data[j][i];
            for (int k = 0; k < columns; k++)
            {
                matrix.data[j][k] -= factor * matrix.data[i][k];
                identity.data[j][k] -= factor * identity.data[i][k];
            }
        }
    }

    //perform back substitution to obtain the inverse matrix
    for (int i = rows - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            double factor = matrix.data[j][i];
            for (int k = 0; k < columns; k++)
            {
                matrix.data[j][k] -= factor * matrix.data[i][k];
                identity.data[j][k] -= factor * identity.data[i][k];
            }
        }
    }

    return identity;
}