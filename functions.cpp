#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "functions.h"
using namespace std;

/*****FUNCTIONS******/


// Generate all rolls of 4 dice and compute sum matrix
int generateSumMatrix(int sides, vector<int>& sumCounts, vector<vector<int>>& sumMatrix) {
    int count = 0;
    for(int d1=1; d1<=sides; ++d1)
        for(int d2=1; d2<=sides; ++d2)
            for(int d3=1; d3<=sides; ++d3)
                for(int d4=1; d4<=sides; ++d4){
                    for(int m=2; m<=2*sides; ++m){
                        if(d1+d2==m || d1+d3==m || d1+d4==m || d2+d3==m || d2+d4==m || d3+d4==m){
                            ++sumCounts[m];
                            ++sumMatrix[count][m];
                        }
                    }
                    ++count;
                }
    return count;
}

// Function to compute probabilities for pairs of sums
vector<vector<int>> ProbPairs(int sides, const vector<vector<int>>& sumMatrix) {

    double totalRolls = pow(sides, 4); // total number of rolls
    int MS = 2 * sides + 1;        // max sum index

    // Initialize the pair matrix
    vector<vector<int>> pairMatrix(MS, vector<int>(MS, 0));

    // Compute counts for each pair of sums
    for (int S1 = 2; S1 < MS; ++S1) {
        for (int S2 = S1 + 1; S2 < MS; ++S2) {
            for (int i = 0; i < totalRolls; ++i) {
                if (sumMatrix[i][S1] == 1 || sumMatrix[i][S2] == 1) {
                    ++pairMatrix[S1][S2];
                }
            }
        }
    }

    return pairMatrix;
}

// Builds a list of all unordered sum pairs (S1, S2) with S1 < S2 for a dice of given sides.
vector<pair<double, string>> buildPairList(const vector<vector<int>>& pairMatrix) {
    vector<pair<double, string>> pairList;
    int MS = pairMatrix.size();

    for (int i = 2; i < MS; ++i) {
        for (int j = i + 1; j < MS; ++j) {
            if (pairMatrix[i][j] != 0) {
                ostringstream oss;
                oss << "(" << i << "," << j << ")";
                string label = oss.str();

                pairList.push_back(make_pair(
                    static_cast<double>(pairMatrix[i][j]),
                    label
                ));
            }
        }
    }

    return pairList;
}

// Builds a list of triples in the format: (count, "(S1,S2,S3)")
vector<pair<double, string>> buildTrioList(const vector<vector<vector<int>>>& trioMatrix) {
    vector<pair<double, string>> trioList;
    int MS = trioMatrix.size();

    for (int i = 2; i < MS; ++i) {
        for (int j = i + 1; j < MS; ++j) {
            for (int k = j + 1; k < MS; ++k) {
                if (trioMatrix[i][j][k] != 0) {
                    ostringstream oss;
                    oss << "(" << i << "," << j << "," << k << ")";
                    string label = oss.str();

                    trioList.push_back(make_pair(
                        static_cast<double>(trioMatrix[i][j][k]),
                        label
                    ));
                }
            }
        }
    }

    return trioList;
}


// Function to compute probabilities for triples of sums
vector<vector<vector<int>>> ProbTrios(int sides, const vector<vector<int>>& sumMatrix) {

    double totalRolls = pow(sides, 4);  // total number of rolls
    int MS = 2 * sides + 1;         // max sum index

    // Initialize the 3D trio matrix
    vector<vector<vector<int>>> trioMatrix(MS, vector<vector<int>>(MS, vector<int>(MS, 0)));

    // Compute counts for each triple of sums
    for (int S1 = 2; S1 < MS; ++S1) {
        for (int S2 = S1 + 1; S2 < MS; ++S2) {
            for (int S3 = S2 + 1; S3 < MS; ++S3) {
                for (int i = 0; i < totalRolls; ++i) {
                    if (sumMatrix[i][S1] == 1 || sumMatrix[i][S2] == 1 || sumMatrix[i][S3] == 1) {
                        ++trioMatrix[S1][S2][S3];
                    }
                }
            }
        }
    }

    return trioMatrix;
}

// Print frequencies and probabilities
void printFrequencies(const vector<int>& sumCounts, int totalRolls){
    for(int i=2;i<sumCounts.size();++i) { 
        cout << "Sum " << i << ": freq = " << sumCounts[i] 
             << ", P = " << sumCounts[i]/static_cast<double>(totalRolls) << endl;
    }
    cout << endl;
}

// Prints all pairs sorted from most frequent to least frequent
void printPairList(const vector<pair<double, string>>& pairList, int totalRolls) {
    cout << "Pairs sorted by frequency (highest first):" << endl;

    for (int i = pairList.size() - 1; i >= 0; --i) {
        double freq = pairList[i].first;
        const string& label = pairList[i].second;

        cout << "Freq " << label 
             << " = " << freq
             << ", P = " << freq / totalRolls
             << endl;
    }
}


// Prints all triples sorted from most frequent to least frequent
void printTrioList(const vector<pair<double, string>>& trioList, int totalRolls) {
    cout << "Triples sorted by frequency (highest first):" << endl;

    for (int i = trioList.size() - 1; i >= 0; --i) {
        double freq = trioList[i].first;
        const string& label = trioList[i].second;

        cout << "Freq " << label
             << " = " << freq
             << ", P = " << freq / totalRolls
             << endl;
    }
    cout << endl;
}



// Compute how many times each sum appears in any trio of the 4 dice
vector<int> computeTrioAppearances(int sides) {
    vector<int> trioAppear(2 * sides + 1, 0);

    for (int d1 = 1; d1 <= sides; ++d1)
        for (int d2 = 1; d2 <= sides; ++d2)
            for (int d3 = 1; d3 <= sides; ++d3)
                for (int d4 = 1; d4 <= sides; ++d4) {

                    vector<int> sums = {
                        d1 + d2, d1 + d3, d1 + d4,
                        d2 + d3, d2 + d4, d3 + d4
                    };

                    // Count all 20 trios generated from 6 sums
                    for (int i = 0; i < 6; ++i)
                        for (int j = i + 1; j < 6; ++j)
                            for (int k = j + 1; k < 6; ++k) {
                                trioAppear[sums[i]]++;
                                trioAppear[sums[j]]++;
                                trioAppear[sums[k]]++;
                            }
                }

    return trioAppear;
}

// Compute probability of each sum appearing in a trio
vector<double> computeTrioProbabilities(int sides, const vector<int>& trioAppear) {
    int totalRolls = pow(sides, 4);
    vector<double> prob(2 * sides + 1, 0.0);

    for (int s = 2; s <= 2 * sides; ++s)
        prob[s] = double(trioAppear[s]) / (totalRolls * 20.0);

    return prob;
}

// Compute ideal path lengths scaled from a reference sum
vector<double> computeIdealPaths(const vector<double>& prob, int refSum, double refLength, int sides) {
    vector<double> ideal(2 * sides + 1, 0.0);
    double refProb = prob[refSum];

    for (int s = 2; s <= 2 * sides; ++s)
        ideal[s] = refLength * (prob[s] / refProb);

    return ideal;
}

// Print ideal path values
void printIdealPaths(const vector<double>& ideal, int sides) {
    cout << "\nIdeal path lengths per sum (4 dice, trios, Can't Stop):\n";
    for (int s = 2; s <= 2 * sides; ++s)
        cout << "Sum " << s << ": ideal path length = " << ideal[s] << endl;
}
