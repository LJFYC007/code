/***************************************************************
	File name: CF559E.cpp
	Author: ljfcnyali
	Create time: 2021年01月20日 星期三 20时33分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define pos first
#define len second
typedef long long LL;

const int maxn = 110;
const int INF = 0x3f3f3f3f;

int n, f[maxn][maxn][2], ans;
pii a[maxn];

inline int Get(int x, int y) 
{
    if ( y == 0 ) return a[x].pos - 1;
    return a[x].pos - 1 + a[x].len;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%d%d", &a[i].pos, &a[i].len);
    sort(a + 1, a + n + 1); a[0].pos = -INF;
    REP(i, 0, n - 1) REP(j, 0, i) REP(p, 0, 1)
    {
        if ( f[i][j][p] == INF ) continue ;  
        int r = Get(j, p), Max = -INF, pos = 0;
        REP(k, i + 1, n) REP(o, 0, 1)
        {
            if ( Get(k, o) > Max ) { Max = Get(k, o); pos = k; }
            f[k][pos][pos == k ? o : 1] = max(f[k][pos][pos == k ? o : 1], f[i][j][p] + Max - max(r, o == 0 ? a[k].pos - a[k].len - 1 : a[k].pos - 1));
            if ( Get(k, 1) > Max ) { Max = Get(k, 1); pos = k; } 
        }
    }
    REP(i, 1, n) REP(j, 1, n) REP(p, 0, 1) ans = max(ans, f[i][j][p]);
    printf("%d\n", ans);
    return 0;
}
