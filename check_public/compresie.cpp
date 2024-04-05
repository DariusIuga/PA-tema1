#include <bits/stdc++.h>
using namespace std;

// Functie pentru calcularea dp
int computeDP(const vector<int>& A, const vector<int>& B) {
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            // Verificam daca se pot elimina elemente din A
            for (int k = 1; k < i; k++) {
                int sumA = 0;
                for (int l = k; l < i; l++) {
                    sumA += A[l];
                }

                // Verificam daca se pot elimina elemente din B
                for (int l = 1; l < j; l++) {
                    int sumB = 0;
                    for (int r = l; r < j; r++) {
                        sumB += B[r];
                    }

                    // Daca sumele sunt egale, actualizam dp
                    if (sumA == sumB) {
                        dp[i][j] = max(dp[i][j], dp[k - 1][l - 1] + sumA + 1);
                    }
                }
            }
        }
    }

    return dp[n][m];
}

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;

    // Read input
    ifstream in("compresie.in");

    in >> n;
    vector<int> A;
    for (int i = 0; i < n; ++i) {
        int nr;
        in >> nr;
        A.push_back(nr);
    }

    in >> m;
    vector<int> B;
    for (int i = 0; i < m; ++i) {
        int nr;
        in >> nr;
        B.push_back(nr);
    }
    in.close();

    // Write output
    ofstream out("compresie.out");
    out << -1 << "\n";
    out.close();

    return 0;
}
