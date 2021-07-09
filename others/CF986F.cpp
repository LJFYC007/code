/***************************************************************
	File name: CF986F.cpp
	Author: ljfcnyali
	Create time: 2020年10月30日 星期五 10时26分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 2e18;

int T, k, prime[maxn], n, tot, dis[maxn], p[maxn * 100], m;
bool ans[maxn], vis[maxn];
map<int, vector<pii> > Map;
vector<pii> Edge[maxn];
queue<int> Q;

inline void exgcd(int a, int b, int  &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, x, y); int t = x; x = y; y = t - (a / b) * y;
}

inline int pow(int a, int b, int p) 
{ 
    int r = 0; 
    while ( b ) { if ( b & 1 ) r = (r + a) % p; a = (a + a) % p; b >>= 1; } 
    return r; 
}

inline void INIT(int n)
{
    bool vis[maxn * 340]; mem(vis);
    REP(i, 2, n)
    {
        if ( !vis[i] ) p[++ m] = i;
        for ( int j = 1; j <= m && i * p[j] <= n; ++ j ) 
        {
            vis[i * p[j]] = true;
            if ( i % p[j] == 0 ) break ; 
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    INIT(34000000);
    scanf("%lld", &T);
    REP(i, 1, T) { int n, k; scanf("%lld%lld", &n, &k); Map[k].push_back(pii(n, i)); }
    for ( auto it : Map ) 
    {
        k = it.first; tot = 0;
        if ( k == 1 ) continue ;
        for ( int i = 1; p[i] <= k / p[i]; ++ i ) 
        {
            if ( k % p[i] != 0 ) continue ;
            while ( k % p[i] == 0 ) k /= p[i];
            prime[++ tot] = p[i];
        }
        if ( k > 1 ) prime[++ tot] = k;

        // REP(i, 1, tot) cout << prime[i] << " "; cout << endl;

        if ( tot == 1 ) 
        {
            for ( auto i : it.second ) ans[i.second] = (i.first % prime[1] == 0);
            continue ;
        }
        if ( tot == 2 ) 
        {
            int a = prime[1], b = prime[2];
            for ( auto i : it.second ) 
            {
                int n = i.first, x, y;
                exgcd(a, b, x, y); 
                int X = (pow(x, n, b) + b) % b; if ( !X || a <= n / X ) ans[i.second] = true;
                int Y = (pow(y, n, a) + a) % a; if ( !Y || b <= n / Y ) ans[i.second] = true;
            }
            continue ;
        }

        sort(prime + 1, prime + tot + 1); n = prime[1];
        REP(i, 0, n - 1) { dis[i] = INF; vis[i] = false; Edge[i].clear(); }
        dis[0] = 0; vis[0] = true; Q.push(0);
        REP(i, 0, n - 1) REP(j, 2, tot) Edge[i].push_back(pii((i + prime[j]) % n, prime[j]));
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            for ( auto i : Edge[u] ) 
            {
                int v = i.first;
                if ( dis[v] > dis[u] + i.second ) 
                {
                    dis[v] = dis[u] + i.second;
                    if ( !vis[v] ) { vis[v] = true; Q.push(v); }
                }
            }
            vis[u] = false;
        }

        // REP(i, 0, n - 1) printf("%lld ", dis[i]); puts("");
        for ( auto i : it.second ) ans[i.second] = dis[i.first % n] <= i.first;
    }
    REP(i, 1, T) if ( ans[i] ) puts("YES"); else puts("NO");
    return 0;
}
