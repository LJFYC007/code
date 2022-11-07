/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5010;

int n, b[maxn];
pii a[maxn];
vector<int> ans;

inline bool chk(pii a, pii b)
{
	int x = a.x * b.x + a.y * b.y;
	return x > 0;
}

pii operator - (pii a, pii b ){ return pii(a.x - b.x, a.y - b.y); }

inline bool Check(int pos)
{
	if ( pos < 0 || pos + 2 > ans.size() ) return true;
	return chk(a[b[pos + 1]] - a[b[pos]], a[b[pos + 1]] - a[b[pos + 2]]);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld%lld", &a[i].x, &a[i].y);
	ans.push_back(1); ans.push_back(2);
	REP(i, 3, n)
	{
		if ( chk(a[ans[i - 2]] - a[i], a[ans[i - 2]] - a[ans[i - 3]]) )
		{ ans.push_back(i); continue ; }
		REP(j, 0, i - 2) b[j] = ans[j];
		REP(j, 0, i - 2)
		{
			b[j] = i; b[i - 1] = ans[j];
			if ( !Check(j - 2) || !Check(j - 1) || !Check(j) || !Check(i - 3) ) { b[j] = ans[j]; continue ; }
			ans.push_back(ans[j]); ans[j] = i; break ;
		}
	}
	for ( int i = 0; i < ans.size(); ++ i ) printf("%lld ", ans[i]);
	puts("");
    return 0;
}
