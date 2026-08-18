#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <string>
#include "../src/MST.hpp"
#include "../../common/csr/src/CSR.hpp"
#include "../../common/csr/src/driver_csr.hpp"
using namespace std;namespace fs = filesystem;

// Print result to terminal or file
void printMST(ostream &out, const string &algorithm, MSTEdge edges[], int edgeCount, int totalWeight, double executionTime)
{
    out << "Algorithm: " << algorithm << "\n";
    out << "\nMST edges:\n";
    for(int i = 0; i < edgeCount; i++)
    {
        out << edges[i].u << " "<< edges[i].v << " "<< edges[i].weight << "\n";
    }
    out << "\nTotal MST weight: " << totalWeight << "\n";
    out << "\nExecution time: " << executionTime << " ms\n";
}

int main()
{
    string input = "assignment_03/tests/mst"; // input file
    string csr_out = "common/csr/outputs/graph"; //CSR generated file 
    string kru_out = "assignment_03/outputs/kruskal"; // Kruskal output file
    string prim_out = "assignment_03/outputs/prim"; // Prim output file

    genCSR(input); // Generate CSR

    if(fs::exists(kru_out))//Remove old Kruskal output file 
    {
        for(auto file : fs::directory_iterator(kru_out))
        {
            if(file.path().extension() == ".txt")
            {
                fs::remove(file.path());
            }
        }
    }

    if(fs::exists(prim_out)) //Remove old Prim output file
    {
        for(auto file : fs::directory_iterator(prim_out))
        {
            if(file.path().extension() == ".txt")
            {
                fs::remove(file.path());
            }
        }
    }

    for(auto file : fs::directory_iterator(csr_out)) //Reading all file with .txt  extension
    {
        if(file.path().extension() != ".txt")
        {
            continue;
        }
        cout << "\n";
        cout << "Running : "<< file.path().filename().string()<< "\n";

        ifstream fin(file.path()); // Open CSR file
        if(!fin)
        {
            cout << "Cannot open CSR file."<< "\n";
            continue;
        }

        int vertices;
        int edges;
        fin >> vertices >> edges; // Read number of vertices and edges
        // Create CSR arrays
        int *rowPtr = new int[vertices + 1];
        int *colIdx = new int[edges];
        int *values = new int[edges];

        for(int i = 0; i <= vertices; i++) // Read row pointer
        {
            fin >> rowPtr[i];
        }
        for(int i = 0; i < edges; i++) // Read column indices
        {
            fin >> colIdx[i];
        }
        for(int i = 0; i < edges; i++) // Read weights
        {
            fin >> values[i];
        }
        fin.close();

        CSR graph; // Create CSR object
        graph.vertices = vertices;
        graph.edges = edges;
        graph.row_ptr = rowPtr;
        graph.col_idx = colIdx;
        graph.values = values;
        // Allocate MST edge arrays
        MSTEdge *kr_Edges = new MSTEdge[vertices - 1];
        MSTEdge *pr_Edges = new MSTEdge[vertices - 1];

        // KRUSKAL
        int kr_edge = 0;
        int kr_weight = 0;
        auto k_start =chrono::high_resolution_clock::now(); // Start Kruskal timing
        kruskalMST( graph, kr_Edges, kr_edge, kr_weight);
        auto k_stop =chrono::high_resolution_clock::now(); // Stop Kruskal timing
        double k_time =chrono::duration<double, milli>(k_stop - k_start).count();
        string k_out = kru_out + "/" + file.path().filename().string();
        ofstream kfout(k_out);

        if(!kfout)
        {
            cout << "Cannot create Kruskal output file."<< "\n";
        }
        else
        {  
            printMST(cout,"Kruskal's MST",kr_Edges,kr_edge,kr_weight,k_time); // Print to terminal
            printMST(kfout,"Kruskal's MST",kr_Edges,kr_edge,kr_weight,k_time); // Print to file
            kfout.close();
            cout << "Kruskal Output : " << k_out << "\n";
        }

        // PRIM
        int pr_edget = 0;
        int pr_weight = 0;
        auto p_start =chrono::high_resolution_clock::now();
        primMST( graph, pr_Edges, pr_edget, pr_weight);
        auto p_stop = chrono::high_resolution_clock::now();
        double p_time = chrono::duration<double, milli>(p_stop - p_start).count();
        string p_out = prim_out + "/" + file.path().filename().string();
        ofstream pfout(p_out);
        if(!pfout)
        {
            cout << "Cannot create Prim output file."<< "\n";
        }
        else
        {
            printMST( cout, "Prim's MST", pr_Edges, pr_edget, pr_weight, p_time); // Print to terminal
            printMST( pfout, "Prim's MST", pr_Edges, pr_edget, pr_weight, p_time); // Print to file
            pfout.close();
            cout << "Prim Output : " << p_out << "\n";
        }
    }
    return 0;
}