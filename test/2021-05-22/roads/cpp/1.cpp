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
vector<LL> ans, f[maxn][2], c[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; ++ deg[v]; } 

inline int lowbit(int x) { return x & -x; }  
inline void modify(vector<int> &c, int pos, int val) 
{ 
    int n = c.size(); ++ pos;
    for ( int i = pos; i < n; i += lowbit(i) ) c[i] += val;
}
inline int query(vector<int> &c, int pos)
{
    int ret = 0; ++ pos;
    for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i];
    return ret;
}

inline void DFS(int u, int fa)
{
    f[u][0].resize(deg[u] + 1); f[u][1].resize(deg[u] + 1); 
    c[u].resize(deg[u] + 2);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ; 
        DFS(v, u);
    }
    for ( int k = deg[u]; k >= 0; -- k ) 
    {
        vector<int> p;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ; 
            if ( k > deg[v] ) 
            {
                f[u][0][k] += f[v][0][deg[v]] + W[i];
                p.push_back(-W[i]); continue ; 
            }
            if ( f[v][1][k] < f[v][0][k] + W[i] ) p.push_back(f[v][1][k] - f[v][0][k] - W[i]);
            f[u][0][k] += f[v][0][k] + W[i];
        }
        sort(p.begin(), p.end()); int num = p.size();
        for ( int i = 0; i < min(k - 1, num); ++ i ) f[u][0][k] += p[i];
        f[u][1][k] = f[u][0][k]; if ( k >= 1 && k - 1 < num ) f[u][0][k] += p[k - 1];
    }
}

vector<LL> minimum_closure_costs(int N, vector<int> U, vector<int> V, vector<int> W) 
{
    n = N; ans.resize(n);
    REP(i, 0, n - 2) add(U[i] + 1, V[i] + 1, W[i]), add(V[i] + 1, U[i] + 1, W[i]);
    DFS(1, 0); 
    REP(i, 0, n - 1) ans[i] = f[1][0][i <= deg[1] ? i : deg[1]];
    return ans;
}
