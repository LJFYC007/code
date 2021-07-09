/***************************************************************
	File name: idioms.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 08时28分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2000010;
const int INF = 100000000000;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, f[maxn][2], out[maxn];
bool use[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

signed main()
{
    freopen("idioms.in", "r", stdin);
    freopen("idioms.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) 
    { 
        int u, v; scanf("%lld%lld", &u, &v); 
        ++ out[u]; add(v, u);
    }
    REP(i, 1, n) f[i][0] = INF;
    queue<pii> Q;
    REP(i, 1, n) 
    {
        if ( out[i] ) continue ;
        f[i][0] = f[i][1] = 0;
        Q.push(make_pair(i, 0));
        Q.push(make_pair(i, 1));
    }
    while ( !Q.empty() ) 
    {
        int u = Q.front().first, x = Q.front().second; Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( x == 1 )
            {
                if ( f[v][0] != INF ) continue ;
                f[v][0] = min(f[v][0], f[u][1] + 1);
                Q.push(make_pair(v, 0));
            }
            else
            {
                f[v][1] = max(f[v][1], f[u][0] + 1);
                -- out[v]; if ( !out[v] ) Q.push(make_pair(v, 1));
            }
        }
    }
    REP(i, 1, n) printf("%lld\n", f[i][0] == INF ? -1 : f[i][0]);
    return 0;
}
