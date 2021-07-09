/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 08时20分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1000010;
const int Mod = 998244353;

int p[maxn][2], n, m, Hash[maxn][2], inv[maxn][2], seed[2];
char s[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline int calc(int l, int r, int opt)
{
    int sum = Hash[r][opt] - Hash[l - 1][opt];
    if ( n >= r + 1 ) sum = sum * inv[n - r - 1][opt] % Mod;
    else sum = sum * seed[opt] % Mod;
    sum = (sum + Mod) % Mod;
    return sum;
}

signed main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    seed[0] = 233; seed[1] = 107;
    p[0][0] = p[0][1] = inv[0][0] = inv[0][1] = 1; 
    REP(i, 1, maxn - 10) p[i][0] = p[i - 1][0] * seed[0] % Mod, p[i][1] = p[i - 1][1] * seed[1] % Mod;
    REP(i, 1, maxn - 10) inv[i][0] = power(p[i][0], Mod - 2), inv[i][1] = power(p[i][1], Mod - 2);
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) 
    {
        Hash[i][0] = (Hash[i - 1][0] + p[n - i][0] * (s[i] - 'a' + 1)) % Mod;
        Hash[i][1] = (Hash[i - 1][1] + p[n - i][1] * (s[i] - 'a' + 1)) % Mod;
    }
    scanf("%lld", &m); 
    while ( m -- )
    {
        int x, y, len; scanf("%lld%lld%lld", &x, &y, &len);
        if ( x + len - 1 > n || y + len - 1 > n ) { puts("NO"); continue ; }
        if ( calc(x, x + len - 1, 0) == calc(y, y + len - 1, 0) && calc(x, x + len - 1, 1) == calc(y, y + len - 1, 1) ) puts("YES");
        else puts("NO");
    }
    return 0;
}
