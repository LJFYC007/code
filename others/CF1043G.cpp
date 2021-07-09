/***************************************************************
	File name: CF1043G.cpp
	Author: ljfcnyali
	Create time: 2020年12月30日 星期三 11时36分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, Hash[2][maxn], fac[2][maxn], inv[2][maxn], num[maxn][26], cnt;
int sa[maxn], rk[maxn], f[maxn], g[maxn], st[maxn][20], Log[maxn], Mod[2] = {1000000007, 998244353}, seed[2] = {233, 97};
char s[maxn];
set<int> Set1, Set2;

inline int power(int a, int b, int op) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod[op]; a = 1ll * a * a % Mod[op]; b >>= 1; } return r; }
inline int Get(int op, int l, int r) { return ((LL)Hash[op][r] - Hash[op][l - 1] + Mod[op]) * inv[op][l - 1] % Mod[op]; }
inline int Find(int l, int r) { int x = Log[r - l + 1]; return min(st[l][x], st[r - (1 << x) + 1][x]); }

inline int Get1(int x, int y, int r)
{
    int l = 1, pos = 0;
    while ( l <= r ) 
    { 
        int Mid = l + r >> 1;
        if ( Get(0, x - Mid + 1, x) == Get(0, y - Mid + 1, y) && Get(1, x - Mid + 1, x) == Get(1, y - Mid + 1, y)) { pos = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    return pos;
}

inline int Get2(int x, int y, int r)
{
    int l = 1, pos = 0; r = min(r, n - y + 1);
    while ( l <= r ) 
    { 
        int Mid = l + r >> 1;
        if ( Get(0, x, x + Mid - 1) == Get(0, y, y + Mid - 1) && Get(1, x, x + Mid - 1) == Get(1, y, y + Mid - 1) ) { pos = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    return pos;
}

inline int Solve(int l, int r)
{
    int len = n;
    REP(i, 1, sqrt(len)) if ( i < r - l + 1 && Get(0, l, l + i - 1) == Get(0, r - i + 1, r) && Get(1, l, l + i - 1) == Get(1, r - i + 1, r) ) return i;
    int Min = n + 1;
    REP(t, rk[l] - sqrt(len), rk[l] + sqrt(len)) if ( 1 <= t && t <= n ) 
    {
        int i = sa[t];
        if ( l < i && i <= r && Get(0, l, l + r - i) == Get(0, i, r) && Get(1, l, l + r - i) == Get(1, i, r) ) Min = min(Min, r - i + 1);
    }
    return Min == n + 1 ? -1 : Min;
}

inline void SA()
{
    int x[maxn], y[maxn], c[maxn], m = 25;
    REP(i, 1, n) { x[i] = s[i] - 'a'; ++ c[x[i]]; } REP(i, 1, m) c[i] += c[i - 1];
    for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
    for ( int k = 1; k <= n; k <<= 1 ) 
    {
        mem(c); int tot = 0;
        REP(i, n - k + 1, n) y[++ tot] = i; REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
        REP(i, 1, n) ++ c[x[y[i]]]; REP(i, 1, m) c[i] += c[i - 1];
        for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
        swap(x, y); x[sa[1]] = tot = 1;
        REP(i, 2, n) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot;
        m = tot;
    }
    REP(i, 1, n) rk[sa[i]] = i;
}

inline void Modify1(int l, int r, int val)
{
    if ( l > r ) return ;
    auto it = Set1.lower_bound(l);
    while ( it != Set1.end() && *it <= r ) { f[*it] = val; auto nxt = it; ++ nxt; Set1.erase(it); it = nxt; }
}

inline void Modify2(int l, int r, int val)
{
    if ( l > r ) return ;
    auto it = Set2.lower_bound(l);
    while ( it != Set2.end() && *it <= r ) { g[*it] = val; auto nxt = it; ++ nxt; Set2.erase(it); it = nxt; }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); scanf("%s", s + 1); SA();
    REP(op, 0, 1)
    {
        fac[op][0] = inv[op][0] = 1; 
        REP(i, 1, n) 
        { 
            fac[op][i] = 1ll * fac[op][i - 1] * seed[op] % Mod[op];
            inv[op][i] = 1ll * inv[op][i - 1] * power(seed[op], Mod[op] - 2, op) % Mod[op]; 
        }
        REP(i, 1, n) 
        {
            Hash[op][i] = (Hash[op][i - 1] + 1ll * fac[op][i] * (s[i] - 'a')) % Mod[op];
            REP(j, 0, 25) num[i][j] = num[i - 1][j];
            ++ num[i][s[i] - 'a'];
        }
    }

    REP(i, 1, n) { f[i] = g[i] = n + 1; Set1.insert(i); Set2.insert(i); }
    REP(len, 1, n) for ( int i = len; i + len < n; i += len ) 
    {
        int x = Get1(i, i + len, len), y = Get2(i + 1, i + len + 1, len);
        Modify1(i - x + 1, i - len + y + 1, len); Modify2(i + len + len - x, i + len + y, len);
    }
    REP(i, 1, n) st[i][0] = i + f[i] + f[i] - 1;
    REP(j, 1, 18) REP(i, 1, n) st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
    REP(i, 2, n) Log[i] = Log[i >> 1] + 1;

    scanf("%d", &m); cnt = 0;
    while ( m -- ) 
    {
        int l, r; scanf("%d%d", &l, &r);
        int len = r - l + 1; ++ cnt;
        for ( int i = 1; i * i <= len; ++ i ) 
        {
            if ( i != len && len % i == 0 && Get(0, l, l + (len - i) - 1) == Get(0, r - (len - i) + 1, r) && 
                Get(1, l, l + (len - i) - 1) == Get(1, r - (len - i) + 1, r) 
                    ) { puts("1"); goto Next ; } 
            if ( i != 1 && len % i == 0 && Get(0, l, l + (len - len / i) - 1) == Get(0, r - (len - len / i) + 1, r) && 
                Get(1, l, l + (len - len / i) - 1) == Get(1, r - (len - len / i) + 1, r) 
                    ) { puts("1"); goto Next ; } 
        }
        if ( l + f[l] + f[l] - 1 <= r ) { puts("2"); continue ; }
        if ( r - g[r] - g[r] + 1 >= l ) { puts("2"); continue ; }
        if ( Solve(l, r) != -1 ) { puts("2"); continue ; }

        if ( num[r][s[r] - 'a'] - num[l - 1][s[r] - 'a'] >= 2 ) { puts("3"); continue ; }
        if ( num[r][s[l] - 'a'] - num[l - 1][s[l] - 'a'] >= 2 ) { puts("3"); continue ; }
        if ( Find(l, r) <= r ) { puts("3"); continue ; }
        REP(j, 0, 25) if ( num[r][j] - num[l - 1][j] >= 2 ) { puts("4"); goto Next ; }
        puts("-1");
Next : ;
    }
    return 0;
}
