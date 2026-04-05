#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using Clock = chrono::steady_clock;
using Second = chrono::duration<double, micro>;

struct Result {
    long long maxValue;
    string subsequence;
};

Result computeHVLCS(const string& A, const string& B, const unordered_map<char, int>& valueMap) {
    int n = (int)A.size();
    int m = (int)B.size();

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

    // fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + valueMap.at(A[i - 1]));
            }
        }
    }

    // reconstruct one optimal subsequence
    string subsequence;
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (A[i - 1] == B[j - 1] && dp[i][j] == dp[i - 1][j - 1] + valueMap.at(A[i - 1])) {
            subsequence.push_back(A[i - 1]);
            i--;
            j--;
        } else if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(subsequence.begin(), subsequence.end());

    return {dp[n][m], subsequence};
}

int main(int argc, char* argv[]) {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <input_file> [--measure-runtime]\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cout << "Error: could not open input file.\n";
        return 1;
    }

    bool measure_runtime = (argc >= 3 && string(argv[2]) == "--measure-runtime");

    int K;
    fin >> K;

    unordered_map<char, int> valueMap;
    for (int i = 0; i < K; i++) {
        char ch;
        int val;
        fin >> ch >> val;
        valueMap[ch] = val;
    }

    string A, B;
    fin >> A >> B;

    // When checking runtime, takes the average of 5 iterations
    
    if (!measure_runtime)
    {
        Result ans = computeHVLCS(A, B, valueMap);

        cout << ans.maxValue << "\n";
        cout << ans.subsequence << "\n";
    }
    else
    {
        for (int i = 0; i < 5; ++i)
        {
            chrono::time_point<Clock> codeTimer { Clock::now() };
            Result ans = computeHVLCS(A, B, valueMap);
            int elapsed = (int)std::chrono::duration_cast<Second>(Clock::now() - codeTimer).count();

            if (i == 0)
            {
                cout << ans.maxValue << "\n";
                cout << ans.subsequence << "\n";
            }
            
            std::cout << "Runtime: " << elapsed << " microseconds" << std::endl;
        }
    }

    return 0;
}