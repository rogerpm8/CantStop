#include<iostream>
#include <fstream>
#include <cmath>
#include <vector> 
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>   
#include "functions.h"
using namespace std;


/*************************************Main**************************************/

int main(){

    int sides;
    cout << "Enter number of sides on the dice: ";
    cin >> sides;
    cout << endl;

    int totalRolls = pow(sides,4);
    vector<int> sumCounts(2*sides+1,0);
    vector<vector<int>> sumMatrix(totalRolls, vector<int>(2*sides+1,0));

    int count = generateSumMatrix(sides, sumCounts, sumMatrix);

    cout << "Total rolls = " << totalRolls << endl << endl;

    cout << "Relative frequencies and probabilities of each sum:" << endl;
    printFrequencies(sumCounts, totalRolls);



/********************* Output for sum pairs *****************************/

    vector<vector<int>> pairMatrix = ProbPairs(sides, sumMatrix);

    cout << "Probabilities for pairs of sums:" << endl;

    vector<pair<double, string>> pairList = buildPairList(pairMatrix);

    sort(pairList.begin(), pairList.end());

    printPairList(pairList, totalRolls);



/************************ Output for sum triples ***************************/

    vector<vector<vector<int>>> trioMatrix = ProbTrios(sides, sumMatrix);

    cout << endl << "Probabilities for triples of sums:" << endl;

    vector<pair<double, string>> trioList = buildTrioList(trioMatrix);

    sort(trioList.begin(), trioList.end());

    printTrioList(trioList, totalRolls);



/********************* Ideal Paths (4 dice, trios, Cant Stop) **********/

    char computePathsChar;
    cout << "Compute ideal paths? (y/n): ";
    cin >> computePathsChar;
    bool computePaths = (computePathsChar == 'y' || computePathsChar == 'Y');

    if (computePaths) {
        cout << "\nCalculating ideal paths (4 dice, trios, Can't Stop)...\n";

        double refLength;
        int refSum = 2;

        cout << "Enter reference path length for sum " << refSum << ": ";
        cin >> refLength;
        cout << endl;

        // Count trio appearances
        vector<int> trioAppear = computeTrioAppearances(sides);

        // Compute probabilities
        vector<double> probSum = computeTrioProbabilities(sides, trioAppear);

        // Compute ideal paths
        vector<double> idealPath = computeIdealPaths(probSum, refSum, refLength, sides);

        // Output
        printIdealPaths(idealPath, sides);
    }

    return 0;
}
