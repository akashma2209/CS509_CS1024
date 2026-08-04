#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <string>
#include "../src/GEMM_Simple.hpp"
#include "../src/GEMM_Blocking.hpp"
using namespace std;
namespace fs = std::filesystem;

// Printing output matrix on terminal 
void printMatrix(int **out, int r, int c)
{
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cout << out[i][j] << " ";
        }
        cout << "\n";
    }
}

// Writing output result and total exexution time for each fine in output file
void write_out(string algo, string file_name, int **out, int r, int c, double time)
{
    ofstream file(file_name);
    file << "Algorithm: " << algo << "\n\n"; //Writing algorithm name in file
    //Writing  output matrix in output file
    file << "Result Matrix:\n";
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            file << out[i][j] << " ";
        }
        file << "\n";
    }
    file << "\nTime taken to run the code: " << time << " ms\n"; //Writing Execution time in file
    file.close();
}
//As array size is not fix for each code so here we are dynamically allocating the size or rows and column of matrix
int** createMat(int r, int c)
{
    int **mat = new int*[r];
    for(int i = 0; i < r; i++)
    {
        mat[i] = new int[c];
    }
    return mat;
}

int main()
{
    string input = "tests/matrix"; //Location of all test case file
    string simple_output= "outputs/matrix/simple"; //Location where output file of simple GEMM will be stored
    string blocking_output = "outputs/matrix/blocking"; //Location where output file of Blocking GEMM will be stored
    
    int count = 1;
    // Loop to read all test file inside the tests folder
    for(const auto &file : fs::directory_iterator(input))
    {
        if(file.path().extension() != ".txt")
        {
            continue;
        }

        string simple_file =simple_output +"/simple_" + to_string(count)+".txt"; //Creating output file loctaion for simple GEMM
        string blocking_file =blocking_output +"/blocking_" +to_string(count) +".txt"; //Creating output file loctaion for blocking GEMM
        count++;
        int row_A;
        int col_A;
        int row_B;
        int col_B;

        ifstream fin(file.path());

        if(!fin)
        {
            cout << "Cannot open input file : "<< file.path()<< "\n";
            continue;
        }

        // Input Format  row_A col_A col_B Matrix A, Matrix B 
        fin >> row_A >> col_A >> col_B;
        row_B = col_A;

        int **A = createMat(row_A, col_A);

        int **B = createMat(row_B, col_B);

        int **C_simple = createMat(row_A, col_B);

        int **C_blocking = createMat(row_A, col_B);

        // Reading Matrix A form input file 
        for(int i = 0; i < row_A; i++)
        {
            for(int j = 0; j < col_A; j++)
            {
                fin >> A[i][j];
            }
        }

        // Reading Matrix B form input file
        for(int i = 0; i < row_B; i++)
        {
            for(int j = 0; j < col_B; j++)
            {
                fin >> B[i][j];
            }
        }
        fin.close();

        // Runing Simple GEMM code and recording time
        auto start =chrono::high_resolution_clock::now(); //Starting Timer
        matrixMulti(A,B,C_simple,row_A,col_A,col_B);
        auto end =chrono::high_resolution_clock::now(); //Stopping Timer
        double simpleTime =chrono::duration<double,milli>(end-start).count(); //Calculating time in millisecond

        // Runing Blocking GEMM code and recording time
        auto start1 =chrono::high_resolution_clock::now(); //Starting Timer
        block_Multi(A, B, C_blocking, row_A, col_A, col_B);
        auto end1 =chrono::high_resolution_clock::now(); //Stopping Timer
        double blockingTime =chrono::duration<double,milli>(end1-start1).count();  //Calculating time in millisecond

        
        // Printing Result on Terminal Output
        cout << "Test File : "<< file.path().filename().string()<< "\n";
    
        cout << "\nAlgorithm: GEMM Simple\n\n";
        cout << "Result Matrix:\n";

        printMatrix(C_simple,row_A,col_B);

        cout << "\nExecution Time: "<< simpleTime<< " ms\n";
        

        cout << "\n\n\nAlgorithm: GEMM Blocking\n\n";
        cout << "Result Matrix:\n";
        printMatrix(C_blocking,row_A,col_B);

        cout << "\nExecution Time: "<< blockingTime<< " ms\n\n\n";

        // Write output files
        write_out("GEMM Simple",simple_file,C_simple,row_A,col_B,simpleTime);
        
        write_out("GEMM Blocking",blocking_file,C_blocking,row_A,col_B,blockingTime);
    }

    return 0;
}

//g++ -std=c++17 driver\driver_matrix.cpp src\GEMM_Simple.cpp src\GEMM_Blocking.cpp -o executables\gemm_compare.exe
//executables\gemm_compare.exe