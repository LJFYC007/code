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

int n, a, b, f[maxn], h[maxn], ans = INF, Begin[maxn], Next[maxn], To[maxn], e;
int sum = 1, num;
bool flag = false, vis[maxn];
char s[maxn], t[maxn], g[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    if ( vis[u] ) return ; vis[u] = true; ++ num;
    for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i]);
}

inline bool Check(int x)
{
    REP(i, 0, n - 1) if ( s[x + i] != t[i] ) return false;
    return true;
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
    REP(i, 1, b) REP(j, 0, 25) h[j] = f[h[j]];
    REP(i, 0, 25) { f[i] = h[i]; add(i + 1, f[i] + 1); }
    REP(i, 1, 26) if ( !vis[i] ) 
    {
        num = 0;
        DFS(i);
        sum = sum * num / __gcd(sum, num);
    }
    scanf("%s", s); scanf("%s", t);
    REP(o, 0, sum)
    {
        REP(i, 0, n - 1) s[n + i] = s[i];          

        REP(i, 0, n - 1) if ( Check(i) ) 
        {
            int ret = o == 0 ? sum : 0, num = o == 0 ? 1 : 0;
            while ( ret % n != i ) { ret += sum * a; ++ num; } 
            ans = min(ans, num * sum + o);
            flag = true;
        }
       
        REP(i, 0, n - 1) g[i] = s[i];
        REP(i, 0, n - 1) s[i] = g[(i + a) % n];
        REP(i, 0, n - 1) s[i] = f[s[i] - 'a'] + 'a';
    }
    if ( flag == false ) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
