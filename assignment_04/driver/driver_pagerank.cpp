#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <string>
#include <iomanip>
#include "../src/PageRank.hpp"
#include "../../common/csr/src/CSR.hpp"
#include "../../common/csr/src/driver_csr.hpp"
using namespace std;
namespace fs = filesystem;

int main()
{
    string input = "assignment_04/tests/pagerank";
    string csr_out = "common/csr/outputs/graph";
    string pagerank_out = "assignment_04/outputs/pagerank";

    genCSR(input); // Generate CSR
    if(!fs::exists(pagerank_out)) // Create output folder if it does not exist
    {
        fs::create_directories(pagerank_out);
    }

    for(auto file : fs::directory_iterator(pagerank_out)) // Remove old PageRank output files
    {
        if(file.path().extension() == ".txt")
        {
            fs::remove(file.path());
        }
    }
    
    for(auto file : fs::directory_iterator(csr_out)) // Read all generated CSR files
    {
        if(file.path().extension() != ".txt")
        {
            continue;
        }

        string fileName = file.path().filename().string();
        string originalInput = input + "/" + fileName;
        ifstream parameterFile(originalInput);

        if(!parameterFile)
        {
            cout << "Cannot open PageRank input file." << "\n";
            continue;
        }
        int inputVertices;
        int inputEdges;

        parameterFile >> inputVertices >> inputEdges;

        string line;
        getline(parameterFile, line);
        for(int i = 0; i < inputVertices; i++)
        {
            getline(parameterFile, line);
        }

        // Read PageRank parameters
        string word;
        double damping;
        double tolerance;
        int maxIterations;
        parameterFile >> word >> damping;
        parameterFile >> word >> tolerance;
        parameterFile >> word >> maxIterations;
        parameterFile.close();

        // Read CSR file directly
        string csrFile = csr_out + "/" + fileName;
        ifstream fin(csrFile);
        if(!fin)
        {
            cout << "Cannot open CSR output file." << "\n";
            continue;
        }

        int vertices;
        int edges;
        fin >> vertices >> edges;

        // Allocate CSR arrays
        int *rowPtr = new int[vertices + 1];
        int *colIdx =  new int[edges];
        int *values = nullptr;

        
        for(int i = 0; i <= vertices; i++) // Read row pointer
        {
            fin >> rowPtr[i];
        }
        for(int i = 0; i < edges; i++)
        {
            fin >> colIdx[i]; // Read column indices
        }
        fin.close();

        // Create CSR object
        CSR graph;
        graph.vertices = vertices;
        graph.edges = edges;
        graph.row_ptr = rowPtr;
        graph.col_idx = colIdx;
        graph.values = values;

        // Allocate PageRank array
        double *rank = new double[vertices];
        int iterations = 0;
        bool converged = false;
        
        // Start timing
        auto start =chrono::high_resolution_clock::now();
        pageRank( graph, damping, tolerance, maxIterations, rank, iterations, converged);
        auto end =chrono::high_resolution_clock::now();
        chrono::duration<double, milli> executionTime = end - start;

        // Calculate sum of ranks
        double rankSum = 0.0;
        for(int i = 0; i < vertices; i++)
        {
            rankSum += rank[i];
        }

        // Print result to terminal
        cout << fixed << setprecision(6);
        cout << "Algorithm: PageRank" << "\n";
        cout << "Damping: " << damping << "\n";
        cout << "Vertex ranks:" << "\n";
        for(int i = 0; i < vertices; i++)
        {
            cout << i << " " << rank[i] << "\n";
        }

        cout << "Sum of ranks: " << rankSum << "\n";
        cout << "Iterations: " << iterations << "\n";
        cout << "Converged: ";

        if(converged)
        {
            cout << "true" << "\n";
        }
        else
        {
            cout << "false" << "\n";
        }
        cout << "Execution time: " << executionTime.count() << " ms" << "\n";

        // Write result to output file
        string outputFile = pagerank_out + "/" + fileName;
        ofstream fout(outputFile);
        if(!fout)
        {
            cout << "Cannot create PageRank output file." << "\n";
        }
        else
        {
            fout << fixed << setprecision(6);
            fout << "Algorithm: PageRank" << "\n";
            fout << "Damping: " << damping << "\n";
            fout << "Vertex ranks:" << "\n";

            for(int i = 0;  i < vertices; i++)
            {
                fout << i << " "  << rank[i] << "\n";
            }

            fout << "Sum of ranks: " << rankSum << "\n";
            fout << "Iterations: " << iterations << "\n";
            fout << "Converged: ";
            if(converged)
            {
                fout << "true" << "\n";
            }
            else
            {
                fout << "false" << "\n";
            }

            fout << "Execution time: " << executionTime.count() << " ms" << "\n";
            fout.close();
            cout << "PageRank Output : " << outputFile << "\n";
        }

        // Free memory directly
        delete[] rank;
        delete[] graph.row_ptr;
        delete[] graph.col_idx;
    }

    cout << "\n========================================\n";
    cout << "All PageRank tests completed." << "\n";
    cout << "========================================\n";
    return 0;
}
