#include "roads.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], deg[maxn];
vector<LL> ans;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; ++ deg[v]; } 

vector<LL> minimum_closure_costs(int N, vector<int> U, vector<int> V, vector<int> W) 
{
    n = N; ans.resize(n);
    sort(W.begin(), W.end());
    reverse(W.begin(), W.end());
    for ( int i = n - 1; i >= 0; -- i )
        ans[i] = (i == n - 1 ? 0 : ans[i + 1]) + W[i];
    return ans;
}
