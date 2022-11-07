#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, k, num, x, y;
vector<int> a[maxn];

inline bool Check(int x, int y)
{
	int pos = lower_bound(a[x].begin(), a[x].end(), y) - a[x].begin();
	if ( a[x][pos] == y ) return true;
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &k);
	REP(i, 1, k)
	{
		scanf("%d%d", &x, &y);
		a[x].push_back(y);
	}
	REP(i, 1, n) sort(a[i].begin(), a[i].end());
	x = y = 1;
	while ( n >= 3 && m >= 3 )
	{
		++ x; ++ y;
		n -= 2; m -= 2;
	}
	int sum1 = 0, sum2 = 0, pos;
	if ( n == 1 && m == 1 ) pos = 1, pos = 1;
	else if ( n == 1 ) y += m - 1, pos = 3;
	else if ( m == 1 ) x += n - 1, pos = 2;
	else ++ x, pos = 4;
	-- n; -- m;
	cerr << n << " " << m << endl;
	while ( num < k )
	{
		cerr << n << " " << m << endl;
		cerr << x << " " << y << " " << pos << endl;
		if ( !Check(x, y) ) { puts("No"); return 0; }
		++ num;
		if ( pos == 4 )
		{
			if ( n <= 1 ) { ++ x; ++ n; pos = 3; continue ; }
			else {
				++ sum1; ++ x;
				if ( sum1 + 1 == n )
				{
					++ n; sum1 = 0;
					pos = 3;
				}
				continue ;
			}
		}
		if ( pos == 3 )
		{
			if ( m <= 1 ) { ++ y; ++ m; pos = 2; continue ; }
			else {
				++ sum2; ++ y;
				if ( sum2 + 1 == m )
				{
					++ m; sum2 = 0;
					pos = 2;
				}
				continue ;
			}
		}
		if ( pos == 2 )
		{
			if ( n <= 1 ) { -- x; pos = 1; ++ n; continue ; }
			else
			{
				++ sum1; -- x;
				if ( sum1 + 1 == n )
				{
					++ n; sum1 = 0;
					pos = 1;
				}
				continue ;
			}
		}
		if ( pos == 1 )
		{
			if ( m <= 1 ) { -- y; ++ m; pos = 4; continue ;}
			else
			{
				++ sum2; -- y;
				if ( sum2 + 1 == m ) { ++ m; sum2 = 0; pos = 4; }
				continue ;
			}
		}
	}
	puts("Yes");
	return 0;
}
