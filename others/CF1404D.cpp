/***************************************************************
	File name: CF1404D.cpp
	Author: ljfcnyali
	Create time: 2020年10月12日 星期一 14时48分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, sum;
bool vis[maxn], use[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int op)
{
    if ( vis[u] ) return ; vis[u] = true;
    if ( op == 0 ) { use[u] = true; sum += u; }
    for ( int i = Begin[u]; i; i = Next[i] ) 
        DFS(To[i], op ^ 1);
}

signed main()
{
    scanf("%lld", &n);
    if ( n % 2 == 0 ) 
    {
        puts("First");
        REP(i, 1, n) printf("%lld ", i); REP(i, 1, n) printf("%lld ", i);
        fflush(stdout);
        return 0;
    }
    puts("Second"); fflush(stdout);
    REP(i, 1, n + n) 
    { 
        int x; scanf("%lld", &x); 
        // cerr << a[x] << " " << i << endl;
        if ( a[x] ) { add(a[x], i); add(i, a[x]); }
        else a[x] = i;
    }
    REP(i, 1, n) { add(i, i + n); add(i + n, i); }
    REP(i, 1, n + n) if ( !vis[i] ) DFS(i, 0);
    if ( sum % (n + n) == 0 ) 
    {
        REP(i, 1, n + n) if ( use[i] ) printf("%lld ", i);
    }
    else 
    {
        REP(i, 1, n + n) if ( !use[i] ) printf("%lld ", i);
    }
    puts("");
    return 0;
}
