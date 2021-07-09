/***************************************************************
	File name: ARC098D.cpp
	Author: ljfcnyali
	Create time: 2021年01月20日 星期三 14时59分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, A[maxn], B[maxn], ans, C[maxn], f[maxn];
int dp[maxn], sum[maxn], id[maxn];
pii t[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) { scanf("%lld%lld", &A[i], &B[i]); C[i] = max(0ll, A[i] - B[i]); t[i] = pii(C[i], i); f[i] = i; }
    REP(i, 1, m) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    sort(t + 1, t + n + 1);
    REP(o, 1, n)
    {
        int u = t[o].second;
        vector<int> p; p.clear(); 
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( !vis[v] || u == find(v) ) continue ; 
            v = find(v); sum[u] += sum[v]; f[v] = u; p.push_back(v);
        }
        dp[u] = INF; sum[u] += B[u];
        if ( !p.size() ) dp[u] = max(A[u], B[u]); 
        else for ( auto it : p ) dp[u] = min(dp[u], sum[u] - sum[it] + max(dp[it], C[u]));
        vis[u] = true;
    }
    printf("%lld\n", dp[t[n].second]);
    return 0;
}
