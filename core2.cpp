#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

static string syncFile = "sync.txt";

int main () {
    //sync with core1
    ofstream fout(syncFile);
    fout << "ready";
    //calculate

    //upload results to csv1
}