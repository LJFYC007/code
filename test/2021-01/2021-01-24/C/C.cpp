/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年01月24日 星期日 09时54分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 6e5 + 10;
const int Mod = 998244353;

int n, m, a[maxn], ans, fac[maxn], p[maxn], num[maxn], g[maxn], suf[maxn], pre[maxn], f[maxn];

inline bool Insert(int x, int l, int r)
{
    if ( !a[l] ) return true;
    if ( l == r ) { ++ num[x]; return true; }
    if ( (suf[l] >= r || a[l + r - suf[l]] == a[r]) && (pre[r] <= l || a[l + r - pre[r]] == a[l]) )
    {
        if ( suf[l] >= r ) ++ num[x];
        if ( a[l] != a[r] && pre[r] <= l ) ++ num[x];
        return true;
    }
    return false;
}

inline void Erase(int x, int l, int r)
{
    if ( !a[l] ) return ;
    if ( suf[l] >= r ) -- num[x];
    if ( a[l] != a[r] && pre[r] <= l ) -- num[x];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m); REP(i, 1, n) scanf("%lld", &a[2 * i]);
    n = n * 2 + 1; fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * m % Mod;

    REP(i, 1, n) { pre[i] = f[a[i]]; f[a[i]] = i; } 
    REP(i, 0, m) f[i] = n + 1; for ( int i = n; i >= 1; -- i ) { suf[i] = f[a[i]]; f[a[i]] = i; } 

    Insert(1, 1, 1); int L = 1, R = 1;
    REP(i, 2, n)
    {
        if ( i > R ) { Insert(i, i, i); if ( a[i] ) g[i] = (g[i] + fac[m - num[i]]) % Mod; } 
        else 
        {
            int pos = R + L - i; p[i] = p[pos]; num[i] = num[pos]; g[i] = g[pos];
            while ( p[i] + i > R ) 
            {
                if ( a[pos + p[i]] ) g[i] = (g[i] - fac[m - num[i]]) % Mod;
                Erase(i, pos - p[i], pos + p[i]); -- p[i];
            }
            if ( p[i] + i == R ) L = i - p[i]; 
        }
        while ( i + p[i] < n && i - p[i] > 1 ) 
        {
            ++ p[i];
            if ( !Insert(i, i - p[i], i + p[i]) ) { -- p[i]; break ; }
            if ( a[i + p[i]] ) g[i] = (g[i] + fac[m - num[i]]) % Mod;
        }

        if ( i + p[i] > R ) { R = i + p[i]; L = i - p[i]; } 
        ans = (ans + g[i]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
