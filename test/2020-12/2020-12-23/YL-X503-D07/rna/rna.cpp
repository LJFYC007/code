/***************************************************************
	File name: rna.cpp
	Author: ljfcnyali
	Create time: 2020年12月23日 星期三 15时36分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;
const int Mod = 998244353;

int n, L, q, enc, tot, a[maxn], anc[maxn][20], dis[maxn], Next[maxn];
int fac[maxn], ans[maxn], lstans;

inline int Get(int x, int k)
{
    for ( int i = 18; i >= 0; -- i ) if ( dis[anc[x][i]] >= k ) x = anc[x][i];
    return x;
}

inline int calc(int l, int r, int val) { return 0; }

inline void Insert(int lst, int val)
{
    ++ tot; a[tot] = val; dis[tot] = dis[lst] + 1; anc[tot][0] = lst;
    REP(i, 1, 18) anc[tot][i] = anc[anc[tot][i - 1]][i - 1];

    if ( lst == 0 ) { ans[tot] = n + n; return ; }
    int pos = Next[lst];
    while ( pos && a[Get(tot, dis[pos] + 1)] != val ) 
    {
        if ( dis[Next[pos]] * 2 <= dis[pos] ) { pos = Next[pos]; continue ; }
        int t = Next[pos];
        if ( t && a[Get(tot, dis[t] + 1)] != val ) 
        {
            t = dis[pos] - dis[Next[pos]];
            if ( dis[pos] % t == 1 ) pos = Next[pos];
            else if ( dis[pos] % t == 0 ) 
            { 
                ans[tot] = (ans[tot] + calc(t, dis[pos], t)) % Mod;
                pos = Get(pos, t); 
            }
            else 
            { 
                ans[tot] = (ans[tot] + calc(dis[pos] % t, dis[pos], t)) % Mod; 
                pos = Get(pos, dis[pos] % t); 
            }
        }
        else pos = t;
    }
    int x = Get(tot, dis[pos] + 1); if ( a[x] == val ) pos = x;
    Next[tot] = pos; ans[tot] = (ans[tot] + ans[Get(tot, dis[pos])] + fac[dis[tot]]) % Mod;
}

signed main()
{
    freopen("rna.in", "r", stdin);
    freopen("rna.out", "w", stdout);
    scanf("%lld", &n); scanf("%lld%lld%lld%lld", &n, &L, &q, &enc);
    fac[0] = 1; REP(i, 1, maxn - 10) fac[i] = fac[i - 1] * (n + n) % Mod;
    REP(i, 1, L) { int x; scanf("%lld", &x); Insert(i - 1, x); }
    while ( q -- ) 
    {
        int f, x; char s; getchar();
        scanf("%c %lld %lld", &s, &f, &x);
        if ( enc && s == 'A' ) x = (x + lstans) % (n + n);
        if ( enc && s == 'Q' ) x = (x + lstans) % (dis[f + L] + 1);
        
        if ( s == 'A' ) Insert(f + L, x);
        else 
        {
            lstans = ans[f + L] - ans[Get(f + L, x)];
            lstans = (lstans % Mod + Mod) % Mod;
            printf("%lld\n", lstans);
        }
    }
    return 0;
}
