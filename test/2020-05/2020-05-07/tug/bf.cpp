/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年05月07日 星期四 13时49分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30;

int n, l[maxn], r[maxn], s[maxn], ans = 100000;
bool vis[maxn];

inline void DFS(int x, int sum)
{
    if ( x == n * 2 + 1 ) { ans = min(ans, abs(sum)); return ; }
    if ( !vis[l[x]] ) { vis[l[x]] = true; DFS(x + 1, sum + s[x]); vis[l[x]] = false; }
    if ( !vis[r[x]] ) { vis[r[x]] = true; DFS(x + 1, sum - s[x]); vis[r[x]] = false; }
}

int main()
{
    freopen("tug.in", "r", stdin);
    freopen("tug.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, 2 * n) { scanf("%d%d%d", &l[i], &r[i], &s[i]); r[i] += n; }
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
