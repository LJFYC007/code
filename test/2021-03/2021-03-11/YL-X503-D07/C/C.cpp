#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, a[maxn], q, Min, ans;
struct node 
{ 
	int l, r, x; 
	bool operator < (const node &a) const { return l < a.l; } 
} ; 
set<node> Set;

inline void Insert(int l, int r)
{
	// cout << l << " " << r << " " << Min << endl;
	Set.insert({l, r, Min});
	REP(i, l, r - 1) if ( i & 1 ) ans += a[i];
	if ( (l - 1) & 1 ) ans += Min;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	Min = a[n]; int lst = n;
	for ( int i = n - 1; i >= 1; -- i ) if ( a[i] < Min ) 
	{
		Insert(i + 1, lst);
		lst = i; Min = a[i];
	}
	Insert(1, lst); printf("%lld\n", ans + Min);
	scanf("%lld", &q);
	while ( q -- ) 
	{
		int p, d; scanf("%lld%lld", &p, &d); a[p] -= d; Min = min(Min, a[p]);
		auto it = -- Set.lower_bound({p + 1, 0, 0});		
		int l = it -> l, r = it -> r, x = it -> x, now = l;
		// cout << a[p] << " " << x << " " << l << " " << r << endl;
		if ( a[p] >= x ) 
		{
			if ( p & 1 ) ans -= d;
			goto Next ; 
		}
		if ( r != p ) 
		{
			if ( p & 1 ) ans = ans - (a[p] + d) + x;
			Set.erase({l, r, x}); Set.insert({p + 1, r, x}); 
		}
		else Set.erase({l, r, x});

		while ( now != 1 ) 
		{
			auto it = -- Set.lower_bound({now, 0, 0});
			if ( it -> x < a[p] ) 
			{ 
				if ( it -> r & 1 ) ans = ans - x + a[p]; 
				break ; 
			}
			if ( it -> r & 1 ) ans = ans - x + a[it -> r];
			x = it -> x; now = it -> l; Set.erase(it);
		}
		Set.insert({now, p, a[p]});
Next : ; 
	   // for ( auto it : Set ) cout << it.l << " " << it.r << " " << it.x << endl;
	   printf("%lld\n", ans + Min);
	}
	return 0;
}
