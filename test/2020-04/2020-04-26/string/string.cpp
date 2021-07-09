/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2020年04月28日 星期二 12时36分06秒
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
const int seed = 233;

int T, n, Hash[maxn], p[maxn], inv[maxn], f[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int l, int r)
{
    int sum = (Hash[r] - Hash[l - 1]) % Mod;
    sum = sum * inv[l - 1] % Mod;
    return (sum + Mod) % Mod;
}

inline bool Check(int l, int r, int len)
{
    if ( Get(l, l + len - 1) == Get(r - len + 1, r) ) return true;
    return false;
}

signed main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%lld", &T);
    n = 1000000;
    p[0] = inv[0] = 1; 
    REP(i, 1, n) 
    {
        p[i] = p[i - 1] * seed % Mod;
        inv[i] = inv[i - 1] * power(seed, Mod - 2) % Mod;
    }
    while ( T -- ) 
    {
        scanf("%s", s + 1); n = str(s + 1);
        REP(i, 1, n) Hash[i] = (Hash[i - 1] + (s[i] - 'a' + 1) * p[i - 1]) % Mod;
        f[n / 2] = 0;
        int l = n / 2, r = (n & 1 ? 2 : 1) + l, ans = 0;
        if ( s[1] == s[n] && n > 1 ) ans = 1;
        for ( int i = n / 2 - 1; i >= 1; -- i ) 
        {
            int m = f[i + 1] + 2;
            while ( m >= 0 && (l + m - 1 >= r - m + 1 || !Check(l, r, m)) ) -- m;
            f[i] = max(0ll, m);
            if ( Get(1, i) == Get(n - i + 1, n) ) ans = max(ans, i + f[i]);
            -- l; ++ r;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
