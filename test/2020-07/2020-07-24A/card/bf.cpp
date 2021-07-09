/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 15时29分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, k, f[2][maxn];

int main()
{
    freopen("card.in", "r", stdin);
    freopen("card1.out", "w", stdout);
    scanf("%d%d%d", &m, &n, &k);
    int o = 1;
    REP(i, 1, m) f[o][i] = 1;
    REP(i, 2, n)
    {
        o ^= 1; REP(j, 1, m) f[o][j] = 0;
        REP(j, 1, m) REP(t, 1, m) if ( j + t != k ) f[o][j] = (f[o][j] + f[o ^ 1][t]) % Mod;
    }
    int ans = 0;
    REP(i, 1, m) ans = (ans + f[o][i]) % Mod;
    printf("%d\n", ans);
    return 0;
}
