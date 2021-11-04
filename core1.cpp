#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

static string syncFile = "sync.txt";

int main () {
    //sync with core 2
    ifstream fin;
    string sync;
    
    while (sync!="ready") {
        fin.open(syncFile);
        fin >> sync;
        fin.close();
    }

    cout << "FINISHED SYNCING\n";
    //calculate
    
    //fetch data from core 2

    //combined calculation

    //finish timer
}