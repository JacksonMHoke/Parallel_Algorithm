#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <time.h>
#include <math.h>

using namespace std;

static string syncFile = "sync.txt";
static string dataFile = "data.txt";
unsigned long long num = 12312123421342521200;


// unsigned long long sumPermutations (vector<int>& digits, int currSum, int prevSum, int index) {

// }

int main () {
    //sync with core 2
    clock_t timer = clock();
    ifstream fin;
    string sync;
    
    while (sync!="ready") {
        fin.open(syncFile);
        fin >> sync;
        fin.close();
    }
    timer = clock() - timer;
    cout << "FINISHED SYNCING IN " << (float)timer/CLOCKS_PER_SEC << " SECONDS\n";
    remove(syncFile.c_str());

    //calculate all factors
    timer = clock();

    unordered_map<int, int> factors;
    while (num%2==0) {
        cout << 2 << " ";
        num/=2;
        factors[2]++;
    }

    int sqrtNum = sqrt(num);
    for (int i=3; i<sqrtNum; i+=2) {
        if (num%i==0) {
            cout << i << " ";
            num/=i;
            factors[i]++;
        }
    }

    if (num>2) {
        factors[num]++;
        cout << num << " ";
    }
    cout << "\n";

    //wait for data from core 2
    sync="";
    while (sync!="ready") {
        fin.open(syncFile);
        fin >> sync;
        fin.close();
    }

    //fetch data from core 2/combined calculation
    fin.open(dataFile);
    int num;
    string s;
    while (fin >> num) {
        cout << num << " ";
        if (factors.find(num)!=factors.end() && factors[num]>0) {
            s+=to_string(num)+" ";
            factors[num]--;
        }
    }
    cout << "\n" << s;

    cout << "\nFINISHED COMBINED CALCULATION IN " << (float)(clock()-timer)/CLOCKS_PER_SEC << " SECONDS\n";
    remove(syncFile.c_str());
}