/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 14时25分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define piii pair<pii, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 100010;

int n, m, ans, t, r[maxn], now, num;
vector<pii> q[maxn];
vector<piii> f;
multiset<int> Set;
multiset<piii> a;
priority_queue<pii, vector<pii>, greater<pii> > Q[maxn];
map<int, int> Map;

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("park.in", "r", stdin);
    freopen("park.out", "w", stdout);
    read(n); read(m);
    m = 0;
    REP(i, 1, n) 
    { 
        int l, r, x; read(l); read(r); read(x);
        if ( !Map[x] ) Map[x] = ++ m;
        q[Map[x]].push_back(make_pair(l, r)); 
    }
    REP(i, 1, m) 
    {
        if ( !q[i].size() ) continue ; 
        sort(q[i].begin(), q[i].end(), [](pii a, pii b) { return a.y > b.y; });
        r[0] = q[i][0].y;
        REP(j, 1, q[i].size() - 1)
            r[j] = min(q[i][j].y, r[j - 1] - 1);
        Set.clear(); REP(j, 0, q[i].size() - 1) Set.insert(r[j]);
        sort(q[i].begin(), q[i].end(), [](pii a, pii b) { return a.x > b.x; });
        REP(j, 0, q[i].size() - 1)
        {
            auto it = -- Set.upper_bound(q[i][j].y);
            q[i][j].y = *it; Set.erase(it);
            if ( q[i][j].x > q[i][j].y ) { puts("GG"); return 0; }
            a.insert(make_pair(make_pair(q[i][j].y, q[i][j].x), i)); 
            f.push_back(make_pair(q[i][j], i));
        }
    }
    sort(f.begin(), f.end(), [](piii a, piii b) { return a.x.x < b.x.x; });
    Set.clear();
    while ( !a.empty() ) 
    {
        ++ ans; t = a.begin() -> x.x;
        while ( now < n && f[now].x.x <= t ) 
        {
            if ( Q[f[now].y].empty() ) Set.insert(f[now].y);
            Q[f[now].y].push(make_pair(f[now].x.y, f[now].x.x)); ++ now;
        }
        for ( set<int> :: iterator i = Set.begin(); i != Set.end(); )
        {
            auto it = Q[*i].top(); Q[*i].pop();
            a.erase(make_pair(make_pair(it.x, it.y), *i));
            if ( Q[*i].empty() ) { set<int> :: iterator p = i; ++ i; Set.erase(p); }
            else ++ i;
        }
    }
    printf("%d\n", ans);
    return 0;
}
