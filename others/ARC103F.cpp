/***************************************************************
	File name: ARC103F.cpp
	Author: ljfcnyali
	Create time: 2021年01月13日 星期三 19时47分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, a[maxn], s[maxn];
vector<pii> Edge;
priority_queue<pii> Q;
map<int, int> Map;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); s[i] = 1; Map[a[i]] = i; Q.push(pii(a[i], i)); }
    REP(o, 1, n - 1)
    {
        pii x = Q.top(); Q.pop(); 
        int t = x.first - n + 2 * s[x.second];
        if ( !Map.count(t) || Map[t] == x.second ) { puts("-1"); return 0; } 
        s[Map[t]] += s[x.second]; Edge.push_back(pii(x.second, Map[t]));
    }
    int sum = -n; REP(i, 1, n) sum += s[i];
    if ( sum != Q.top().first ) puts("-1");
    else for ( auto it : Edge ) printf("%lld %lld\n", it.first, it.second);
    return 0;
}
