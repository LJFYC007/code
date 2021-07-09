/***************************************************************
	File name: hhpb.cpp
	Author: ljfcnyali
	Create time: 2020年11月13日 星期五 09时11分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2100;

int n, m, f[12][maxn][maxn];

int main()
{
    freopen("hhpb.in", "r", stdin);
    freopen("hhpb.out", "w", stdout);
    scanf("%d", &m);
    puts("2");
    printf("2048\n");
    f[1][1][1] = f[1][2][2] = 1;
    f[1][1][2] = f[1][2][1] = 2;
    REP(o, 2, 11)
    {
        int x = 1 << o - 1;
        REP(i, 1, x) REP(j, i, x) f[o][i][j] = f[o - 1][i][j];
        REP(i, x + 1, x + x) REP(j, i, x + x) f[o][i][j] = f[o - 1][i - x][j - x];
        REP(i, 1, x) REP(j, x + i, x + x) f[o][i][j] = f[o - 1][i][j - x] + x;
        REP(i, 1, x) REP(j, x + i + 1, x + x) f[o][j - x][i + x] = f[o][i][j];
        
        REP(i, 1, x + x) REP(j, i + 1, x + x) f[o][j][i] = f[o][i][j] + x + x - 1;
    }

    REP(i, 1, 2048) { REP(j, 1, 2048) printf("%d ", f[11][i][j]); puts(""); }
    return 0;
}
