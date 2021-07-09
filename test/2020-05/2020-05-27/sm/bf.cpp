/***************************************************************
	File name: sm.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 18时57分20秒
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

int n, m, sum, ans[maxn], g[maxn];
struct node 
{ 
    int u, v, id; 
    node(int a, int b, int c) { u = a; v = b; id = c; }
} ;
vector<pii> a[maxn];
vector<int> b[maxn];
vector<node> f[maxn];

signed main()
{
    freopen("sm.in", "r", stdin);
    freopen("sm.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) 
    {
        int u, v, t; scanf("%lld%lld%lld", &t, &u, &v);
        f[t].push_back(node(u, v, i));
    }
    int x = 1, num = 0;
    REP(o, 0, 100)
    {
        for ( auto i : f[o] ) a[i.u].push_back(pii(i.v, i.id));
        for ( auto i : a[x] ) 
        {
            -- g[x]; 
            b[i.first].push_back(i.second);
            ++ g[i.first];
        }
        for ( auto i : b[x] ) { -- g[x]; ans[i] = o; }
        sum = 0;
        REP(i, 0, 100) if ( i < x ) sum -= g[i]; else sum += g[i];
        if ( num = 0 ) 
        if ( sum >= 0 ) ++ x;
        else -- x;
        cerr << x << " " << sum << endl;
    }
    REP(i, 1, n) printf("%lld\n", ans[i]); puts("");
    return 0;
}
