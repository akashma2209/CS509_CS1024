#include "GEMM_Blocking.hpp"

void block_Multi(int **A,int **B,int **C,int row_A,int col_A,int col_B)
{
    int blockSize = 64;  //Deciding the block sixe used for matrix multiplication
    // Initializing output matrix C with 0
    for(int i = 0; i < row_A; i++)
    {
        for(int j = 0; j < col_B; j++)
        {
            C[i][j] = 0;
        }
    }
    
    //Doing Blocking Matrix Multiplication
    for(int ii = 0; ii < row_A; ii += blockSize) //Manage row block of matrix
    {
        for(int kk = 0; kk < col_A; kk += blockSize) //Manage combine block of matrix
        {
            for(int jj = 0; jj < col_B; jj += blockSize) //Manage column block of matrix
            {
                for(int i = ii; i < ii + blockSize && i < row_A; i++)
                {
                    for(int k = kk; k < kk + blockSize && k < col_A; k++)
                    {
                        int temp = A[i][k];
                        for(int j = jj; j < jj + blockSize && j < col_B;j++)
                        {
                            C[i][j] = C[i][j] + (temp * B[k][j]);
                        }
                    }
                }
            }
        }
    }
}