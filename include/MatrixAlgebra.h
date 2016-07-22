#ifndef MATRIXALGEBRA_H
#define MATRIXALGEBRA_H
#include <matrix.h>

class MatrixAlgebra
{
    public:
        MatrixAlgebra();
        virtual ~MatrixAlgebra();
        Matrix *T(Matrix *input);//returns the tranpose
        Matrix *extractRow(Matrix *input, vector<int>* index);
        Matrix *extractCol(Matrix *input, vector<int>* index);
        Matrix *scalarMultiplication(Matrix *input, double factor);
        Matrix *addition(Matrix *A, Matrix *B);
        Matrix *subtraction(Matrix *A, Matrix *B);
        Matrix *matrixMultiplication(Matrix* A, Matrix* B);//AB
        Matrix *appendEnd(Matrix *A, Matrix *B);
    protected:
    private:
};

#endif // MATRIXALGEBRA_H
