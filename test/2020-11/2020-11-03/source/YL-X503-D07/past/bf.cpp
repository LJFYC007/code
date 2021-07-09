/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年11月03日 星期二 10时39分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, ans;

struct FUCKu
{
    int Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], f[maxn] ;
   
    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

    inline void DFS1(int u, int fa)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            f[v] = u; dis[v] = dis[u] + 1; DFS1(v, u);
        }
    }

    inline int Dis(int x, int y)
    {
        int u = x, v = y;
        if ( dis[x] < dis[y] ) swap(x, y);
        int ret = 0;
        while ( dis[f[x]] >= dis[y] ) { x = f[x]; ++ ret; }
        if ( x == y ) return ret;
        while ( f[x] != f[y] ) { x = f[x]; y = f[y]; ret += 2; }
        return ret + 2;
    }

    inline void Build()
    {
        dis[1] = 1; DFS1(1, 0);
    }
} A, B;
signed main()
{
    freopen("past.in", "r", stdin);
    freopen("past1.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); A.add(u, v); A.add(v, u); }        
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); B.add(u, v); B.add(v, u); }        
    A.Build(); B.Build();
    REP(i, 1, n) REP(j, i + 1, n) ans += A.Dis(i, j) * B.Dis(i, j);
    printf("%lld\n", ans);
    return 0;
}
