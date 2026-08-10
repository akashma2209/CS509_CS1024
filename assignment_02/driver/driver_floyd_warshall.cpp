#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include "../src/Floyd_Warshall.hpp"
using namespace std;

const int INF = 1000000000; 
// Printing distance matrix
void printMatrix(ostream &out, int **mat, int vertex)
{
    for(int i = 0; i < vertex; i++) //Row Transverse
    {
        for(int j = 0; j < vertex; j++) //Column Transverse
        {
            if(mat[i][j] == INF) //Checking for no path
            {
                out << "INF ";
            }
            else
            {
                out << mat[i][j] << " ";  //Printing Shortest distance
            }
        }
        out << "\n";
    }
}

int main()
{
    string input = "assignment_02/tests/floyd_warshall";  //Input file
    string output = "assignment_02/outputs/floyd_warshall";  //Output file

    if(filesystem::exists(output))  
    {
        for(auto file : filesystem::directory_iterator(output)) 
        {
            if(file.path().extension() == ".txt")
            {
                filesystem::remove(file.path());  //Remove old files
            }
        }
    }
    
    for(auto file : filesystem::directory_iterator(input))
    {
        if(file.path().extension() != ".txt")  //Reading all file with .txt  extension
        {
            continue;
        }
        cout << "\n";
        cout << "Running : " << file.path().filename().string() << "\n";

        ifstream fin(file.path());  //Open input file
        if(!fin)
        {
            cout << "Cannot open input file." << "\n";
            continue;
        }
        int vertex;
        fin >> vertex; //Read number of vertex
       
        int **dis = new int*[vertex];
        for(int i = 0; i < vertex; i++)  // Creating distance matrix
        {
            dis[i] = new int[vertex];
        }
        for(int i = 0; i < vertex; i++) // Read matrix
        {
            for(int j = 0; j < vertex; j++)
            {
                string value;
                fin >> value;
                if(value == "INF")
                {
                    dis[i][j] = INF; // Changing "INF" into the  INF value
                }
                else
                {
                    dis[i][j] = stoi(value); //Changing string value to integer
                }
            }
        }
        fin.close();
        bool neg_cycle = false;  //used tf negitive cycle
        
        auto start =chrono::high_resolution_clock::now(); // Start Floyd-Warshall timer
        floydWarshall(dis,vertex,neg_cycle); //Calling Floyd warshall Algo
        auto end =chrono::high_resolution_clock::now(); // Stop timer
        double time =chrono::duration<double, milli>(end-start).count();
 
        string out =output + "/" + file.path().filename().string(); //Output file
        ofstream fout(out);
        if(!fout)
        {
            cout << "Cannot create output file." << "\n";
            continue;
        }
        fout << "Algorithm: Floyd-Warshall" << "\n";
        if(neg_cycle == true)  //if negative cycle detected
        {
            cout << "Negative cycle: true" << "\n";
            fout << "Negative cycle: true" << "\n";
        }
        else    //if  negitive cycle is not detected
        {
            cout << "Distance matrix:" << "\n";
            fout << "Distance matrix:" << "\n";

            printMatrix(fout, dis, vertex);  //Storing in file
            printMatrix(cout, dis, vertex); //Printion on terminal

            cout << "Negative cycle: none" << "\n";
            fout << "Negative cycle: none" << "\n";
        }
        cout << "Execution time: " << time << " ms" << "\n";  
        fout << "Execution time: " << time << " ms" << "\n";
        fout.close();
        cout << "Output : " << out << "\n";
    }
    return 0;
}