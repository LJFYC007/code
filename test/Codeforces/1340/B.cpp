/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 19时44分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, k, m, suf[maxn], h[maxn][10];
char s[maxn][8];
bool f[10][8], g[maxn][maxn], G[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%s", s[i] + 1);
    for ( int i = n; i >= 1; -- i )
    {
        suf[i] = suf[i + 1];
        REP(j, 1, 7) if ( s[i][j] == '1' ) ++ suf[i];
    }
    f[0][1] = f[0][2] = f[0][3] = f[0][5] = f[0][6] = f[0][7] = true;
    f[1][3] = f[1][6] = true;
    f[2][1] = f[2][3] = f[2][4] = f[2][5] = f[2][7] = true;
    f[3][1] = f[3][3] = f[3][4] = f[3][6] = f[3][7] = true;
    f[4][2] = f[4][3] = f[4][4] = f[4][6] = true;
    f[5][1] = f[5][2] = f[5][4] = f[5][6] = f[5][7] = true;
    f[6][1] = f[6][2] = f[6][4] = f[6][5] = f[6][6] = f[6][7] = true;
    f[7][1] = f[7][3] = f[7][6] = true;
    f[8][1] = f[8][2] = f[8][3] = f[8][4] = f[8][5] = f[8][6] = f[8][7] = true;
    f[9][1] = f[9][2] = f[9][3] = f[9][4] = f[9][6] = f[9][7] = true;


    memset(h, -1, sizeof(h));
    g[0][0] = true;
    REP(i, 1, n) REP(j, 0, k) 
    {
        if ( !g[i - 1][j] ) continue ;
        for ( int o = 9; o >= 0; -- o )
        {
            bool flag = true; int num = 0;
            REP(oo, 1, 7)
            {
                if ( !f[o][oo] && s[i][oo] == '1' ) { flag = false; break ; }
                if ( f[o][oo] && s[i][oo] == '0' ) ++ num; 
            }
            if ( flag ) { h[i][o] = num; g[i][j + num] = true; }
        }
    }
    if ( !g[n][k] ) { puts("-1"); return 0; }

    G[n][k] = true;
    for ( int i = n; i >= 1; -- i ) REP(j, 0, k)
    {
        if ( !G[i][j] ) continue ;
        REP(o, 0, 9) if ( h[i][o] != -1 && j >= h[i][o] ) G[i - 1][j - h[i][o]] = true;
    }

    int num = 0;
    REP(i, 1, n) for ( int o = 9; o >= 0; -- o ) if ( h[i][o] != -1 && G[i][num + h[i][o]] )
    {
        num += h[i][o];
        printf("%d", o);
        break ; 
    }
    puts("");
    return 0;
}
