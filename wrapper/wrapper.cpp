#include <iostream>
#include <cstdlib>
using namespace std;

void assignment1()
{
    char choice;
    cout << "\nAssignment 1\n-----------------\n";
    cout << "1. GEMM Matrix Multiplication\n";
    cout << "2. CSR Graph\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch(choice)
    {
        case '1':
            cout << "\nRunning GEMM...\n";
            system("cd assignment_01 && " "g++ -std=c++17 " "driver\\driver_matrix.cpp " "src\\GEMM_Simple.cpp " "src\\GEMM_Blocking.cpp " "-o executables\\matrix.exe" );
            system("cd assignment_01 && executables\\matrix.exe" );
            break;

        case '2':
            cout << "\nRunning CSR...\n";
            system("cd assignment_01 && " "g++ -std=c++17 " "driver\\driver_csr.cpp " "src\\CSR_Graph.cpp " "-o executables\\csr.exe" );
            system( "cd assignment_01 && executables\\csr.exe" );
            break;

        default:
            cout << "Invalid choice\n";
    }
}

void assignment2()
{
    cout << "\nAssignment 2 not added yet\n";
}

int main()
{
    char choice;

    while(true)
    {
        cout << "      Select your Assignment\n";
        cout << "============================\n";

        cout << "1. Assignment 1\n";
        cout << "2. Exit\n";

        cout << "Enter your selection: ";
        cin >> choice;

        switch(choice)
        {
            case '1':
                assignment1();
                break;

            case '2':
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}