/***************************************************************
	File name: city.cpp
	Author: ljfcnyali
	Create time: 2020年10月17日 星期六 14时23分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;

int T, n, p, f[maxn][2];

int main()
{
    freopen("city.in", "r", stdin);
    freopen("city.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &p);
        REP(i, 0, n) f[i][0] = f[i][1] = 0;
        f[1][1] = 1;
        REP(i, 2, n)
        {
            f[i][0] = (f[i - 1][0] + f[i - 1][1]) % Mod;
            f[i][1] = f[i - 1][1];
            if ( i != 2 && (i - 2) % p == 0 ) 
            {
                f[i][1] = (f[i][1] + f[i - 1][0]) % Mod;
                f[i][1] = (f[i][1] + f[i - 1][1]) % Mod;
            }
        }
        printf("%d\n", f[n][1]);
    }
    return 0;
}
