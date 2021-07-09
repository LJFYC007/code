/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2020年11月13日 星期五 09时22分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4100;

int a[maxn][maxn];
bool vis[maxn];

int main()
{
    freopen("hhpb.out", "r", stdin);
    int m; scanf("%d%d", &m, &m);   
    REP(i, 1, m) REP(j, 1, m) scanf("%d", &a[i][j]);
    REP(i, 1, m)
    {
        mem(vis);
        REP(j, 1, m) vis[a[i][j]] = vis[a[j][i]] = true;
        REP(j, 1, m + m - 1) if ( !vis[j] ) { cerr << "WA" << endl; exit(0); }
    }
    return 0;
}
