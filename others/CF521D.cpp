/***************************************************************
	File name: CF521D.cpp
	Author: ljfcnyali
	Create time: 2021年05月26日 星期三 09时39分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;

int k, n, m, a[maxn]; pii b[maxn];
struct node { double val; int op, id; } ;
bool operator < (const node &a, const node &b) { return a.val < b.val; } 
vector<pii> ans; vector<node> p, c[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &k, &n, &m);
	REP(i, 1, k) { scanf("%lld", &a[i]); b[i] = pii(-1, -1); } 
	REP(i, 1, n)
	{
		int op, x, y; scanf("%lld%lld%lld", &op, &x, &y);
		if ( op == 1 && b[x].first < y ) b[x] = pii(y, i);
		if ( op == 2 ) c[x].push_back({(double)y, 2, i});
		if ( op == 3 ) p.push_back({(double)y, 3, i});
	}
	REP(i, 1, k) 
	{
		if ( b[i].first > a[i] ) c[i].push_back({(double)b[i].first - a[i], 1, b[i].second});
		sort(c[i].begin(), c[i].end()); reverse(c[i].begin(), c[i].end());
		for ( auto it : c[i] ) 
		{
			p.push_back({(it.val + a[i]) / a[i], it.op, it.id});
			a[i] += it.val;
		}
	}
	sort(p.begin(), p.end());
	while ( !p.empty() && m ) 
	{
		ans.push_back(pii(p.back().op, p.back().id));
		p.pop_back(); -- m;
	}
	sort(ans.begin(), ans.end(), [](const pii &a, const pii &b) { return a.first < b.first; });
	cout << ans.size() << endl;
	for ( auto it : ans ) printf("%lld ", it.second); puts("");
    return 0;
}
