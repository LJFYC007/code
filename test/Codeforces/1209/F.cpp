/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2020年10月14日 星期三 14时29分59秒
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
const int Mod = 1e9 + 7;

int n, m, k, id[maxn][2], a[maxn], dis[maxn];
vector<int> p;
vector<pii> Edge[maxn], q;
queue< vector<int> > Q;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    k = n;
    REP(i, 1, m) 
    { 
        int u, v, x = i; scanf("%lld%lld", &u, &v); 
        p.clear(); while ( x ) { p.push_back(x % 10); x /= 10; } reverse(p.begin(), p.end());
        int lst = u;
        for ( int j = 0; j < (int)p.size() - 1; ++ j ) 
        {
            Edge[lst].push_back(pii(p[j], ++ k));
            lst = k;
        }
        Edge[lst].push_back(pii(i % 10, v));
        swap(u, v); lst = u;
        for ( int j = 0; j < (int)p.size() - 1; ++ j ) 
        {
            Edge[lst].push_back(pii(p[j], ++ k));
            lst = k;
        }
        Edge[lst].push_back(pii(i % 10, v));
    }
    dis[1] = 0; REP(i, 2, k) dis[i] = -1; p.clear(); p.push_back(1); Q.push(p);
    while ( !Q.empty() ) 
    {
        p = Q.front(); Q.pop(); q.clear(); int u = p[0];
        for ( auto i : p ) for ( auto j : Edge[i] ) if ( dis[j.second] == -1 ) q.push_back(j);
        sort(q.begin(), q.end());
        // for ( auto i : p ) printf("%lld ", i); puts("");
        for ( int l = 0, r; l < q.size(); l = r + 1 )  
        {
            r = l; while ( r + 1 < q.size() && q[l].first == q[r + 1].first ) ++ r;
            p.clear(); 
            REP(i, l, r) 
            { 
                if ( dis[q[i].second] != -1 ) continue ;
                p.push_back(q[i].second); 
                // if ( q[i].second == 5 ) cout << u << endl;
                dis[q[i].second] = (dis[u] * 10 + q[i].first) % Mod; 
            }
            Q.push(p);
        }
    }
    REP(i, 2, n) printf("%lld\n", (dis[i] + Mod) % Mod);
    return 0;
}
