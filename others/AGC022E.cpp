/***************************************************************
	File name: AGC022E.cpp
	Author: ljfcnyali
	Create time: 2021年01月22日 星期五 17时20分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 1e9 + 7;

int n, f[maxn][4][3];
char s[maxn];

inline void Move(int i, int c)
{
    if ( c == 0 ) REP(x, 0, 3) 
    {
        f[i + 1][x][1] = (f[i + 1][x][1] + f[i][x][0]) % Mod;
        f[i + 1][x][2] = (f[i + 1][x][2] + f[i][x][1]) % Mod;
        f[i + 1][x][1] = (f[i + 1][x][1] + f[i][x][2]) % Mod; 
    }
    if ( c == 1 ) 
    {
        REP(x, 0, 3) REP(y, 1, 2) f[i + 1][x][y - 1] = (f[i + 1][x][y - 1] + f[i][x][y]) % Mod;
        REP(x, 0, 2) f[i + 1][x + 1][0] = (f[i + 1][x + 1][0] + f[i][x][0]) % Mod;
        f[i + 1][3][0] = (f[i + 1][3][0] + f[i][3][0]) % Mod;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    f[0][0][0] = 1;
    REP(i, 1, n)
    {
        if ( s[i] == '0' ) Move(i - 1, 0);
        if ( s[i] == '1' ) Move(i - 1, 1); 
        if ( s[i] == '?' ) Move(i - 1, 0), Move(i - 1, 1);
    }
    int ans = (f[n][1][0] + f[n][2][1] + f[n][3][2] + f[n][3][1] + f[n][3][0]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
