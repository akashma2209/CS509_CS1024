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
    char choice;
    cout << "\nAssignment 1\n-----------------\n";
    cout << "1. Bellman Ford\n";
    cout << "2. Floyd Warshall\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch(choice)
    {
        case '1':
            cout << "\nRunning Bellman Ford...\n";
            system("g++ -std=c++17 assignment_02\\driver\\driver_bellman_ford.cpp assignment_02\\src\\Bellman_Ford.cpp common\\csr\\src\\CSR.cpp common\\csr\\src\\driver_csr.cpp -o assignment_02\\executables\\bellman_ford.exe");

            system(".\\assignment_02\\executables\\bellman_ford.exe");

            break;

        case '2':
            cout << "\nRunning Floyd Warshall...\n";
            
            system("g++ -std=c++17 assignment_02\\driver\\driver_floyd_warshall.cpp assignment_02\\src\\Floyd_Warshall.cpp common\\csr\\src\\CSR.cpp common\\csr\\src\\driver_csr.cpp -o assignment_02\\executables\\floyd_warshall.exe");

            system(".\\assignment_02\\executables\\floyd_warshall.exe");
            break;

        default:
            cout << "Invalid choice\n";
    }
}

int main()
{
    char choice;

    while(true)
    {
        cout << "      Select your Assignment\n";
        cout << "============================\n";

        cout << "Press 1. Assignment 1\n";
        cout << "Press 2. Assignment 2\n";
        cout << "Press 3. For Testing CSR\n";
        cout << "Press 4. Exit\n";

        cout << "Enter your selection: ";
        cin >> choice;

        switch(choice)
        {
            
            case '1':
                assignment1();
                break;
            
            case '2':
                assignment2();
                break;

            case '4':
                cout << "Exiting...\n";
                return 0;
            
            case '3':
                cout << "\nTesting Common CSR...\n";

                system("g++ -std=c++17 common\\csr\\test_csr.cpp common\\csr\\src\\CSR.cpp common\\csr\\src\\driver_csr.cpp -o common\\csr\\executables\\csr_test.exe");

                system(".\\common\\csr\\executables\\csr_test.exe");

            break;
            

            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}