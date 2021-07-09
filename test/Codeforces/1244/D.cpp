/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 18时15分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 200010;
const int INF = 1e18;

int n, c[maxn][4], ans, d[maxn], Ans[maxn], p[maxn];
int Begin[maxn], Next[maxn], To[maxn], e, a[maxn], tot;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        vis[v] = true; p[++ tot] = v; DFS(v);
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &n);
    REP(j, 1, 3) REP(i, 1, n) scanf("%I64d", &c[i][j]);
    REP(i, 1, n - 1)
    {
        int u, v; scanf("%I64d%I64d", &u, &v);
        add(u, v); add(v, u); ++ d[u]; ++ d[v];
    }
    int sum = 0, s;
    REP(i, 1, n) if ( d[i] % 2 == 1 ) { ++ sum; s = i; }
    if ( sum != 2 ) { puts("-1"); return 0; }
    vis[s] = true; p[++ tot] = s; DFS(s);
    ans = INF;
    REP(i, 1, 3)
        REP(j, 1, 3)
        {
            if ( i == j ) continue ;
            REP(k, 1, 3)
            {
                if ( k == i || k == j ) continue ;
                sum = 0;
                REP(o, 1, n)
                {
                    if ( o % 3 == 1 ) a[p[o]] = i, sum += c[p[o]][i];
                    if ( o % 3 == 2 ) a[p[o]] = j, sum += c[p[o]][j];
                    if ( o % 3 == 0 ) a[p[o]] = k, sum += c[p[o]][k];
                }
                if ( sum < ans ) 
                {
                    ans = sum;
                    REP(o, 1, n) Ans[o] = a[o];
                }
            }
        }
    printf("%I64d\n", ans);
    REP(i, 1, n) printf("%I64d ", Ans[i]); puts("");
    return 0;
}
