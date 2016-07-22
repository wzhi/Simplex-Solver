#ifndef MATRIXVIEWER_H
#define MATRIXVIEWER_H
#include <Matrix.h>

class MatrixViewer
{
    public:
        MatrixViewer();
        virtual ~MatrixViewer();
        void printMatrix(Matrix* input);
    protected:
    private:
};

#endif // MATRIXVIEWER_H
