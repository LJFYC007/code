/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年01月20日 星期一 08时36分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;
const int op = (Mod + 1) / 2;

int r[maxn], M;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *a, int n, int inv)
{
    r[0] = 0; REP(i, 1, n - 1) 
    {
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
        if ( r[i] > i ) swap(a[i], a[r[i]]);
    }
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = a[i + j], y = a[i + Mid + j] * sum % Mod;
                a[i + j] = (x + y) % Mod; a[i + Mid + j] = (x - y) % Mod;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) a[i] = a[i] * inv % Mod;
    }
}


inline void Solve(int *f, int *g, int N)
{
    NTT(f, N, 1);
    REP(i, 0, N - 1) f[i] = f[i] * g[i] % Mod;
    NTT(f, N, -1); 
    REP(i, M, N - 1) { f[i % M] = (f[i % M] + f[i]) % Mod; f[i] = 0; }
}

int n, k, a[maxn], b[maxn], sum, N, f[maxn];

signed main()
{
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) { scanf("%lld", &a[i]); sum += a[i]; }
    sum = power(sum, Mod - 2);
    REP(i, 1, n) a[i] = (a[i] * sum % Mod) * op % Mod;
    a[n] = a[n] * 2 % Mod;
    REP(i, 1, n - 1) a[n + n - i] = a[i];
    N = 1; M = n + n;
    while ( N <= (n << 2) ) N <<= 1;
    f[0] = 1;
    while ( k )
    {
        REP(i, 0, N - 1) b[i] = a[i]; NTT(b, N, 1);
        if ( k & 1 ) Solve(f, b, N);
        Solve(a, b, N); k >>= 1;
    }
    REP(i, n + 1, n + n - 1) f[2 * n - i] = (f[2 * n - i] + f[i]) % Mod;
    REP(i, 0, n) printf("%lld ", (f[i] + Mod) % Mod); puts("");
    return 0;
}
