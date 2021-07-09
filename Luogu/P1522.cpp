/***************************************************************
	File name: P1522.cpp
	Author: ljfcnyali
	Create time: 2019年06月16日 星期日 10时17分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 210;

int n, a[maxn], b[maxn];
double dis[maxn], f[maxn][maxn], ans = 0x3f3f3f3f, ans1;

inline double js(int x, int y)
{
    return sqrt((double)(a[x] - a[y]) * (a[x] - a[y]) + (b[x] - b[y]) * (b[x] - b[y]));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
    REP(i, 1, n)
    {
        getchar(); getchar();
        REP(j, 1, n)
        {
            char c = getchar();
            if ( c == '0' ) f[i][j] = 0x3f3f3f3f;
            else f[i][j] = js(i, j);
        }
        f[i][i] = 0;
    }
    REP(k, 1, n)
        REP(i, 1, n)
            REP(j, 1, n)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    REP(i, 1, n)
    {
        REP(j, 1, n)
            if ( f[i][j] != 0x3f3f3f3f ) dis[i] = max(dis[i], f[i][j]);
        ans1 = max(ans1, dis[i]);
    }
    REP(i, 1, n) REP(j, 1, n) if ( f[i][j] == 0x3f3f3f3f ) ans = min(ans, dis[i] + dis[j] + js(i, j));
    printf("%.6lf\n", max(ans1, ans));
    return 0;
}
