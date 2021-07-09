#include "roads.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, f[maxn][2];
vector<LL> ans;

vector<LL> minimum_closure_costs(int N, vector<int> U, vector<int> V, vector<int> W) 
{
    n = N; ans.resize(n);
    REP(i, 0, n - 1) ans[0] += W[i];
    REP(i, 1, n)
    {
        f[i][0] = min(f[i - 1][0], f[i - 1][1]) + W[i - 1];
        f[i][1] = f[i - 1][0];
    }
    ans[1] = min(f[n][0], f[n][1]);
    return ans;
}
