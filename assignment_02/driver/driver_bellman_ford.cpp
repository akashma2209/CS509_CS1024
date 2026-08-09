#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <climits>
#include "../src/Bellman_Ford.hpp"
#include "../../common/csr/src/CSR.hpp"
#include "../../common/csr/src/driver_csr.hpp"
using namespace std;

// Print Results on terminal and file
void printResult(ostream &out,int source,int vertex,int *dis,bool neg_cycle,double time)
{
    out << "Algorithm: Bellman-Ford" << "\n";
    out << "Source: " << source << "\n";
    if(neg_cycle) //checking that negitive-weighted cycle  was detected
    {
        out << "Negative cycle: true" << "\n";
    }
    else
    {
        out << "\n";
        out << "Vertex Distance" << "\n";
        for(int i = 0; i < vertex; i++)  //Printing shortest distance from source for every vertex
        {
            out << i << " ";
            if(dis[i] == INT_MAX) //Condition for not reachable vertex 
            {
                out << "INF";
            }
            else
            {
                out << dis[i];
            }
            out << "\n";
        }
        out << "Negative cycle: none" << "\n";
    }
    out << "Execution time: "<< time << " ms" << "\n";  //Printing exexution time for alogrithm
}

int main()
{
    string input ="assignment_02/tests/bellman_ford"; //input file
    string csr_out ="common/csr/outputs/graph";    //CSR generated file 
    string output ="assignment_02/outputs/bellman_ford"; //output file
    cout << "Generating CSR files..." << "\n";
    genCSR(input); // Generate CSR files from Bellman-Ford input
    cout << "CSR generation completed." << "\n";

    if(filesystem::exists(output)) //Remove old output file 
    {
        for(auto file : filesystem::directory_iterator(output))
        {
            if(file.path().extension() == ".txt")
            {
                filesystem::remove(file.path());
            }
        }
    }

    for(auto file : filesystem::directory_iterator(csr_out))
    {
        if(file.path().extension() != ".txt") //Reading all file with .txt  extension
        {
            continue;
        }
        cout << "\n";
        cout << "Running : "<< file.path().filename().string()<< "\n";

        ifstream fin(file.path());
        if(!fin)
        {
            cout << "Cannot open CSR file."<< "\n";
            continue;
        }

        int vertex;
        int edges;
        fin >> vertex >> edges; // Read number of vertices and edges
        // Create CSR arrays
        int *rowPtr =new int[vertex + 1];
        int *colIdx = new int[edges];
        int *values = new int[edges];

        for(int i = 0; i <= vertex; i++) // Read row pointer
        {
            fin >> rowPtr[i];
        }
        for(int i = 0; i < edges; i++)  // Read column index
        {
            fin >> colIdx[i];
        }        
        for(int i = 0; i < edges; i++) // Read edge weights
        {
            fin >> values[i];
        }
        int source;
        fin >> source; // Read source vertex
        fin.close();

        CSR graph; // Create CSR structure
        graph.vertices = vertex;
        graph.edges = edges;
        graph.row_ptr = rowPtr;
        graph.col_idx = colIdx;
        graph.values = values;
        int *dis =new int[vertex]; // distance array
        bool neg_cycle = false;  // tell negatve cycle was found or not

        auto start =chrono::high_resolution_clock::now(); // Start Bellman-Ford timing
        bellmanFord(graph, source, dis, neg_cycle);
        auto end = chrono::high_resolution_clock::now(); // Stop Bellman-Ford timing
        double time =chrono::duration<double, milli>(end - start ).count();
        
        string outputFile =output + "/" +file.path().filename().string(); // Create output file
        ofstream fout(outputFile);
        if(!fout)
        {
            cout << "Cannot create output file."<< "\n";
            continue;
        }
        printResult(cout, source, vertex, dis, neg_cycle, time ); // Print results on terminal
        printResult(fout, source, vertex, dis, neg_cycle, time);  // Print results on output file
    }
    return 0;
}
