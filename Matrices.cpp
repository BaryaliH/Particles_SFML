#include "Matrices.h"

using namespace Matrices;

// ===============================
// Matrix Constructor
// ===============================
Matrix::Matrix(int _rows, int _cols)
{
    rows = _rows;
    cols = _cols;

    a.resize(rows);

    for (int i = 0; i < rows; i++)
    {
        a[i].resize(cols, 0.0);
    }
}

// ===============================
// Operator +
// ===============================
Matrix Matrices::operator+(const Matrix& a, const Matrix& b)
{
    Matrix result(a.getRows(), a.getCols());

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            result(i, j) = a(i, j) + b(i, j);
        }
    }

    return result;
}

// ===============================
// Operator *
// ===============================
Matrix Matrices::operator*(const Matrix& a, const Matrix& b)
{
    Matrix result(a.getRows(), b.getCols());

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < b.getCols(); j++)
        {
            result(i, j) = 0;

            for (int k = 0; k < a.getCols(); k++)
            {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }

    return result;
}

// ===============================
// Operator ==
// ===============================
bool Matrices::operator==(const Matrix& a, const Matrix& b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        return false;
    }

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a(i, j) != b(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

// ===============================
// Operator !=
// ===============================
bool Matrices::operator!=(const Matrix& a, const Matrix& b)
{
    return !(a == b);
}

// ===============================
// Operator <<
// ===============================
ostream& Matrices::operator<<(ostream& os, const Matrix& a)
{
    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            os << a(i, j) << " ";
        }
        os << endl;
    }

    return os;
}

// ===============================
// RotationMatrix
// ===============================
RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
{
    (*this)(0, 0) = cos(theta);
    (*this)(0, 1) = -sin(theta);
    (*this)(1, 0) = sin(theta);
    (*this)(1, 1) = cos(theta);
}

// ===============================
// ScalingMatrix
// ===============================
ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
{
    (*this)(0, 0) = scale;
    (*this)(0, 1) = 0;
    (*this)(1, 0) = 0;
    (*this)(1, 1) = scale;
}

// ===============================
// TranslationMatrix
// ===============================
TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
{
    for (int j = 0; j < nCols; j++)
    {
        (*this)(0, j) = xShift;
        (*this)(1, j) = yShift;
    }
}