#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
using namespace std;
class Matrix
{
    public:
        Matrix(int row, int col);
        Matrix(vector<vector<double> > data);
        int getRowNum();
        int getColNum();
        double getElement(int row, int col);
        vector<vector<double> > getData();
        vector<double> getRow(int row);
        vector<double> getCol(int col);
        bool deleteRow(int row);
        bool deleteCol(int col);
        bool addRow(int row, vector<double> rowData);
        bool addCol(int col, vector<double> colData);
        bool swapRow(int rowA,int rowB);
        bool swapCol(int colA,int colB);
        bool setElement(int row,int col, double element);
        bool replaceRow(int row, vector<double> rowData);
        bool replaceCol(int col, vector<double> colData);
        bool multiplyRow(int row, double scalar);
        bool rowAddition(int rowA,int rowB, double factor);
        void transpose();
        void zeroMatrix();
        bool eye();
        virtual ~Matrix();
    protected:
    private:
        int row;
        int col;
        vector<vector<double> >* data;
};

#endif // MATRIX_H
