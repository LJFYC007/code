/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年06月15日 星期一 17时33分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e4 + 10;
const int Mod = 998244353;

int n, g[maxn], f0[maxn], f1[maxn], f2[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%lld", &n);
    if ( n > maxn / 10 ) 
    {
    static const int R[16] = {0, 4, 8, -1, 16, -10, 4, -12, -48, 26, -44, 15, -16, -4, -4, -1};
	int A[16] = {0, 0, 0, 24, 4, 240, 204, 1316, 2988, 6720, 26200, 50248, 174280, 436904, 1140888, 3436404};
    REP(i, 16, n)
    {
		int x = 0;
        REP(j, 0, 15) x = (x + R[(i - j - 1) & 15] * A[j]) % Mod;
		A[i & 15] = x;
	}
	printf("%lld\n", (A[n & 15] + Mod) % Mod);
    return 0;
    }
    g[0] = 1; g[1] = 0;
    REP(i, 2, n) g[i] = (g[i - 2] + (i > 3 ? g[i - 4] : 0)) % Mod;
    REP(i, 0, n)
    {
        f0[i] = g[i] * (i * i % Mod) % Mod;
        f1[i] = g[i] * ((i + 1) * (i + 1) % Mod) % Mod;
        f2[i] = g[i] * ((i + 2) * (i + 2) % Mod) % Mod;
        REP(j, 0, i - 1)
        {
            f0[i] = (f0[i] + (j * j % Mod) * (f0[i - j - 1] * g[j] % Mod)) % Mod;
            f1[i] = (f1[i] + ((j + 1) * (j + 1) % Mod) * (f0[i - j - 1] * g[j] % Mod)) % Mod;
            f2[i] = (f2[i] + ((j + 1) * (j + 1) % Mod) * (f1[i - j - 1] * g[j] % Mod)) % Mod;
        }
        REP(j, 0, i - 3)
        {
            f0[i] = (f0[i] + ((j + 1) * (j + 1) % Mod) * (f1[i - j - 3] * g[j] % Mod)) % Mod;
            f1[i] = (f1[i] + ((j + 2) * (j + 2) % Mod) * (f1[i - j - 3] * g[j] % Mod)) % Mod;
            f2[i] = (f2[i] + ((j + 2) * (j + 2) % Mod) * (f2[i - j - 3] * g[j] % Mod)) % Mod;
        }
    }
    int ans = (g[n - 1] * n % Mod) * ((n - 1) * (n - 1) % Mod) % Mod;
    if ( n >= 3 ) ans = (ans + (g[n - 3] * n % Mod) * ((n - 1) * (n - 1) % Mod)) % Mod;
    REP(i, 1, n - 1)
    {
        int sum = 0;
        if ( i >= 0 && n - i - 2 >= 0 ) sum = (sum + g[i] * f0[n - i - 2]) % Mod;
        if ( i >= 1 && n - i - 3 >= 0 ) sum = (sum + g[i - 1] * f1[n - i - 3] * 2) % Mod;
        if ( i >= 2 && n - i - 4 >= 0 ) sum = (sum + g[i - 2] * f2[n - i - 4]) % Mod;
        sum = sum * (i * i % Mod) % Mod;
        ans = (ans + sum * (i + 1)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
