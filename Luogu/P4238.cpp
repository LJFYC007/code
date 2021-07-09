/***************************************************************
	File name: P4238.cpp
	Author: ljfcnyali
	Create time: 2019年09月28日 星期六 16时35分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1000010;
const int g = 3;
const int Mod = 998244353;


inline int power(int a, int b) 
{ 
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; } 
    return r; 
}

inline void NTT(int a[], int n, int inv)
{
    static int r[maxn];
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(a[i], a[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 )
    {
        int tmp = power(g, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) )
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = (sum * tmp) % Mod ) 
            {
                int x = a[i + j], y = (sum * a[i + j + Mid]) % Mod;
                a[i + j] = (x + y) % Mod; a[i + j + Mid] = (x - y + Mod) % Mod;
            }
        }
    }
    if ( inv == 1 ) return ;
    int x = power(n, Mod - 2);
    REP(i, 0, n - 1) a[i] = (a[i] * x) % Mod;
}

inline void Solve(int a[], int b[], int n)
{
    if ( n == 1 ) { b[0] = power(a[0], Mod - 2); return ; }
    Solve(a, b, (n + 1) >> 1);
    int m = 1;
    while ( m < n << 1 ) m <<= 1;
    static int x[maxn];
    copy(a, a + n, x); fill(x + n, x + m, 0);
    NTT(x, m, 1); NTT(b, m, 1);
    REP(i, 0, m - 1) b[i] = (((2 - (x[i] * b[i]) % Mod + Mod) % Mod) * b[i]) % Mod;
//    REP(i, 0, m - 1) printf("%lld ", b[i]); puts("");
    NTT(b, m, -1); fill(b + n, b + m, 0);
//    REP(i, 0, m - 1) printf("%lld ", b[i]); puts(""); 
}

int n, a[maxn], b[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 0, n - 1) scanf("%lld", &a[i]);
    Solve(a, b, n);
    REP(i, 0, n - 1) printf("%lld ", (b[i] + Mod) % Mod); puts("");
    return 0;
}
