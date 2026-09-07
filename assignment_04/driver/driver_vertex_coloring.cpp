#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <string>
#include "../src/Vertex_Coloring.hpp"
#include "../../common/csr/src/CSR.hpp"
#include "../../common/csr/src/driver_csr.hpp"
using namespace std;
namespace fs = filesystem;

// Print Vertex Coloring result
void printColoring( ostream &out, int color[], int vertices, int colorsUsed, double total_time)
{
    out << "Algorithm: Greedy Vertex Coloring\n";
    out << "Vertex colors:\n";
    for(int i = 0; i < vertices; i++)
    {
        out << i << " " << color[i] << "\n";
    }
    out << "Colors used: " << colorsUsed << "\n";
    out << "Execution time: " << total_time << " ms\n";
}

int main()
{
    string input = "assignment_04/tests/vertex_coloring";
    string csr_out = "common/csr/outputs/graph";
    string output = "assignment_04/outputs/vertex_coloring";

    genCSR(input); // Generate CSR
    if(!fs::exists(output)) // Create output folder
    {
        fs::create_directories(output);
    }

    for(auto file : fs::directory_iterator(output)) // Remove old Vertex
    {
        if(file.path().extension() == ".txt")
        {
            fs::remove(file.path());
        }
    }

    for(auto file : fs::directory_iterator(csr_out)) // Read generated CSR files
    {
        if(file.path().extension() != ".txt")
        {
            continue;
        }
        cout << "\n";
        cout << "Running : " << file.path().filename().string() << "\n";

        ifstream fin(file.path()); // Open CSR file directly
        if(!fin)
        {
            cout << "Cannot open CSR file." << "\n";
            continue;
        }
        int vertices;
        int edges;

        fin >> vertices >> edges; // Read number of vertices and edges

        // Allocate CSR arrays
        int *rowPtr = new int[vertices + 1];
        int *colIdx =new int[edges];
        int *values = nullptr;

        for(int i = 0; i <= vertices; i++) // Read row pointer
        {
            fin >> rowPtr[i];
        }
        for(int i = 0; i < edges; i++) // Read column indices
        {
            fin >> colIdx[i];
        }
        fin.close();

        // Create CSR object
        CSR graph;
        graph.vertices = vertices;
        graph.edges = edges;
        graph.row_ptr = rowPtr;
        graph.col_idx = colIdx;
        graph.values = values;

        int *color = new int[vertices];    // Allocate color array
        int colorsUsed = 0;
        bool valid = false;

        auto start = chrono::high_resolution_clock::now(); // Start timing
        vertexColoring(graph,color,colorsUsed,valid);
        auto end = chrono::high_resolution_clock::now(); // Stop timing
        double total_time =chrono::duration<double, milli>( end - start).count();

        string outputFile = output + "/" + file.path().filename().string(); // Create output file
        ofstream fout(outputFile);

        if(!fout)
        {
            cout << "Cannot create output file." << "\n";
        }
        else
        {
            printColoring(cout,color,vertices,colorsUsed,total_time); // Print result to terminal
            printColoring(fout,color,vertices,colorsUsed,total_time); // Print result to output file
            fout.close();
            cout << "Vertex Coloring Output : " << outputFile << "\n";
        }

        // Free memory
        delete[] color;
        delete[] graph.row_ptr;
        delete[] graph.col_idx;
    }
    cout << "\n";
    cout << "All Vertex Coloring tests completed." << "\n";
    return 0;
}

