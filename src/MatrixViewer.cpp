#include "MatrixViewer.h"
#include <iostream>
#include <Matrix.h>
#include <vector>

using namespace std;
void MatrixViewer::printMatrix(Matrix *input){
    int row=input->getRowNum();
    int col=input->getColNum();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<(input->getElement(i+1,j+1))<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
MatrixViewer::MatrixViewer()
{
    //ctor
}

MatrixViewer::~MatrixViewer()
{
    //dtor
}
