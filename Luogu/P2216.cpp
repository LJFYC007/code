/***************************************************************
	File name: P2216.cpp
	Author: ljfcnyali
	Create time: 2019年07月03日 星期三 14时35分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1310;

int a, b, n, Max[maxn][maxn][9], Min[maxn][maxn][9], ans = 0x3f3f3f3f;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &a, &b, &n);
    memset(Min, 0x3f, sizeof(Min));
    REP(i, 1, a) REP(j, 1, b) { scanf("%d", &Max[i][j][0]); Min[i][j][0] = Max[i][j][0]; }
    REP(k, 1, 8)
        for ( int i = a; i >= 1; -- i)
            for ( int j = b; j >= 1; -- j )
            {
                Max[i][j][k] = max(Max[i][j][k - 1], Max[i + (1 << (k - 1))][j][k - 1]);
                Max[i][j][k] = max(Max[i][j][k], Max[i][j + (1 << (k - 1))][k - 1]);
                Max[i][j][k] = max(Max[i][j][k], Max[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]);
                Min[i][j][k] = min(Min[i][j][k - 1], Min[i + (1 << (k - 1))][j][k - 1]);
                Min[i][j][k] = min(Min[i][j][k], Min[i][j + (1 << (k - 1))][k - 1]);
                Min[i][j][k] = min(Min[i][j][k], Min[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1]);
            }
    int x = n, num = -1;
    while ( x ) { ++ num; x /= 2; }
    int cnt = 1 << num;
    REP(i, 1, a - n + 1)
        REP(j, 1, b - n + 1) 
        {
            int l = i + n - cnt, r = j + n - cnt;
            int Maxx = max(Max[i][j][num], Max[l][r][num]);
            Maxx = max(Maxx, max(Max[i][r][num], Max[l][j][num]));
            int Minn = min(Min[i][j][num], Min[l][r][num]);
            Minn = min(Minn, min(Min[i][r][num], Min[l][j][num]));
            ans = min(ans, Maxx - Minn);
        }
    printf("%d\n", ans);
    return 0;
}
