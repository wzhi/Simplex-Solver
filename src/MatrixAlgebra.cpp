#include "MatrixAlgebra.h"
#include <matrix.h>
MatrixAlgebra::MatrixAlgebra()
{
    //ctor
}
Matrix *MatrixAlgebra::T(Matrix *input){
    Matrix *Transpose=input;
    Transpose->transpose();
    return Transpose;
}
Matrix *MatrixAlgebra::extractRow(Matrix *input, vector<int>* index){
    Matrix *output=new Matrix(index->size(),input->getColNum());//to make sure the indices are sane
    int counter=1;//start from one, as this is the index+1th extracted
    for(vector<int>::iterator it=index->begin();it!=index->end();it++){
        if(*it<1||*it>input->getRowNum()){throw;}
        output->replaceRow(counter,input->getRow(*it));
        counter++;
    }
    return output;
}
Matrix *MatrixAlgebra::extractCol(Matrix *input, vector<int>* index){
    Matrix *output=new Matrix(input->getColNum(),index->size());
    int counter=1;//start from one, as this is the index+1th extracted
    for(vector<int>::iterator it=index->begin();it!=index->end();it++){
        if(*it<1||*it>input->getColNum()){throw;}//to make sure the indices are sane
        output->replaceCol(counter,input->getCol(*it));
        counter++;
    }
    return output;
}
Matrix *MatrixAlgebra::scalarMultiplication(Matrix *input, double factor){
    Matrix *output=new Matrix(input->getRowNum(),input->getColNum());
    for(int i=1;i<=input->getRowNum();i++){
        for(int j=1;j<=input->getColNum();j++){
            output->setElement(i+1,j+1,factor*input->getElement(i,j));
        }
    }
    return output;
}
Matrix *MatrixAlgebra::addition(Matrix *A, Matrix *B){
    Matrix *resultant=new Matrix(A->getRowNum(),A->getColNum());
    if(A->getRowNum()!=B->getRowNum()||A->getColNum()!=B->getColNum()){return resultant;}
    for(int i=1;i<=A->getRowNum();i++){
        for(int j=1;j<=B->getColNum();j++){
            resultant->setElement(i,j,A->getElement(i,j)+B->getElement(i,j));
        }
    }
    return resultant;
}
Matrix *MatrixAlgebra::subtraction(Matrix *A, Matrix *B){
    Matrix *resultant=new Matrix(A->getRowNum(),A->getColNum());
    if(A->getRowNum()!=B->getRowNum()||A->getColNum()!=B->getColNum()){return resultant;}
    for(int i=1;i<=A->getRowNum();i++){
        for(int j=1;j<=B->getColNum();j++){
            resultant->setElement(i,j,A->getElement(i,j)-B->getElement(i,j));
        }
    }
    return resultant;
}

Matrix* MatrixAlgebra::matrixMultiplication(Matrix *A,Matrix *B){ //throw error in case of size errors
    //lets store the dimensions of the matrices for simplicity's sake
    int colA=A->getColNum();
    int colB=B->getColNum();
    int rowA=A->getRowNum();
    int rowB=B->getRowNum();
    if(colA!=rowB){//if dimensions don't match
        throw;//throw error in case of size errors
    }
    Matrix *resultant=new Matrix(rowA,colB);
    for(int i=0;i<rowA;i++){
        for(int j=0;j<colB;j++){
            double sum=0;
            for(int k=0;k<colA;k++){
                sum+=(A->getElement(i+1,k+1)*B->getElement(k+1,j+1));
            }
            resultant->setElement(i+1,j+1,sum);
        }
    }
    return resultant;
}
Matrix *MatrixAlgebra::appendEnd(Matrix *A,Matrix *B){
    Matrix *resultant=new Matrix(A->getRowNum(),(A->getColNum()+B->getColNum()));
    if(A->getRowNum()!=B->getRowNum()){return resultant;}
    for(int i=1;i<=A->getColNum();i++){
        resultant->replaceCol(i,A->getCol(i));
    }
    for(int i=1;i<=B->getColNum();i++){
        resultant->replaceCol(i+A->getColNum(),B->getCol(i));
    }
    return resultant;
}
MatrixAlgebra::~MatrixAlgebra()
{
    //dtor
}
