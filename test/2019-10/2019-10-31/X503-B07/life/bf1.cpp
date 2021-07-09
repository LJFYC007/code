/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 08时32分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30;

int n, m, l[maxn], r[maxn], g[maxn], a[maxn], ans;
bool use[maxn];

inline void DFS(int x, int ret)
{
    if ( x == n + 1 ) 
    { 
        ans = max(ans, ret); return ; 
    }
    if ( !a[x] ) { DFS(x + 1, ret); return ; }
    -- a[x];
    REP(i, 1, m) if ( l[i] <= x && x <= r[i] && !use[i] ) { use[i] = true; DFS(x, ret + g[i]); use[i] = false; } 
    ++ a[x];
    DFS(x + 1, ret);
}

int main()
{
    freopen("life.in.1", "r", stdin);
    freopen("life.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) scanf("%d%d%d", &l[i], &r[i], &g[i]);
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
