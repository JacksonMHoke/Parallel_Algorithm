#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

static string syncFile = "sync.txt";
static string dataFile = "data.txt";
unsigned long long num = 123121234200000;

/*
    Desc: Returns a vector of all prime factors of n

    Parameters:
        n: Number to be factored

    Return value: vector of all prime values of n in order to least to greatest
*/
vector<unsigned long long> findFactorsVec(unsigned long long n) {
    vector<unsigned long long> rt;
    while (n%2==0) {
        n/=2;
        rt.push_back(2);
    }

    int sqrtNum = sqrt(n);
    for (unsigned long long i=3; i<sqrtNum; i+=2) {
        if (n%i==0) {
            n/=i;
            rt.push_back(i);
        }
    }

    if (n>2) {
        rt.push_back(n);
    }
    return rt;
}

int main (int argc, char* argv[]) {
    cout << "Core2 ran\n";
    string pc;
    //if there was a command line input, set num to that input
    if (argc==3) {
        num=stoull(argv[1]);
        pc = argv[2];
    }

    //sync with core1
    ofstream fout(pc+syncFile);
    fout << "ready";
    fout.close();
    //calculate
    vector<unsigned long long> data = findFactorsVec(num);

    //upload results to csv1
    fout.open(pc+dataFile);
    for (unsigned long long i : data) {
        fout << i << " ";
    }
    fout << endl;
    fout.close();

    //sync with core1
    fout.open(pc+syncFile);
    fout << "ready";
    fout.close();
}