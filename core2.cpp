#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

static string syncFile = "sync.txt";
static string dataFile = "data.txt";
unsigned long long num = 1231231231231200000;

int main () {
    //sync with core1
    ofstream fout(syncFile);
    fout << "ready";
    fout.close();
    //calculate
    vector<unsigned long long> data;
    while (num%2==0) {
        num/=2;
        data.push_back(2);
    }

    unsigned long long sqrtNum = sqrt(num);
    for (unsigned long long i=3; i<sqrtNum; i+=2) {
        if (num%i==0) {
            num/=i;
            data.push_back(i);
        }
    }

    if (num>2) data.push_back(num);

    //upload results to csv1
    remove(dataFile.c_str());
    fout.open(dataFile);
    for (auto i : data) {
        fout << i << " ";
    }
    fout.close();

    //sync with core1
    fout.open(syncFile);
    fout << "ready";
    fout.close();
}