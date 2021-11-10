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
unsigned long long num1 = 123121234200000;
unsigned long long num2 = 123121234200000;

/*
    Desc: Outputs an unordered_map<unsigned long long, int> of all the frequencies of prime factors in n. Ex: 49 will have
    map[7]=2

    Paramaters:
        n: Number to find prime factors of

    Return value: Unordered_map of frequencies of prime factors of n
*/
unordered_map<unsigned long long, int> findFactorsMap (unsigned long long n) {
    unordered_map<unsigned long long, int> mp;
    while (n%2==0) {
        cout << 2 << " ";
        n/=2;
        mp[2]++;
    }

    unsigned long long sqrtNum = sqrt(n);
    for (unsigned long long i=3; i<sqrtNum; i+=2) {
        if (n%i==0) {
            cout << i << " ";
            n/=i;
            mp[i]++;
        }
    }

    if (n>2) {
        mp[n]++;
        cout << n << " ";
    }
    cout << "\n";
    return mp;
}

/*
    Desc: Returns a vector of all prime factors of n

    Parameters:
        n: Number to be factored

    Return value: vector of all prime values of n in order to least to greatest
*/
vector<unsigned long long> findFactorsVec(unsigned long long n) {
    vector<unsigned long long> rt;
    while (n%2==0) {
        cout << 2 << " ";
        n/=2;
        rt.push_back(2);
    }

    unsigned long long sqrtNum = sqrt(n);
    for (unsigned long long i=3; i<sqrtNum; i+=2) {
        if (n%i==0) {
            cout << i << " ";
            n/=i;
            rt.push_back(i);
        }
    }

    if (n>2) {
        rt.push_back(n);
        cout << n << " ";
    }
    cout << "\n";
    return rt;
}


/*
    Desc: Syncs up Core1.cpp with Core2.cpp(Core1.cpp cannot continue until Core2.cpp outputs ready to sync.txt)

    Parameters:
        None

    Return value: void
*/
void sync (string pc) {
    ifstream fin;
    string sync;
    while (sync!="ready") {
        fin.open(pc+syncFile);
        fin >> sync;
        fin.close();
    }
    remove((pc+syncFile).c_str());
}

int main (int argc, char* argv[]) {
    string pc;
    //check if arguments are passed in
    if (argc == 4) {
        num1=stoull(argv[1]);
        num2=stoull(argv[2]);
        pc = argv[3];
    }

    //sync with core 2
    clock_t timer = clock();
    sync(pc);
    timer = clock() - timer;
    cout << "FINISHED SYNCING IN " << (float)timer/CLOCKS_PER_SEC << " SECONDS\n";

    //calculate all factors
    timer = clock(); //start timer for calculating combined calculation
    unordered_map<unsigned long long, int> factors = findFactorsMap(num1);

    //wait for data from core 2
    sync(pc);

    //fetch data from core 2/combined calculation
    ifstream fin;
    fin.open(pc+dataFile);

    unsigned long long temp;
    string s;
    while (fin >> temp) {
        cout << temp << " ";
        if (factors.find(temp)!=factors.end() && factors[temp]>0) {
            s+=to_string(temp)+" ";
            factors[temp]--;
        }
    }
    cout << "\n" << s;
    fin.close();

    float timeParallel = (float)(clock()-timer)/CLOCKS_PER_SEC;
    cout << "\nFINISHED COMBINED CALCULATION IN " << timeParallel << " SECONDS\n";
    remove((pc+dataFile).c_str());


    //series, running calculations one afer another instead of in parallel, compare times
    //calculating for num1
    timer = clock(); //timer for series calculation

    clock_t timerNum1 = clock();
    unordered_map<unsigned long long, int> factors2 = findFactorsMap(num1);
    float timeNum1=float(clock()-timerNum1)/CLOCKS_PER_SEC;

    //calculating for num 2
    clock_t timerNum2 = clock();
    vector<unsigned long long> num2Factors = findFactorsVec(num2);
    float timeNum2=float(clock()-timerNum2)/CLOCKS_PER_SEC;

    //combined calculation
    for (auto i : num2Factors) {
        if (factors2[i]>0) {
            factors2[i]--;
            cout << i << " ";
        }
    }
    cout << "\n";

    //outputs times for both parallel and series and compares them
    float timeSeries = (float)(clock() - timer)/CLOCKS_PER_SEC;
    cout << "TIME IN PARALLEL: " << timeParallel << "\nTIME IN SERIES: " << timeSeries << "\nTIME DIFFERENCE(series-parallel): " << timeSeries-timeParallel << endl;
    cout << "PERCENT SPEED DIFFERENCE ((SERIES-PARALLEL)/PARALLEL): " << 100*(timeSeries-timeParallel)/timeParallel << "%\n";

    //outputs time to calculate in parallel, in series, and both numbers separately
    ofstream fout("time.csv", ios_base::app);
    //parallel time, series time, num1 time, num2 time
    fout << timeParallel << "," << timeSeries << "," << timeNum1 << "," << timeNum2 << "\n";
    fout.close();
}