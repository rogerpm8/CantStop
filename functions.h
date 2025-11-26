#ifndef CANTSTOP_FUNCTIONS_H
#define CANTSTOP_FUNCTIONS_H

#include <vector>
#include <string>
#include <utility>
using namespace std;

// Generate all rolls of 4 dice and compute sum matrix
int generateSumMatrix(int sides, vector<int>& sumCounts, vector<vector<int>>& sumMatrix);

// Compute probabilities for pairs of sums
vector<vector<int>> ProbPairs(int sides, const vector<vector<int>>& sumMatrix);

// Builds a list of all unordered sum pairs (S1, S2) with S1 < S2
vector<pair<double, string>> buildPairList(const vector<vector<int>>& pairMatrix);

// Prints all pairs sorted from most frequent to least frequent
void printPairList(const vector<pair<double, string>>& pairList, int totalRolls);

// Compute probabilities for triples of sums
vector<vector<vector<int>>> ProbTrios(int sides, const vector<vector<int>>& sumMatrix);

// Builds a list of triples in the format: (count, "(S1,S2,S3)")
vector<pair<double, string>> buildTrioList(const vector<vector<vector<int>>>& trioMatrix);

// Prints all triples sorted from most frequent to least frequent
void printTrioList(const vector<pair<double, string>>& trioList, int totalRolls);

// Print frequencies and probabilities
void printFrequencies(const vector<int>& sumCounts, int totalRolls);

// Compute how many times each sum appears in any trio of the 4 dice
vector<int> computeTrioAppearances(int sides);

// Compute probability of each sum appearing in a trio
vector<double> computeTrioProbabilities(int sides, const vector<int>& trioAppear);

// Compute ideal path lengths scaled from a reference sum
vector<double> computeIdealPaths(const vector<double>& prob, int refSum, double refLength, int sides);

// Print ideal path values
void printIdealPaths(const vector<double>& ideal, int sides);

#endif
