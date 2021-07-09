/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年06月16日 星期二 10时09分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], d[maxn], ans = 0x3f3f3f3f;
bool vis[maxn];

inline void DFS(int x, int sum)
{
    if ( sum >= ans ) return ;
    if ( x == n + 1 ) { ans = sum; return ; }
    if ( vis[x] ) DFS(x + 1, sum);
    REP(i, x + 1, n)
    {
        if ( vis[i] ) continue ;
        vis[x] = vis[i] = true;
        DFS(x + 1, sum + 2 * min(a[i], a[x]) + d[i - 1] - d[x - 1]);
        vis[x] = vis[i] = false;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) scanf("%d", &d[i]); 
    REP(i, 2, n - 1) d[i] += d[i - 1];
    REP(i, 1, n) scanf("%d", &a[i]); 
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
