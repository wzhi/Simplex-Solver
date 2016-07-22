/*Made by William Zhi, for fun*/
#include <iostream>
#include <MatrixAlgebra.h>
#include <MatrixViewer.h>
#include <RevisedSimplexMethod.h>
using namespace std;
void MatrixTest();
void MatrixAlgebraTest();
void SolverTest();
int main()
{
    //MatrixTest();
    //MatrixAlgebraTest();
    SolverTest();
    return 0;
}
/*solver testing*/
//turns 2d array to 2d vector suitable for Matrix creation
//vector<vector<double> > arrayvectoriser(double **a,int rows,int cols){
//    vector<vector<double> > returnvec;
//    for(int i=0;i<cols;i++){
//        vector<double> colData;
//        for(int j=0;j<rows;j++){
//            colData.push_back(a[j][i]);
//        }
//        returnvec.push_back(colData);
//    }
//    return returnvec;
//}
void SolverTest(){
    vector<vector<double> > a_ar{
        {1,-1,1,1,0,0},
        {1,1,0,0,-1,0},
        {0,0,1,0,0,1}
        };
    vector<vector<double> > n_ar{
        {1,1,0},
        {1,0,-1},
        {0,0,0}
    };
    vector<vector<double> > c_ar{
        {1},{2},{3},{0},{0},{0}
        };
    vector<vector<double> > b_ar{
        {4},{0},{6}
    };
    vector<vector<double> > Binv_ar{
        {0,1,0},
        {1,1,0},
        {-1,-1,1}
    };
    vector<int> basicVars{2,3,6};
    vector<int> nonBasicVars{1,4,5};
    MatrixAlgebra *o=new MatrixAlgebra();//we'll have to transpose all our matrices. Due to formatting
    MatrixViewer *v=new MatrixViewer();
    cout<<"transpose test"<<endl;
    Matrix *A=new Matrix(a_ar);
    Matrix *b=new Matrix(b_ar);
    Matrix *c=new Matrix(c_ar);
    Matrix *Binv=new Matrix(Binv_ar);
    Matrix *N=new Matrix(n_ar);
    v->printMatrix(c);
    cout<<"transpose test end"<<endl;
    cout<<"A dimensions: "<<A->getRowNum()<<A->getColNum()<<endl;
    v->printMatrix(A);
    RevisedSimplexMethod *R=new RevisedSimplexMethod(A,c,b);
    /*
    R->setBinv(Binv,N,&basicVars,&nonBasicVars);
    R->initialiseCB();
    cout<<"initialising cB complete"<<endl;
    int EV=R->findEV();
    cout<<"Entering Variable"<<EV<<endl;
    int LV=R->findLV();
    cout<<"leaving Variable"<<LV<<endl;
    R->GaussJordanPivot();*/
    R->RSM();
    solution *result=R->getSolution();
    cout<<"status: "<<result->problemStatus<<"objective: "<<result->objective<<endl;

}


/*Tests for our code*/
void MatrixTest(){//sanity check on our matrix class
    Matrix *test_matrix=new Matrix(5,5);
    MatrixViewer *test_viewer=new MatrixViewer();
    test_viewer->printMatrix(test_matrix);
    cout<<"test eye"<<endl;
    test_matrix->eye();
    test_viewer->printMatrix(test_matrix);
    cout<<"test setelement"<<endl;
    test_matrix->setElement(2,3,9);
    test_viewer->printMatrix(test_matrix);
    cout<<"test transpose"<<endl;
    test_matrix->transpose();
    test_viewer->printMatrix(test_matrix);
    cout<<"test swap row"<<endl;
    test_matrix->swapRow(1,5);
    test_viewer->printMatrix(test_matrix);
    cout<<"test swap col"<<endl;
    test_matrix->swapCol(1,5);
    test_viewer->printMatrix(test_matrix);
    cout<<"test delete row"<<endl;
    test_matrix->deleteRow(3);
    test_viewer->printMatrix(test_matrix);
    cout<<"test delete col"<<endl;
    test_matrix->deleteCol(3);
    test_viewer->printMatrix(test_matrix);
    /*Good coding practice*/
    delete test_matrix;
    delete test_viewer;
}
void MatrixAlgebraTest(){//Matrix algebra test
    Matrix *test_matrixA=new Matrix(1,3);
    Matrix *test_matrixB=new Matrix(3,3);
    MatrixViewer *test_viewer=new MatrixViewer();
    MatrixAlgebra *test_algebra=new MatrixAlgebra();
    test_matrixA->setElement(1,2,3);
    test_matrixB->eye();
    test_matrixB->setElement(2,1,6);
    Matrix *result=test_algebra->T(test_algebra->matrixMultiplication(test_matrixA,test_matrixB));
    test_viewer->printMatrix(result);
    /*Good coding practice*/
    delete test_matrixA;
    delete test_matrixB;
    delete test_algebra;
    delete test_viewer;
}
