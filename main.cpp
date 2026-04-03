#include <bits/stdc++.h>
using namespace std;

// Store result of DP
struct Result {
    long long maxValue;
    string subsequence;
};

// Function that solves HVLCS
Result computeHVLCS(const string& A, const string& B,
                    const unordered_map<char, int>& valueMap) {
    // 1. Create DP table
    // dp[i][j] = maximum value of a common subsequence
    //            between A[0..i-1] and B[0..j-1]

    // 2. Fill DP table using recurrence

    // 3. Reconstruct one optimal subsequence by walking backward

    // 4. Return both maximum value and subsequence
}

int main() {
    // hard code example

    // Call computeHVLCS(...)
    // Print max value
    // Print subsequence
}