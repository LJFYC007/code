/***************************************************************
	File name: lol.cpp
	Author: ljfcnyali
	Create time: 2020年10月19日 星期一 08时52分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;

int x, n = maxn - 10;
double f[maxn][110];

int main()
{
    freopen("lol.in", "r", stdin);
    freopen("lol.out", "w", stdout);
    scanf("%d", &x);
    int m = 101 / x;
    for ( int i = n; i >= 1; -- i ) 
        REP(j, 1, m + 1)
        {
            double y = min(100, x * j) * 1.0 / 100;
            f[i][j] = (1 + f[i + 1][1]) * y + f[i + 1][j + 1] * (1 - y);
        }
    double ans = f[1][1];
    ans /= n;
    printf("%.10lf\n", ans);
    return 0;
}
