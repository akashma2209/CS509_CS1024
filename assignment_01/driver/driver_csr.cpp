#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "../src/CSR_Graph.hpp"
using namespace std;
namespace fs = std::filesystem;

// Function to print CSR output on terminal and write it in output f
void printCSR(ostream &out, CSR graph)
{
    out << "Row_ptr: ";
    for(int i = 0; i <= graph.vertices; i++)
    {
        out << graph.row_ptr[i] << " ";
    }
    out << endl;

    out << "Col_idx: ";
    for(int i = 0; i < graph.edges; i++)
    {
        out << graph.col_idx[i] << " ";
    }
    out << endl;

    out << "Values: ";
    for(int i = 0; i < graph.edges; i++)
    {
        out << graph.values[i] << " ";
    }

    out << endl;
}

int main()
{
    int c=1;
    string input = "tests/csr_graph"; //Location of all test case file
    string output = "outputs/graph/csr"; //Location where output file of simple GEMM will be stored

    for (auto &file : fs::directory_iterator(input))
    {
        if (file.path().extension() != ".txt")
        {
            continue;
        }
        string outfile = output + "/output_" + to_string(c) + ".txt"; //Creating output file loctaion for CSR
        c++;
        cout << "\n Running : " ;
        
        ifstream fin(file.path());

        if(!fin)
        {
            cout << "Cannot open input file : "<< file.path()<< "\n";
            continue;
        }
        //Temprory array to run adjacency list
        int sr[10000]; //Source matrix
        int des[10000]; //Destination matrix
        int we[10000]; //Weight natrix

        int vertices, totalEdges;
        fin >> vertices >> totalEdges;

        int edges = 0;
        // Read adjacency list
        for(int i = 0; i < vertices; i++)
        {
            int u, degree;
            fin >> u >> degree;
            // Read all outgoing edges of vertex
            for(int j = 0; j < degree; j++)
            {
                fin >> des[edges] >> we[edges];

                sr[edges] = u;
                edges++;
            }
        }

        // Reading sr line
        string temp;
        int startVertex;
        fin >> temp >> startVertex;
        fin.close();

        // Runing CSR code code and recording time
        auto start = chrono::high_resolution_clock::now(); //Starting Timer
        CSR graph = convertToCSR(sr,des,we,edges,vertices);
        auto end = chrono::high_resolution_clock::now();//Stopping Timer
        double time = chrono::duration<double, milli>(end - start).count(); //Calculating time in millisecond
        

        // Printing Result on Terminal Output
        cout << "\nCSR Representation\n \n" ;
        printCSR(cout, graph);

        ofstream fout(outfile);
        if(!fout)
        {
            cout << "Cannot create output file.\n" ;
            continue;
        }
        fout << "Algorithm: CSR Graph \n\n";
        printCSR(fout, graph);

        fout  << "\nAlgorithm Execution Time : "<< time<< " ms \n";

        // Terminal output
        cout << "\nAlgorithm Execution Time : "<< time << " ms \n";
    }
            cout << "\nAll CSR tests completed." << endl;
            return 0;
}
