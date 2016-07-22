#include "RevisedSimplexMethod.h"
#include <MatrixAlgebra.h>
#include <MatrixViewer.h>
#include <algorithm>
#include <iostream>
#include <limits>
void RevisedSimplexMethod::initialisePhaseI(){
    phaseI=true;
    cSaved=c;
    delete c;
    c=new Matrix(m+n,1);
    for(int i=1;i<=n;i++){
        c->setElement(i,1,0);
    }
    for(int i=n+1;i<=m+n;i++){
        c->setElement(i,1,1);
    }
    //add artificial variables
    Matrix *identity=new Matrix(m,m);
    identity->eye();
    ASaved=A;
    A=o->appendEnd(A,identity);
    Binv=identity;//initialise Basic matrix inverse as the artificial variables
    for(int i=1;i<=n;i++){//store indices of nonbasics
        nonBasicVars->push_back(i);
    }
    for(int i=n+1;i<=m+n;i++){
       basicVars->push_back(i);
    }
    xB=b;
    N=ASaved;
}
void RevisedSimplexMethod::initialisePhaseII(){
    phaseI=false;
    delete c;
    c=cSaved;
}
void RevisedSimplexMethod::initialiseCB(){
    MatrixViewer *v=new MatrixViewer();
    vector<vector<double> >* cBasics=new vector<vector<double> >;
    vector<vector<double> >* cNonBasics=new vector<vector<double> >;
    vector<double> first;
    cBasics->push_back(first);
    cNonBasics->push_back(first);
    cout<<"c: "<<endl;
    v->printMatrix(c);
    for(vector<int>::iterator it=basicVars->begin();it!=basicVars->end();++it){
        //cout<<"getting cost of basic var: "<<*it<<endl;

        (*cBasics)[0].push_back(c->getElement(*it,1));
    }
    for(vector<int>::iterator it=nonBasicVars->begin();it!=nonBasicVars->end();++it){

        (*cNonBasics)[0].push_back(c->getElement(*it,1));
    }
    cout<<"cB"<<endl;
//    delete cB;
    cB=o->T(new Matrix(*cBasics));
//    delete cN;

    cN=o->T(new Matrix(*cNonBasics));


    v->printMatrix(cB);
    cout<<"cN"<<endl;
    v->printMatrix(cN);
    delete v;
}
bool RevisedSimplexMethod::sanityCheck(){
    if(c->getRowNum()!=n||c->getColNum()!=1||b->getRowNum()!=m||b->getColNum()!=1){problemStatus=-1;return false;}//infeasible.
    for(int i=0;i<m;i++){
        if(b->getElement(1,i)<0){problemStatus=-1;return false;}
    }
    return true;
}
int RevisedSimplexMethod::findEV(){//if -1 returned. Then problem is optimal
    MatrixViewer *v=new MatrixViewer();
    int EV=-1;
    //find pi
    cout<<"find pt"<<endl;
    Matrix *pi_T=o->matrixMultiplication(o->T(cB),Binv);
    cout<<"pi_T done"<<endl;
    v->printMatrix(pi_T);
    cout<<"multiple: "<<endl;
    v->printMatrix(o->matrixMultiplication(pi_T,N));
    v->printMatrix(cN);
    Matrix *rc=o->subtraction(cN,o->T(o->matrixMultiplication(pi_T,N)));
    cout<<"rc done"<<endl;
    v->printMatrix(rc);
    //We now have to find the most negative.
    double minimum=0;
    for(int i=1;i<=rc->getColNum();i++){//therecout<<"Entering Variable"<<EV<<endl; should be a single row as reduced cost
        if(rc->getElement(1,i)<minimum){
                minimum=rc->getElement(1,i);
                EV=i;
        }
    }
    s=EV;
    delete v;
    return EV;
}
int RevisedSimplexMethod::findLV(){
    int LV=-1;//default at -1 if non-found. (unbounded problem)
    if(s<=0){return LV;}//this means no entering variable was found. Program should never reach here.
    MatrixViewer *v=new MatrixViewer();
    Matrix *A_s=new Matrix(m,1);
    A_s->replaceCol(1,A->getCol(s));
    cout<<"A_s"<<endl;
    v->printMatrix(A_s);
    cout<<"Binv: "<<endl;
    v->printMatrix(Binv);
    B_as=o->matrixMultiplication(Binv,A_s);
    cout<<"B_as: "<<endl;
    v->printMatrix(B_as);
    if(phaseI==false){//we shall use the extended leaving variable criterion
        int counter=1;
        for(vector<int>::iterator it=basicVars->begin();it!=basicVars->end();it++){
            if(*it>n&&B_as->getElement(counter,1)>=0){
                return counter;//this becomes the leaving var
            }
            counter++;
        }
    }
    double minRatio=numeric_limits<double>::infinity();
    cout<<"xB: "<<endl;
    v->printMatrix(xB);
    for(int i=1;i<=m;i++){
        if(B_as->getElement(i,1)>0){//only positives
            double x_a_ratio=(xB->getElement(i,1))/(B_as->getElement(i,1));
            cout<<"x ratio: "<<x_a_ratio<<endl;
            if(x_a_ratio<minRatio){
                minRatio=x_a_ratio;
                LV=i;
            }
        }
    }
    r=LV;
    return LV;//note that the Leaving Var is the index relative to the basis matrix, not A.
}
void RevisedSimplexMethod::GaussJordanPivot(){
    MatrixViewer *v=new MatrixViewer();
    Matrix *pivotMatrix=o->appendEnd(xB,o->appendEnd(Binv,B_as));//Create Matrix[xB|B^-1|B^-1as], of size m*(m+2)
    pivotMatrix->multiplyRow(r,(1/B_as->getElement(r,1)));
    for(int i=1;i<=m;i++){
        if(i!=r){
            pivotMatrix->rowAddition(i,r,-(B_as->getElement(i,1)));
        }
    }
    vector<double> xBVector=pivotMatrix->getCol(1);
    xB->replaceCol(1,xBVector);
    v->printMatrix(xB);
    cout<<"pivot Matrix:" <<endl;
    v->printMatrix(pivotMatrix);
    for(vector<int>::iterator it=nonBasicVars->begin();it!=nonBasicVars->end();it++){
        if(*it==(*basicVars)[r-1]){*it=s;}
        continue;
    }
    cout<<"Test"<<endl;
    (*basicVars)[r-1]=s;//the entering var is now stored in the basicvar vector
    pivotMatrix->deleteCol(pivotMatrix->getColNum());//delete the last column
    pivotMatrix->deleteCol(1);
    Binv=pivotMatrix;
    v->printMatrix(Binv);
    //delete pivotMatrix;
    //build N matrix(There should be a more efficient way to do this...):
    //delete N;
    N=new Matrix(m,A->getColNum()-m);
    for(int i=0;i<nonBasicVars->size();i++){
        N->replaceCol(i+1,A->getCol((*nonBasicVars)[i]));
    }
    initialiseCB();
}
void RevisedSimplexMethod::RSM(){
    if(sanityCheck()==false){return;}
    initialisePhaseI();//phaseI
    initialiseCB();//initialise cost vector
    while(true){
        s=findEV();
        if(s==-1){//no leaving variable found
            if(phaseI==true){
                Matrix *objective=o->matrixMultiplication(cB,xB);
                double objectiveValue=objective->getElement(1,1);
                if(objectiveValue==0){//PhaseI at optimal
                    initialisePhaseII();
                }else{//infesible case
                    problemStatus=-1;
                    return;
                }
            }else{
                //in this case we have optimal.
                problemStatus=1;
                Matrix *objective=o->matrixMultiplication(cB,xB);
                ObjectiveVal=objective->getElement(1,1);
            }
        }
        r=findLV();
        if(r==-1){//unbounded case
            problemStatus=0;
            ObjectiveVal=0;
            return;
        }
    }
}
void RevisedSimplexMethod::setBinv(Matrix *Binv, Matrix *N, vector<int>* basicVars, vector<int>* nonBasicVars){
    this->Binv=Binv;
    this->basicVars=basicVars;
    this->nonBasicVars=nonBasicVars;
    this->N=N;
    xB=o->matrixMultiplication(Binv,b);
}
solution *RevisedSimplexMethod::getSolution(){
    solution *result=new solution;
    result->basicVars=this->basicVars;
    result->problemStatus=this->problemStatus;
    result->x=this->xB;
    result->objective=this->ObjectiveVal;
    return result;
}
RevisedSimplexMethod::RevisedSimplexMethod(Matrix *A,Matrix *c,Matrix* b)
{
    this->A=A;
    this->c=c;
    this->b=b;
    ObjectiveVal=0;
    problemStatus=-2;
    m=A->getRowNum();
    n=A->getColNum();
    basicVars=new vector<int>;
    nonBasicVars=new vector<int>;
    //both leaving and entering set to -1.
    r=-1;
    s=-1;
}
RevisedSimplexMethod::~RevisedSimplexMethod()
{
    delete A;
    delete ASaved;
    delete c;
    delete cSaved;
    delete b;
    delete N;
    delete Binv;
    delete cB;
    delete cN;
    delete basicVars;
    delete nonBasicVars;
    delete o;
    delete B_as;
}
