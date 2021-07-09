/***************************************************************
	File name: CF506C.cpp
	Author: ljfcnyali
	Create time: 2021年01月16日 星期六 15时49分19秒
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
const int INF = 1e18;

int n, m, k, p, h[maxn], a[maxn], b[maxn];
bool flag;
priority_queue<int> Q;
vector<int> c[maxn];

inline void Modify(int i, int t)
{
    int x = min(t, b[i] / a[i]);
    t -= x; b[i] -= a[i] * x;
    c[t + 1].push_back(i);
}

inline void Insert(int i, int t, int val)
{
    // vector<int> g;
    while ( !Q.empty() && b[i] < val ) { b[i] += p; int x = Q.top() - 1; Q.pop(); if ( x) Q.push(x); }
    if ( b[i] < val ) { flag = false; return ; } 
    // for ( auto it : g ) if ( it ) Q.push(it);
    Modify(i, t - 1);
}

inline bool Check(int x)
{
    while ( !Q.empty() ) Q.pop(); REP(i, 1, m) c[i].clear(); 
    REP(i, 1, n) { b[i] = x; Modify(i, m); }
    flag = true;
    for ( int i = m; i >= 2; -- i ) 
    {
        Q.push(k);
        for ( auto it : c[i] ) 
        {
            Insert(it, i, a[it]);
            if ( !flag ) return false;
        }
    }
    Q.push(k);
    REP(i, 1, n) 
    {
        Insert(i, 1, h[i]);
        if ( !flag ) return false;
    }
    return flag;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
    int L = 0, R = INF, ans = 0;
    REP(i, 1, n) { scanf("%lld%lld", &h[i], &a[i]); L = max(L, a[i]); }
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Check(Mid) ) { ans = Mid; R = Mid - 1; } 
        else L = Mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
