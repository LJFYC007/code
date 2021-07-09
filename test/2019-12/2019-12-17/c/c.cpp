/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年12月17日 星期二 19时48分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e4 + 10;
const int INF = 1e18;

int f[2][maxn][510], tot[2], m, n, Mod, g[1010];
deque<pii> Q;
vector<pii> a;
string s;

inline void add(int opt, int w, int v)
{
    ++ tot[opt]; int x = tot[opt];
    REP(i, 0, Mod - 1) f[opt][x][i] = f[opt][x - 1][i];
    REP(i, 0, Mod - 1) f[opt][x][(i + w) % Mod] = max(f[opt][x][(i + w) % Mod], f[opt][x - 1][i] + v);
}

inline void Build()
{
    int Mid = n / 2;
    tot[0] = tot[1] = 0; a.clear();
    REP(i, 1, Mid) { a.push_back(pii(Q.front())); Q.pop_front(); }
    reverse(a.begin(), a.end());
    for ( auto i : a ) add(0, i.first, i.second);
    reverse(a.begin(), a.end());
    while ( !Q.empty() ) { add(1, Q.front().first, Q.front().second); a.push_back(Q.front()); Q.pop_front(); }
    for ( auto i : a ) Q.push_back(i);
}

inline int Solve(int l, int r)
{
    REP(i, 0, Mod - 1) g[i] = g[i + Mod] = f[0][tot[0]][i];
    deque<pii> q; q.clear();
    int L = l + Mod, R = r + Mod;
    for ( int i = R; i >= L; -- i ) 
    {
        while ( !q.empty() && g[i] >= q.back().first ) q.pop_back();
        q.push_back(pii(g[i], i));
    }
    int ans = f[1][tot[1]][0] + q.front().first;
    REP(i, 1, Mod - 1)
    {
        -- L; -- R;
        if ( !q.empty() && q.front().second > R ) q.pop_front();
        while ( !q.empty() && g[L] >= q.back().first ) q.pop_back();
        q.push_back(pii(g[L], L));
        ans = max(ans, f[1][tot[1]][i] + q.front().first);
    }
    return max(ans, -1ll);
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int t; scanf("%lld", &t);
    scanf("%lld%lld", &m, &Mod);
    REP(i, 1, Mod - 1) f[0][0][i] = f[1][0][i] = -INF;
    f[0][0][0] = f[1][0][0] = 0;
    while ( m -- ) 
    {
        cin >> s;
        if ( s == "IF" ) 
        {
            int w, v; scanf("%lld%lld", &w, &v);
            Q.push_front(pii(w, v));                        
            add(0, w, v); ++ n;
        }
        if ( s == "IG" ) 
        {
            int w, v; scanf("%lld%lld", &w, &v);
            Q.push_back(pii(w, v));                        
            add(1, w, v); ++ n;
        }
        if ( s == "DF" ) 
        { 
            Q.pop_front(); 
            if ( !tot[0] ) -- tot[1];
            else -- tot[0]; 
            -- n; 
        }
        if ( s == "DG" ) { Q.pop_back(); -- tot[1]; -- n; }
        if ( s == "QU" ) { int l, r; scanf("%lld%lld", &l, &r); printf("%lld\n", Solve(l, r)); }
        if ( !tot[0] || !tot[1] ) Build();
        // printf("%lld %lld\n", tot[0], tot[1]);
    }
    return 0;
}
