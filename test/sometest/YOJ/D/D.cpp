/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 13时56分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, x[maxn], c[maxn], s[maxn], f[maxn], l[maxn], r[maxn];
vector<int> p;
multiset<int> Set;
multiset<pii> t;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); p.push_back(0);
	REP(i, 1, n) { scanf("%lld%lld%lld", &x[i], &c[i], &s[i]); p.push_back(x[i]); } 
	REP(i, 1, n) 
	{
		l[i] = lower_bound(p.begin(), p.end(), x[i] - s[i]) - p.begin() - 1;
		if ( l[i] < 0 ) l[i] = 0;
		r[i] = upper_bound(p.begin(), p.end(), x[i] + s[i]) - p.begin() - 1;
		// cout << l[i] << " " << r[i] << endl;
	}
	int Min = INF, now = 1;
	REP(i, 1, n)
	{
		Set.insert(f[l[i]] + c[i]); 
		t.insert(pii(r[i], i));
		while ( (*t.begin()).first < i ) 
		{
			int pos = (*t.begin()).second;
			t.erase(t.find(pii(r[pos], pos))); 
			Set.erase(Set.find(f[l[pos]] + c[pos]));
		}
		// while ( now <= i && r[now] < i ) { Set.erase(Set.find(f[l[now]] + c[now])); ++ now; } 
		f[i] = *Set.begin();	
		cout << f[i] << " ";
	}
	printf("%lld\n", f[n]);
    return 0;
}
