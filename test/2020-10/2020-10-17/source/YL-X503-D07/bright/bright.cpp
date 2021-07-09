/***************************************************************
	File name: bright.cpp
	Author: ljfcnyali
	Create time: 2020年10月17日 星期六 09时17分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int Mod = 1e9 + 7;

int n, m, x, f[502][502][502];

signed main()
{
    freopen("bright.in", "r", stdin);
    freopen("bright.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &x);
    if ( x == 1 ) f[1][1][1] = 1;
    else f[1][1][0] = 1;
    REP(i, 1, n) 
    if ( i + 1 < x ) 
    {
        int sum = 0;
        for ( int j = i; j >= 1; -- j ) 
        {
            sum = (f[i][j][0] + sum) % Mod;
            f[i + 1][j][0] = (f[i + 1][j][0] + sum) % Mod;
            f[i + 1][j + 1][0] = (f[i + 1][j + 1][0] + f[i][j][0]) % Mod;
        }
    }
    else if ( i + 1 == x ) 
    {
        int sum = 0;
        for ( int j = i; j >= 1; -- j ) 
        {
            sum = (f[i][j][0] + sum) % Mod;
            f[i + 1][j][j + 1] = (f[i + 1][j][j + 1] + sum) % Mod;
            f[i + 1][j + 1][1] = (f[i + 1][j + 1][1] + f[i][j][0]) % Mod;
        }
    }
    else REP(pos, 1, i)
    {
        int sum = 0;
        for ( int j = i; j >= 1; -- j )
        {
            sum = (f[i][j][pos] + sum) % Mod;
            if ( pos <= j ) f[i + 1][j][pos] = (f[i + 1][j][pos] + sum) % Mod;
            else f[i + 1][j][pos + 1] = (f[i + 1][j][pos + 1] + sum) % Mod;
            f[i + 1][j + 1][pos + 1] = (f[i + 1][j + 1][pos + 1] + f[i][j][pos]) % Mod;
        }
    }

    REP(i, 1, m)
    {
        int pos, ret = 0; scanf("%d", &pos);
        REP(j, 1, n) ret = (ret + f[n][j][pos]) % Mod;
        printf("%d ", (ret + Mod) % Mod);
    }
    puts("");
    return 0;
}
