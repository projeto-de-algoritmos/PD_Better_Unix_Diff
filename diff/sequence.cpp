#include "sequence.h"

using namespace std;

string result;

void retonar_string(const int& i, const int& j, const string& a, const string& b, const int& pm, const int& pg, const vector<vector<int>>& M) {
    if(i == 0 or j == 0) return;

    if(M[i][j] == (a[i-1]==b[j-1] ? 0 : pm) + M[i-1][j-1]) {
        result.push_back(a[i-1]);
        retonar_string(i-1, j-1, a, b, pm, pg, M);
        return;
    }

    if(M[i][j] == pg + M[i-1][j]) {
        result.push_back('_');
        retonar_string(i-1, j, a, b, pm, pg, M);
        return;
    }

    retonar_string(i, j-1, a, b, pm, pg, M);
    return;
}

void sequence(const int& m, const int& n, const string& a, const string& b, const int& pm, const int& pg) {
    vector<int> temp(n+1, 0);
    vector<vector<int>> M(m+1, temp);
    for(int i = 0; i <= m; ++i)
        M[i][0] = i*pg;

    for(int i = 0; i <= n; ++i)
        M[0][i] = i*pg;

    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            M[i][j] = min({M[i-1][j-1] + (a[i-1]==b[j-1] ? 0 : pm),
                           pg + M[i-1][j],
                           pg + M[i][j-1]});
        }
    }

    retonar_string(m, n, a, b, pm, pg, M);
}
