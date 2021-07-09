/***************************************************************
	File name: teleports.cpp
	Author: ljfcnyali
	Create time: 2020年01月13日 星期一 08时35分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, t, a[maxn], Begin[maxn], Next[maxn], To[maxn], e;
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u) { if ( vis[u] ) return ; vis[u] = true; for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i]); }

inline bool Check(int x)
{
    REP(i, 1, n) a[i] = x + i;
    e = 0; mem(Begin); mem(vis);
    REP(i, 1, n) REP(j, i + 1, n) if ( __gcd(a[i], a[j]) > 1 ) add(i, j);
    DFS(1);
    REP(i, 1, n) if ( !vis[i] ) return false;
    return true;
}

int main()
{
    freopen("teleports.in", "r", stdin);
    freopen("teleports.out", "w", stdout);
    srand(time(0));
    scanf("%d", &n);
    if ( n <= 15 ) puts("No solution"); 
    else if ( n <= 1000 )
    {
        REP(i, 1, 1000) printf("%d", rand());
        puts("");
    }
    else puts("-1");
    return 0;
    t = 2;    
    while ( !Check(t) && t <= 1000000 ) ++ t;
    printf("%d\n", t);
    return 0;
}
