#ifndef REVISEDSIMPLEXMETHOD_H
#define REVISEDSIMPLEXMETHOD_H
#include <MatrixAlgebra.h>
/*Solver assumes that the problem is a minimisation problem in standard computational form
    A - mxn Constraint matrix
    c - nx1 Cost vector
    b - mx1 Positive RHS vector*/
struct solution{
    int problemStatus;
    Matrix *x;
    vector<int> *basicVars;
    double objective;
};
class RevisedSimplexMethod
{
    public:
        RevisedSimplexMethod(Matrix *A,Matrix *c,Matrix* b);
        bool sanityCheck();//We can detect for problems that are not in the right form
        void initialisePhaseI();
        void initialisePhaseII();
        void initialiseCB();
        void RSM();
        int findLV();
        int findEV();
        void setBinv(Matrix *Binv, Matrix *N, vector<int>* basicVars, vector<int>* nonBasicVars);//used for testing
        void GaussJordanPivot();
        virtual ~RevisedSimplexMethod();
        solution *getSolution();
    protected:
    private:

        int m,n;//these are the row/column # of the constraint matrix
        Matrix *A;
        Matrix *ASaved;
        Matrix *c;
        Matrix *cSaved;//this is used in row pivoting. The result: RowA=RowA+factor*RowB
        Matrix *b;
        Matrix *Binv;
        Matrix *N;
        int r;//Leaving variable
        int s;//Entering variable
        Matrix* cB;
        Matrix* cN;
        Matrix* xB;//basic variables
        Matrix* B_as;
        bool phaseI;
        vector<int>* basicVars;
        vector<int>* nonBasicVars;
        MatrixAlgebra* o;//used for matrix operations
        int problemStatus;//-2, not yet solved; -1, infeasible; 0, unbounded; 1, solved
        solution *result;
        double ObjectiveVal;
};

#endif // REVISEDSIMPLEXMETHOD_H
