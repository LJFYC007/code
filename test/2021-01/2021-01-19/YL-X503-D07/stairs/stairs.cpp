/***************************************************************
	File name: stairs.cpp
	Author: ljfcnyali
	Create time: 2021年01月19日 星期二 11时04分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 1e12;
const int Mod = 998244353;

int n, h[maxn], d, a[maxn], ans;
priority_queue<pii, vector<pii>, greater<pii> > Q[2];
vector<pii> p[2];

inline void Insert(pii s, int op, bool t)
{
    pii v = Q[op ^ 1].top(); Q[op ^ 1].pop();
    if ( !t && s.first + v.first > 0 ) { Q[op].push(pii(-s.first, s.second)); Q[op ^ 1].push(v); return ; }
    int x = min(s.second, v.second);
    ans = (ans + x * (s.first + v.first)) % Mod; 
    p[op].push_back(pii(-s.first - s.first - v.first, x));
    if ( !t ) p[op ^ 1].push_back(pii(-s.first, x));
    s.second -= x; v.second -= x;
    if ( s.second ) Insert(s, op, t);
    else Q[op ^ 1].push(v);
}

signed main()
{
    freopen("stairs.in", "r", stdin);
    freopen("stairs.out", "w", stdout);
    scanf("%lld%lld", &n, &d); REP(i, 1, n) scanf("%lld", &h[i]);
    if ( abs(h[1] - h[n]) > d * (n - 1) ) { puts("Impossible"); return 0; } 
    -- n; REP(i, 1, n) h[i] = h[i + 1] - h[i];
    REP(i, 2, n) { scanf("%lld", &a[i]); a[i] += a[i - 1]; } 
    Q[0].push(pii(INF, INF)); Q[1].push(pii(INF, INF));
    REP(i, 1, n)
    {
        p[0].clear(); p[1].clear();
        if ( h[i] > d ) { Insert(pii(a[i], h[i] - d), 0, 1); Insert(pii(a[i], d + d), 0, 0); }
        if ( h[i] < -d ) { Insert(pii(a[i], -d - h[i]), 1, 1); Insert(pii(a[i], d + d), 1, 0); }
        if ( -d <= h[i] && h[i] <= d ) { Insert(pii(a[i], d + h[i]), 0, 0); Insert(pii(a[i], d - h[i]), 1, 0); }
        for ( auto it : p[0] ) Q[0].push(it);
        for ( auto it : p[1] ) Q[1].push(it);
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
