/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月05日 星期五 10时34分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, a, b, f[maxn], h[maxn], ans = INF, Next[maxn], sum, num;
int numa[30], numb[30], F[maxn][30];
pii cur[maxn];
bool flag = false, vis[maxn], Flag;
char s[maxn], t[maxn], g[maxn], S[maxn];

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, x, y);
    int tmp = x; x = y; y = tmp - a / b * y;
}

inline pii Check(int i)
{
    int A = sum * a, B = n, d = __gcd(A, B); 
    if ( i % d != 0 ) return pii(-1, 0);
    int x, y; exgcd(A, B, x, y);
    int k = i / d; x *= k; y *= k; k = B / d; x = (x % k + k) % k;
    return pii(x * sum, k * sum);
}

inline void GET(int o)
{
    for ( int i = 1, j = 0; i < 2 * n; ++ i ) 
    {
        while ( j && s[i - 1] != t[j + 1] ) j = Next[j];
        if ( s[i - 1] == t[j + 1] ) ++ j;
        if ( j == n ) 
        {
            int ret = cur[i - n].first;
            if ( ret == -1 ) continue ;
            if ( !ret && !o ) ret += cur[i - n].second;
            ans = min(ans, ret + o); flag = true;
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &a, &b); a %= n; 
    scanf("%s", s); REP(i, 0, 25) f[i] = s[i] - 'a';
    REP(i, 0, 25) h[i] = i;
    while ( 1 ) 
    {
        ++ sum;
        REP(j, 0, 25) h[j] = f[h[j]];
        bool flag = true;
        REP(j, 0, 25) if ( h[j] != j ) flag = false;
        if ( flag == true ) break ; 
    }
    b %= sum;
    REP(i, 0, 25) h[i] = i;
    REP(i, 1, b) REP(j, 0, 25) h[j] = f[h[j]];
    REP(i, 0, 25) f[i] = h[i];

    REP(i, 0, n - 1) cur[i] = Check(i);

    scanf("%s", s); scanf("%s", t + 1);
    REP(i, 0, n) S[i] = s[i];

    for ( int i = 2, j = 0; i <= n; ++ i )
    {
        while ( j && t[i] != t[j + 1] ) j = Next[j];
        if ( t[i] == t[j + 1] ) ++ j;
        Next[i] = j;
    }

    REP(i, 0, n - 1) ++ numa[s[i] - 'a'];
    REP(i, 1, n) ++ numb[t[i] - 'a'];

    REP(i, 0, 25) F[0][i] = i;
    REP(o, 1, sum) REP(i, 0, 25) F[o][i] = f[F[o - 1][i]];

    REP(o, 0, sum)
    {
        bool flag1 = false;
        REP(i, 0, 25) if ( numa[i] != numb[i] ) flag1 = true;
        REP(i, 0, 25) h[f[i]] = numa[i];
        REP(i, 0, 25) numa[i] = h[i];
        if ( flag1 ) continue ;

        REP(i, 0, n - 1) s[i] = S[(i + a * o) % n];
        REP(i, 0, n - 1) s[i] = F[o][s[i] - 'a'] + 'a';
        REP(i, 0, n - 1) s[n + i] = s[i];
        GET(o);
    }
    if ( flag == false ) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
