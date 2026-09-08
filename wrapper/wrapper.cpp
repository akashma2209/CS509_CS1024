#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// Build and Run Function
// Works on Windows, Linux and Ubuntu/WSL

void buildAndRun(const string& sourceFiles, const string& executablePath)
{
    string executable;
    string runCommand;

#ifdef _WIN32

    // Windows

    // Windows executable extension
    executable = executablePath + ".exe";
    // Convert / to \ for Windows
    string windowsExecutable = executable;

    for(char& ch : windowsExecutable)
    {
        if(ch == '/')
        {
            ch = '\\';
        }
    }
    runCommand = windowsExecutable;

#else
  
    // Linux / Ubuntu / WSL
    // Linux does not use .exe
    executable = executablePath;
    // Linux requires ./ to run a program
    runCommand = "./" + executable;

#endif

    // Compile
    string compileCommand = "g++ -std=c++17 " + sourceFiles + " -o " + executable;
    cout << "\nCompiling...\n";
    int result = system(compileCommand.c_str());
    if(result != 0)
    {
        cout << "\nCompilation failed.\n";
        return;
    }

    cout << "Compilation successful.\n";

    // Run
    cout << "Running program...\n\n";
    result = system(runCommand.c_str());
    if(result != 0)
    {
        cout << "\nProgram exited with an error.\n";
    }
}

// Assignment 1
void assignment1()
{
    char choice;
    cout << "\nAssignment 1\n";
    cout << "-----------------\n";
    cout << "1. GEMM Matrix Multiplication\n";
    cout << "2. CSR Graph\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch(choice)
    {
        case '1':
        {
            cout << "\nRunning GEMM...\n";
            buildAndRun("assignment_01/driver/driver_matrix.cpp " "assignment_01/src/GEMM_Simple.cpp " "assignment_01/src/GEMM_Blocking.cpp", "assignment_01/executables/matrix");
            break;
        }

        case '2':
        {
            cout << "\nRunning CSR...\n";
            buildAndRun( "assignment_01/driver/driver_csr.cpp " "assignment_01/src/CSR_Graph.cpp", "assignment_01/executables/csr");
            break;
        }

        default:
            cout << "Invalid choice\n";
    }
}



// Assignment 2


void assignment2()
{
    char choice;
    cout << "\nAssignment 2\n";
    cout << "-----------------\n";
    cout << "1. Bellman Ford\n";
    cout << "2. Floyd Warshall\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch(choice)
    {
        case '1':
        {
            cout << "\nRunning Bellman Ford...\n";
            buildAndRun( "assignment_02/driver/driver_bellman_ford.cpp " "assignment_02/src/Bellman_Ford.cpp " "common/csr/src/CSR.cpp " "common/csr/src/driver_csr.cpp", "assignment_02/executables/bellman_ford");
            break;
        }

        case '2':
        {
            cout << "\nRunning Floyd Warshall...\n";
            buildAndRun( "assignment_02/driver/driver_floyd_warshall.cpp " "assignment_02/src/Floyd_Warshall.cpp " "common/csr/src/CSR.cpp " "common/csr/src/driver_csr.cpp", "assignment_02/executables/floyd_warshall");
            break;
        }

        default:
            cout << "Invalid choice\n";
    }
}


// Assignment 3


void assignment3()
{
    char choice;

    cout << "\nAssignment 3\n";
    cout << "-----------------\n";
    cout << "1. MST - Kruskal and Prim\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch(choice)
    {
        case '1':
        {
            cout << "\nRunning MST...\n";

            buildAndRun(
                "assignment_03/driver/driver_mst.cpp "
                "assignment_03/src/MST.cpp "
                "common/csr/src/CSR.cpp "
                "common/csr/src/driver_csr.cpp",
                "assignment_03/executables/mst"
            );

            break;
        }


        default:
            cout << "Invalid choice\n";
    }
}

// Assignment 4
void assignment4()
{
    char choice;

    cout << "\nAssignment 4\n";
    cout << "-----------------\n";
    cout << "1. Greedy Vertex Coloring\n";
    cout << "2. PageRank\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch(choice)
    {
        case '1':
        {
            cout << "\nRunning Greedy Vertex Coloring...\n";
            buildAndRun( "assignment_04/driver/driver_vertex_coloring.cpp " "assignment_04/src/Vertex_Coloring.cpp " "common/csr/src/CSR.cpp " "common/csr/src/driver_csr.cpp", "assignment_04/executables/vertex_coloring");
            break;
        }

        case '2':
        {
            cout << "\nRunning PageRank...\n";
            buildAndRun( "assignment_04/driver/driver_pagerank.cpp " "assignment_04/src/PageRank.cpp " "common/csr/src/CSR.cpp " "common/csr/src/driver_csr.cpp", "assignment_04/executables/pagerank");
            break;
        }

        default:
            cout << "Invalid choice\n";
    }
}

// Main
int main()
{
    char choice;
    while(true)
    {
        cout << "\n";
        cout << "      Select your Assignment\n";
        cout << "============================\n";

        cout << "Press 1. Assignment 1\n";
        cout << "Press 2. Assignment 2\n";
        cout << "Press 3. Assignment 3\n";
        cout << "Press 4. Assignment 4\n";
        cout << "Press 5. For Testing CSR\n";
        cout << "Press 6. Exit\n";

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

            case '3':
                assignment3();
                break;

            case '4':
                assignment4();
                break;

            case '5':
            {
                cout << "\nTesting Common CSR...\n";

                buildAndRun( "common/csr/test_csr.cpp " "common/csr/src/CSR.cpp " "common/csr/src/driver_csr.cpp", "common/csr/executables/csr_test");
                break;
            }

            case '6':
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}