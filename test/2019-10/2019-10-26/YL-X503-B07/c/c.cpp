/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年10月26日 星期六 10时36分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, a[maxn], c[maxn][2], ans, S;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val, int opt)
{
    for ( int i = pos; i <= n; i += lowbit(i) ) c[i][opt] += val;
}

inline int get(int pos, int opt)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i][opt];
    return sum;
}

inline bool Check(int x)
{
    int y = x * 2 * (get(x, 0) - S) + get(n, 1) - 2 * get(x, 1);
    return y >= 0;
}

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline int Solve(int x)
{
    int f1 = (2 * get(x, 1) - get(n, 1)) % Mod;
    int f2 = (2 * get(x, 0) - 2 * S) % Mod;
    return f1 * power(f2, Mod - 2) % Mod;
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    read(n);
    REP(i, 1, n) 
    {
        read(a[i]);
        S += a[i];
        add(i, a[i], 0);
        add(i, i * a[i], 1);
    }
    read(m);
    REP(i, 1, m)
    {
        int x, y; read(x); read(y);
        add(x, -a[x], 0); add(x, -(x * a[x]), 1);
        S -= a[x]; a[x] = y; S += a[x];
        add(x, a[x], 0); add(x, x * a[x], 1);
        int L = 0, R = 1000000;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( Check(Mid) ) { ans = Mid; L = Mid + 1; }
            else R = Mid - 1;
        }
        printf("%lld\n", (Solve(ans) + Mod) % Mod);
    }
    return 0;
}
