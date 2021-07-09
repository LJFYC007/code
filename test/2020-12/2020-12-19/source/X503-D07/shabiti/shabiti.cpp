/***************************************************************
	File name: shabiti.cpp
	Author: ljfcnyali
	Create time: 2020年12月19日 星期六 10时30分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;

int T, n, m, len, k = 1000;
bitset<maxn> a[maxn], b, c, t[maxn], fuck, belong[maxn], A[maxn], now;
char s[maxn];

inline void Insert(int x)
{
    fuck = t[x]; now.reset(); now[x] = true;
    REP(i, 1, k) if ( fuck[i] ) 
    {
        if ( !a[i][i] ) { belong[i] = now; a[i] = fuck; return ; }
        fuck ^= a[i]; now ^= belong[i];
    }

    fuck = now;
    REP(i, 1, n) if ( fuck[i] )
    {
        if ( !A[i][i] ) { A[i] = fuck; return ; }
        fuck ^= A[i];
    }
}

inline void Delete(int x)
{
    for ( int i = n; i >= 1; -- i ) if ( A[i][x] )
    {
        REP(j, 1, i - 1) if ( A[j][x] ) A[j] ^= A[i];
        REP(j, 1, k) if ( belong[j][x] ) belong[j] ^= A[i];
        A[i].reset(); return ;
    }

    for ( int i = k; i >= 1; -- i ) if ( belong[i][x] ) 
    {
        REP(j, 1, i - 1) if ( belong[j][x] ) { belong[j] ^= belong[i]; a[j] ^= a[i]; }
        a[i].reset(); belong[i].reset(); return ;
    }
}

signed main()
{
    freopen("shabiti.in", "r", stdin);
    freopen("shabiti.out", "w", stdout);
    scanf("%lld%lld%lld", &T, &n, &m);
    REP(i, 1, n) Insert(i);
    REP(i, 1, m)
    {
        int u, v; scanf("%lld%lld", &u, &v);
        scanf("%s", s + 1); len = str(s + 1);
        b.reset(); REP(i, 1, len) b[k - len + i] = s[i] - '0';

        Delete(u); t[u] ^= b; Insert(u);
        Delete(v); t[v] ^= b; Insert(v);

        b.reset();
        REP(o, 1, k) if ( !b[o] ) b ^= a[o];

        bool flag = false;
        REP(j, 1, k) if ( b[j] ) 
        {
            REP(o, j, k) printf("%lld", (int)b[o]);
            puts(""); flag = true; break ; 
        }
        if ( !flag ) puts("0");
    }
    return 0;
}
