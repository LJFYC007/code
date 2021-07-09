/***************************************************************
	File name: AGC037F.cpp
	Author: ljfcnyali
	Create time: 2021年01月31日 星期日 20时57分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;

int n, L, a[maxn], ans;
pii b[maxn];
struct node 
{ 
	int l, r, len; 
	vector<int> pre, suf;
	bool operator < ( const node &a ) const { return l < a.l; } 
} ;
vector<node> p;
vector<int> g;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &L);
	REP(i, 1, n) { scanf("%lld", &a[i]); b[i] = pii(a[i], i); }
	sort(b + 1, b + n + 1);
	int now = 1, k = 0; g.push_back(0); g.push_back(1); 
	while ( 1 ) 
	{
		if ( p.empty() ) { if ( now > n ) break ; k = b[now].x; }
		else ++ k;
		while ( now <= n && b[now].x == k ) { p.push_back({b[now].y, b[now].y, 1, g, g}); ++ ans; ++ now; }

		sort(p.begin(), p.end()); vector<node> q;
		for ( int l = 0, r; l < p.size(); l = r + 1 ) 
		{
			r = l; int num = p[l].len;
			while ( r + 1 < p.size() && p[r].r + 1 == p[r + 1].l ) { ++ r; num += p[r].len; } 
			if ( num < L ) continue ; 
			int sum = 2, j = l, y = 1, val = 0; 
			REP(i, l, r) for ( int x = 1; x < p[i].pre.size(); ++ x ) val += p[i].pre[x];
			REP(i, l, r) for ( int x = p[i].suf.size() - 1; x >= 1; -- x ) 
			{
				-- sum; 
				while ( sum < L || i == j ) 
				{
					++ sum; val -= p[j].pre[y];
					++ y; if ( p[j].pre.size() == y ) { ++ j; y = 1; }
					if ( j > r ) goto Next ; 
				}
				ans += p[i].suf[x] * val;
			}
Next : ; 
			node t = {p[l].l, p[r].r, num / L};
			t.pre.push_back(0);	t.suf.push_back(0);
			sum = 0; bool flag = false;
			REP(i, l, r) for ( int x = 1; x < p[i].pre.size(); ++ x ) 
			{
				++ sum;
				if ( sum % L == 0 ) { t.pre.push_back(p[i].pre[x]); flag = true; }
				else if ( flag ) t.pre[t.pre.size() - 1] += p[i].pre[x];
			}
			sum = 0; flag = false;
			for ( int i = r; i >= l; -- i ) for ( int x = 1; x < p[i].suf.size(); ++ x ) 
			{
				++ sum;
				if ( sum % L == 0 ) { t.suf.push_back(p[i].suf[x]);	flag = true; }
				else if ( flag ) t.suf[t.suf.size() - 1] += p[i].suf[x];
			}
			q.push_back(t);
		}
		p = q;
	}
	printf("%lld\n", ans);
    return 0;
}
