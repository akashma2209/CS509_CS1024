#include "GEMM_Simple.hpp"
using namespace std;

void matrixMulti(int **A, int **B, int **C, int row_A, int col_A, int col_B)
{
    // Initializing output matrix C with 0
    for(int i = 0; i < row_A; i++)
    {
        for(int j = 0; j < col_B; j++)
        {
            C[i][j] = 0;
        }}

    // Doing Simple matrix multiplication
    for(int i = 0; i < row_A; i++)  
    {
        for(int j = 0; j < col_B; j++)
        {
            for(int k = 0; k < col_A; k++) //Helping in dot matrix multiplication
            {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]); //Storing multiplication as it position in result matrix C
            }
        }
    }
}