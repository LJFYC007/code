/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年09月29日 星期二 19时37分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e8 + 10;
const int Mod = 1e8 + 7;

int n, m, fac[maxn], inv[maxn], g[100], ans;
vector<int> f[100];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline vector<int> operator +(vector<int> a, vector<int> b)
{
    int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
    REP(i, 0, n - 1) a[i] += b[i];
    REP(i, 0, n - 2) { a[i + 1] += a[i] / Mod; a[i] %= Mod; }
    while ( a[n - 1] >= Mod ) 
    {
        a.resize(n + 1); 
        a[n] = a[n - 1] / Mod; a[n - 1] %= Mod;
        ++ n;
    }
    return a;
}

inline int Solve(vector<int> a, vector<int> b)
{
    if ( !a.size() || !b.size() ) return 1;
    int ret = C(a.front(), b.front());
    a.erase(a.begin()); b.erase(b.begin());
    ret = ret * Solve(a, b) % Mod;
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = Mod - 1;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld", &n);
    f[1].resize(1); f[2].resize(1); 
    f[1][0] = f[2][0] = g[1] = g[2] = 1;    
    REP(i, 3, n)
    {
        g[i] = (g[i - 1] + g[i - 2]) % Mod;
        f[i] = f[i - 1] + f[i - 2];
    }

    REP(i, 2, n)    
    {
        int ret = (4 * Solve(f[i] + f[i], f[i]) - g[i] * g[i] - 3) % Mod;
        ans = (ans + 2 * ret - (g[i] + 1) * (g[i] + 1)) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    // ans = 4 * C(2 * n, n) - n * n - 3;
    // cout << 2 * ans - (n + 1) * (n + 1) << endl;
    return 0;
}
