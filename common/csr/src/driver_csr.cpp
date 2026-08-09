#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "CSR.hpp"
#include "driver_csr.hpp"
using namespace std;

const int MAX_EDGES = 1000000;
// Array used to store details of graph
int scr[MAX_EDGES];
int des[MAX_EDGES];
int weight[MAX_EDGES];
bool w_Graph = false; //Variable to check wheather graph is weighted or not

void printCSR(ostream &out, CSR graph) //Function to write CSR in file and print output in terminal
{
    int vertex = graph.vertices;
    int edges = graph.edges;
    
    out << vertex << " " << edges << "\n"; // Printing vertices and edges    
    for(int i = 0; i <= vertex; i++) // Printing row pointer
    {
        out << graph.row_ptr[i] << " ";
    }
    out << "\n";
    for(int i = 0; i < edges; i++) // Printing column index
    {
        out << graph.col_idx[i] << " ";
    }
    out << "\n";
    if(w_Graph == true) // Printing weight only for weighted graph
    {
        for(int i = 0; i < edges; i++)
        {
            out << graph.values[i] << " ";
        }
        out << "\n";
    }
}

void genCSR(const string &input)
{
    string output = "common/csr/outputs/graph";
    if(filesystem::exists(output))  // Removing existing output file and add new one
    {
        for(auto file : filesystem::directory_iterator(output))
        {
            if(file.path().extension() == ".txt")
            {
                filesystem::remove(file.path());
            }
        }
    }
  
    int c = 1;
    for(auto file : filesystem::directory_iterator(input)) //Calling all file present in test folder with .txt extension
    {
        if(file.path().extension() != ".txt")
        {
            continue;
        }
        ifstream fin(file.path());
        if(!fin)
        {
            cout << "Cannot open input file." << "\n";
            continue;
        }
        int vertexs;
        int t_edges;
        fin >> vertexs >> t_edges;
        string line;
        getline(fin,line);     // Remove empty line
        int edges = 0;
        w_Graph = false; //Resing grpah before every ew file is being read
        for(int i = 0; i < vertexs; i++)
        {
            getline(fin,line);
            if(line == "")  // Skipping empty line 
            {
                i--;
                continue;
            }
            stringstream ss(line);
            int u;
            int degree;
            ss >> u >> degree;  ///Reading vertex and its number of neighbour
            int values[10000];
            int count = 0;
            while(ss >> values[count])
            {
                count++;
            }
            // Weightless graph
            if(count == degree)
            {
                for(int j = 0; j < degree; j++)
                {
                    scr[edges] = u;
                    des[edges] = values[j];
                    // default weight
                    weight[edges] = 1;
                    edges++;
                }
            }
            // Weighted graph
            else if(count == degree * 2)
            {
                w_Graph = true;
                int index = 0;
                for(int j = 0; j < degree; j++)
                {
                    scr[edges] = u;
                    des[edges] = values[index];
                    weight[edges] = values[index + 1];
                    index = index + 2;
                    edges++;
                }
            }
        }
        // Read the source vertex if it is present in the graph input file.
        string word;
        int startVertex;
        fin >> word >> startVertex;
        fin.close();
        CSR graph = convertToCSR(scr, des, weight, edges, vertexs ); //Convertig to CSR
        string out = output + "/output_" + to_string(c) + ".txt";
        c++;

        ofstream fout(out);
        if(!fout)
        {
            cout << "Cannot create output file." << "\n";
            continue;
        }
        printCSR(fout,graph);
        fout << startVertex << "\n";
        fout.close();
    }
}