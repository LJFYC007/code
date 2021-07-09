/***************************************************************
	File name: CF1334G.cpp
	Author: ljfcnyali
	Create time: 2020年04月14日 星期二 21时17分42秒
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

int r[maxn], val[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *a, int n, int inv)
{
    vector<unsigned long long> f(n);
    copy(a, a + n, f.begin());
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod ) 
            {
                int y = f[i + Mid + j] * sum % Mod;
                f[i + Mid + j] = f[i + j] - y + Mod;
                f[i + j] += y;
            }
        }
    }
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2);
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
    REP(i, 0, n - 1) a[i] = f[i] % Mod;
}

int n, m, p[maxn], ans[maxn], f[maxn], g[maxn], a[maxn], b[maxn], c[maxn];
char s[maxn], t[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 1, 26) scanf("%lld", &p[i]);
    REP(i, 1, 26) val[i] = rand() % 10000 + 1;
    scanf("%s", s + 1); n = str(s + 1); reverse(s + 1, s + n + 1);
    scanf("%s", t + 1); m = str(t + 1);
    REP(i, 1, n) { a[i] = s[i] - 'a' + 1; b[i] = p[a[i]]; }
    REP(i, 1, m) c[i] = t[i] - 'a' + 1;
    REP(i, 1, n) { a[i] = val[a[i]]; b[i] = val[b[i]]; }
    REP(i, 1, m) c[i] = val[c[i]];
    int len = 1;  
    while ( len < (n + m) ) len <<= 1;
    REP(i, 0, len - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (len >> 1) : 0);

    REP(i, 0, len - 1) f[i] = g[i] = 0;
    REP(i, 1, m) f[i] = power(c[i], 3);
    REP(i, 1, n) g[i] = (a[i] + b[i]) % Mod;
    NTT(f, len, 1); NTT(g, len, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    NTT(f, len, -1);
    REP(i, n + 1, m + 1) ans[i] = (ans[i] - 2 * f[i]) % Mod;

    REP(i, 0, len - 1) f[i] = g[i] = 0;
    REP(i, 1, m) f[i] = power(c[i], 2);
    REP(i, 1, n) g[i] = (a[i] * a[i] + b[i] * b[i] + 4 * a[i] * b[i]) % Mod;
    NTT(f, len, 1); NTT(g, len, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    NTT(f, len, -1);
    REP(i, n + 1, m + 1) ans[i] = (ans[i] + f[i]) % Mod;

    REP(i, 0, len - 1) f[i] = g[i] = 0;
    REP(i, 1, m) f[i] = c[i];
    REP(i, 1, n) g[i] = (a[i] * b[i] % Mod) * (a[i] + b[i]) % Mod;
    NTT(f, len, 1); NTT(g, len, 1);
    REP(i, 0, len - 1) f[i] = f[i] * g[i] % Mod;
    NTT(f, len, -1);
    REP(i, n + 1, m + 1) ans[i] = (ans[i] - 2 * f[i]) % Mod;

    int sum = 0;
    REP(i, 1, n) sum = (sum + (a[i] * a[i] % Mod) * (b[i] * b[i] % Mod)) % Mod;
    REP(i, n + 1, m + 1) ans[i] = (ans[i] + sum) % Mod;
    sum = 0;
    REP(i, 1, n) sum = (sum + power(c[i], 4)) % Mod;
    REP(i, n + 1, m + 1)
    {
        ans[i] = (ans[i] + sum) % Mod;
        sum = (sum + power(c[i], 4) - power(c[i - n], 4)) % Mod;
    }

    REP(i, n + 1, m + 1) printf("%d", ans[i] == 0 ? 1 : 0); puts(""); 
    return 0;
}
