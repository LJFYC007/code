/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 08时58分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;
const int maxm = 2e7 + 10;

int n, a[maxn][maxn];
bool vis[maxm];

inline void DFS(int x, int y, int val)
{
    if ( x == n && y == n ) 
    {
        if ( vis[val] ) { cerr << "WA" << endl; exit(0); }
        vis[val] = true; return ;
    }
    if ( x < n ) DFS(x + 1, y, val + a[x + 1][y]);
    if ( y < n ) DFS(x, y + 1, val + a[x][y + 1]);
}

int main()
{
    freopen("path.in", "r", stdin);
    scanf("%d", &n);
    freopen("path.out", "r", stdin);
    REP(i, 1, n) REP(j, 1, n) scanf("%d", &a[i][j]);
    DFS(1, 1, 0);
    cerr << "AC" << endl;
    return 0;
}
