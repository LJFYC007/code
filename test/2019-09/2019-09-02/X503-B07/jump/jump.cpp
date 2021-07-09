/***************************************************************
	File name: jump.cpp
	Author: ljfcnyali
	Create time: 2019年09月02日 星期一 19时40分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2010 * 2010;

int n, m, a[2010][2010], q, dt[3][2] = {{0, 1}, {1, 1}, {-1, 1}};
char s[10];

inline int Place(int x, int y) { return (x - 1) * m + y; }

inline int Move(int &x, int &y)
{
    int Max = 0, nextu, nextv;
    REP(i, 0, 2)
    {
        int u = x + dt[i][0], v = y + dt[i][1];
        if ( u > n ) u -= n; if ( v > m ) v -= m;
        if ( u < 1 ) u += n; if ( v < 1 ) v += m;
        if ( a[u][v] > Max ) { Max = a[u][v]; nextu = u; nextv = v; }
    }
    x = nextu; y = nextv;
}

int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) scanf("%d", &a[i][j]);
    scanf("%d", &q);
    int nowx = 1, nowy = 1;
    while ( q -- )
    {
        scanf("%s", s);
        if ( s[0] == 'c' ) 
        {
            int x, y, val; scanf("%d%d%d", &x, &y, &val);
            a[x][y] = val; continue ;
        }
        int k; scanf("%d", &k);
        while ( k -- ) Move(nowx, nowy);
        printf("%d %d\n", nowx, nowy);
    }
    return 0;
}
