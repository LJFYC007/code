/***************************************************************
	File name: P2467.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 14时02分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 5010;

int f[2][maxn], n, sum, ans, p, x = 1;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &p);
    f[1][1] = 1;
    REP(i, 2, n)
    {
        sum = 0; x = !x;
        f[x][1] = 0;
        for ( int j = i - 1; j >= 1; -- j )
        {
            sum = (sum + f[!x][j]) % p;
            f[x][i - j + 1] = sum;
            f[!x][j] = 0;
        }
    }
    REP(i, 1, n) ans = (ans + f[x][i]) % p;
    ans = (ans * 2) % p;
    printf("%d\n", ans);
    return 0;
}
