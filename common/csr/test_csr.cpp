#include <iostream>
#include "src/driver_csr.hpp"
using namespace std;

int main()
{
    string input = "common/csr/tests/graph"; //Loction of file where I need to take input
    genCSR(input);   //Calling CSR to conversion
    cout << "\nCSR Test Completed\n";
    return 0;
}