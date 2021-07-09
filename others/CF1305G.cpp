/***************************************************************
	File name: CF1305G.cpp
	Author: ljfcnyali
	Create time: 2020年10月18日 星期日 20时50分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1 << 18; 

int n, f[maxn], num, siz[maxn], len[maxn], g[maxn], cnt[maxn];
LL ans;
vector<int> a[maxn];
bool use[maxn];
bool vis[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline bool Merge(int x, int y, int val)
{
    int fx = find(x), fy = find(y);
    if ( fx != fy ) 
    { 
        ++ num; ans += val; f[fx] = fy;
        return true;
    }
    return false;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    ++ cnt[0];
    REP(i, 1, n) { int x; scanf("%d", &x); ++ cnt[x]; ans -= x; } 
    REP(i, 0, 1 << 18) { f[i] = i; siz[i] = 1; }
    // REP(i, 0, (1 << 18) - 1) { use[i] = a[i].size() > 0; len[i] = a[i].size(); if ( use[i] ) g[i] = a[i][0]; }
    for ( int s = (1 << 18) - 1; s >= 0; -- s ) 
        for ( int i = s; ; i = s & (i - 1) )
        {
            const int j = s ^ i;
            if ( cnt[i] && cnt[j] && Merge(i + 1, j + 1, 0) )
            {
                ans += 1ll * (cnt[i] + cnt[j] - 1) * s;
                cnt[i] = cnt[j] = 1;
            }
            /*
            if ( !vis[i] ) 
            {
                const int pos = g[j];
                while ( len[i] > 1 ) Merge(a[i][-- len[i]], pos, s);
                vis[i] = true;
            }
            else Merge(g[i], g[j], s);
            if ( !vis[j] ) 
            {
                const int pos = g[j];
                while ( len[j] > 1 ) Merge(a[j][-- len[j]], pos, s);
                vis[j] = true;
            }
            */
            if ( !i ) break ; 
        }
    printf("%lld\n", ans);
    return 0;
}
