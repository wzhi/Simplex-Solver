/*Written by William Zhi
Matrix would have been better if [row][col] had been used.*/
#include "Matrix.h"
#include <iostream>

//getter number of rows and columns
int Matrix::getRowNum(){
    return row;
}
int Matrix::getColNum(){
    return col;
}
//get element
double Matrix::getElement(int row,int col){
    if(row>this->row||col>this->col||row<1||col<1){return 0;}
    return (*data)[col-1][row-1];
}
//getter data
vector<vector<double> > Matrix::getData(){
    return *data;
}
vector<double> Matrix::getRow(int row){
    vector<double> rowData;
    if(row>this->row||row<1){return rowData;}
    for(int i=0;i<col;i++){
        double element=(*data)[i][row-1];
        rowData.push_back(element);
    }
    return rowData;
}
vector<double> Matrix::getCol(int col){
    if(col>this->col||col<1){vector<double>* nullData=new vector<double>; return *nullData;}
    return (*data)[col-1];
}
//deletions
bool Matrix::deleteRow(int row){
    if(row>this->row||row<1){return false;}
    for(int i=0;i<col;i++){
        vector<double> colData=(*data)[i];
        colData.erase(colData.begin()+(row-1));
        (*data)[i]=colData;
    }
    this->row--;
    return true;
}
bool Matrix::deleteCol(int col){
    if(col>this->col||col<1){return false;}
    (*data).erase(data->begin()+(col-1));
    this->col--;
    return true;
}
//adding rows, columns
bool Matrix::addRow(int row, vector<double> rowData){
    if(row>this->row+1||row<1){return false;}
    for(int i=0;i<col;i++){
        (*data)[i].insert(((*data)[i]).begin()+(row-1),rowData[i]);
    }
    this->row++;
    return true;
}
bool Matrix::addCol(int col, vector<double> colData){
    if(col>this->col+1||col<1){return false;}
    data->insert(data->begin()+(col-1),colData);
    this->col++;
    return true;
}
//swap rows and columns
bool Matrix::swapRow(int rowA,int rowB){
    if(rowA>row||rowB>row||rowA<1||rowB<1){return false;}
    for(int i=0;i<col;i++){
        double temp=(*data)[i][rowA-1];;
        (*data)[i][rowA-1]=(*data)[i][rowB-1];
        (*data)[i][rowB-1]=temp;
    }
    return true;
}
bool Matrix::swapCol(int colA,int colB){
    if(colA>col||colB>col||colA<1||colB<1){return false;}
    vector<double> temp=(*data)[colA-1];
    (*data)[colA-1]=(*data)[colB-1];
    (*data)[colB-1]=temp;
    return true;
}
bool Matrix::replaceRow(int row, vector<double> rowData){
    if(row>this->row||row<1||rowData.size()!=this->col){return false;}//return false in case of wrong indexing, uncompatitble size
    deleteRow(row);
    addRow(row,rowData);
    return true;
}
bool Matrix::replaceCol(int col, vector<double> colData){
    if(col>this->col||col<1||colData.size()!=this->row){return false;}//wrong indexing or incompatitbility
    deleteCol(col);
    addCol(col,colData);
    return true;
}
//scalar multiply one row
bool Matrix::multiplyRow(int row, double scalar){
    if(row>this->row||row<1){return false;}
    for(int i=0;i<col;i++){
        (*data)[i][row-1]=((*data)[i][row-1])*scalar;
    }
    return true;
}
//this is used in row pivoting. The result: RowA=RowA+factor.*RowB
bool Matrix::rowAddition(int rowA,int rowB,double factor){
    cout<<"rowA: "<<rowA<<"rowB: "<<rowB<<"row: "<<row<<endl;
    if(rowA>row||rowA<1||rowB>row||rowB<1){cout<<"return false"<<endl; return false;}
    for(int i=0;i<col;i++){
        (*data)[i][rowA-1]=(*data)[i][rowA-1]+factor*((*data)[i][rowB-1]);
    }
    return true;
}
//change element
bool Matrix::setElement(int row,int col,double element){
    if(row>this->row||row<1||col>this->col||col<1){return false;}
    (*data)[col-1][row-1]=element;
    return true;
}
//transpose
void Matrix::transpose(){
    vector<vector<double> > *resultant=new vector<vector<double> >;
    for(int i=0;i<row;i++){
            vector<double>* col_T=new vector<double>;
            for(int j=0;j<col;j++){
                col_T->push_back((*data)[j][i]);
            }
            resultant->push_back(*col_T);
    }
    delete data;
    data=resultant;//reassign
    int temp=col;
    col=row;
    row=temp;
}
//creates zero matrix
void Matrix::zeroMatrix(){
    data=new vector<vector<double> >;
    for(int i=0;i<col;i++){
        vector<double> colData;
        for(int j=0;j<row;j++){
            colData.push_back(0);
        }
        data->push_back(colData);
    }
}
//Creates Identity Matrix
bool Matrix::eye(){
    if(col!=row){return false;}//we cannot have an identity with different # rows and columns
    for(int i=0;i<row;i++){
        (*data)[i][i]=1;
    }
    return true;
}
Matrix::Matrix(int row, int col)
{
    this->row=row;
    this->col=col;
    zeroMatrix();

}
Matrix::Matrix(vector<vector<double> > data){
    row=data.size();
    col=data[0].size();
    this->data=new vector<vector<double> >;
    for(int i=0;i<col;i++){
        vector<double> colData;
        for(int j=0;j<row;j++){
            colData.push_back(data[j][i]);
        }
        this->data->push_back(colData);
    }
}
Matrix::~Matrix()
{
    delete data;
}
