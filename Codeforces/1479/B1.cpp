/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans;
vector<int> t1, t2, p;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i,1 , n) scanf("%d", &a[i]);
	int lst = 0;
	for ( int l = 1, r; l <= n ; l = r + 1 )
	{
		r = l;
		while ( a[r + 1] == a[r] ) ++ r;
		if ( l == r ) { p.push_back(a[l]); continue ; }
		if ( a[l] != lst ) { ans += p.size() + 2; lst = a[l]; p.clear(); continue ; }
		bool flag1 = false, flag2 = false;
		for ( int i = 1; i + 1 < p.size(); ++ i )
			if ( p[i] != a[l] && (p[i - 1] != a[l] || p[i + 1] != a[l]) ) flag1 = true;
			else flag2 = true;
		if ( flag2 == false )
		{
			if ( p.size() == 1 ) ans += 2;
			else ans += p.size() + 2;
		}
		else
		{
			if ( !flag1 ) ans += p.size() + 1;
			else ans += p.size() + 2;
		}
		p.clear(); lst = a[l];
	}
	if ( p.size() ) ans += p.size();
	printf("%d\n", ans);
    return 0;
}
