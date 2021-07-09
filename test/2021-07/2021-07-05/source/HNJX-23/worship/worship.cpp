/***************************************************************
	File name: worship.cpp
	Author: ljfcnyali
	Create time: 2021年07月05日 星期一 19时13分03秒
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

int n, m, ans;
struct node 
{ 
	int x, y, w; 
	bool operator < (const node &a) const { return y < a.y; }
} a[maxn], b[maxn];
multiset<node> Set;

signed main()
{
    freopen("worship.in", "r", stdin);
    freopen("worship.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) { scanf("%lld", &a[i].x); a[i].y = i; }
	REP(i, 1, m) { scanf("%lld", &b[i].y); b[i].x = i; }
	REP(i, 1, n) scanf("%lld", &a[i].w);
	REP(i, 1, m) scanf("%lld", &b[i].w);
	sort(a + 1, a + n + 1, [](const node &a, const node &b) { return a.x < b.x; });
	sort(b + 1, b + m + 1, [](const node &a, const node &b) { return a.x < b.x; });
	int now = 1;
	REP(i, 1, n)
	{
		while ( now < m && b[now].x <= a[i].x ) { Set.insert(b[now]); ++ now; }
		while ( a[i].w > 0 ) 
		{
			auto it = Set.lower_bound({0, a[i].y, 0});
			if ( it == Set.end() ) break ; 
			int x = it -> x, y = it -> y, w = it -> w;
			Set.erase(it);
			int val = min(w, a[i].w); a[i].w -= val; w -= val; ans += val;
			if ( w > 0 ) Set.insert({x, y, w});
		}
	}
	printf("%lld\n", ans);
    return 0;
}
