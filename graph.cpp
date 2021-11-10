#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;

unsigned long long randomGen() {
    int numDigits=rand()%4+15;
    unsigned long long rt=0;
    for (int i=0; i<numDigits; ++i) {
        rt*=10;
        rt+=rand()%10;
    }
    return rt;
}

//going to run core1.cpp and core2.cpp in sequence on random inputs
//and graph data
int main () {
    srand(time(nullptr));
    string compile = "g++ core1.cpp -o core1.exe && g++ core2.cpp -o core2.exe";
    system(compile.c_str());

    string execute1 = "start core1.exe";
    string execute2 = "start core2.exe";
    for (int i=0; i<200; ++i) {
        string s1 = to_string(randomGen());
        // string s2 = to_string(randomGen());
        string n = to_string(i);
        string combined = execute1 + " " + s1 + " " + s1 + " " + n + " && " +
                          execute2 + " " + s1 + " " + n;
        system(combined.c_str());
        _sleep(10000);
    }
}