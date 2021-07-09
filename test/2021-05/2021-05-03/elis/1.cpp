#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;

int n, t, a, b, c;
vector<pii> ans;

inline bool pd(int a, int b)
{
	int x = 1, y = 1, val = t;
	for ( auto it : ans ) 
	{
		x += it.first; y += it.second;
		val -= abs(a - x) + abs(b - y);
	}
	return val >= 0;
}

inline bool Check()
{
	if ( !pd(a, b) ) return false;
	if ( !pd(a + c - 1, b) ) return false;
	if ( !pd(a, b + c - 1) ) return false;
	if ( !pd(a + c - 1, b + c - 1) ) return false;
	return true;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("elis.in", "r", stdin);
	freopen("elis.out", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld%lld", &n, &t, &a, &b, &c);
	if ( c == 1 ) 
	{
		int x = 1, y = 1;
		while ( x < a ) { ans.push_back(pii(1, 0)); ++ x; }
		while ( y < b ) { ans.push_back(pii(0, 1)); ++ y; }
		while ( x < n ) { ans.push_back(pii(1, 0)); ++ x; }
		while ( y < n ) { ans.push_back(pii(0, 1)); ++ y; } 
	}
	else if ( a == 1 && b == 1 ) 
	{
		int x = 1, op = 0;
		while ( x < n )
		{
			if ( !op ) { ans.push_back(pii(1, 0)); ans.push_back(pii(0, 1)); }
			else { ans.push_back(pii(0, 1)); ans.push_back(pii(1, 0)); } 
			op ^= 1; ++ x;
		}
	}
	else
	{
		int x = 1, y = 1;
		while ( x < a ) { ans.push_back(pii(1, 0)); ++ x; }
		while ( y < b ) { ans.push_back(pii(0, 1)); ++ y; }
		int op = 0;
		REP(i, 1, c - 1)
		{
			if ( !op ) { ans.push_back(pii(1, 0)); ans.push_back(pii(0, 1)); }
			else { ans.push_back(pii(0, 1)); ans.push_back(pii(1, 0)); } 
			op ^= 1; ++ x; ++ y;
		}
		while ( x < n ) { ans.push_back(pii(1, 0)); ++ x; }
		while ( y < n ) { ans.push_back(pii(0, 1)); ++ y; } 
	}
	if ( !Check() ) puts("Again");
	else { for ( auto it : ans ) if ( it.first == 0 ) putchar('R'); else putchar('U'); puts(""); } 
	return 0;
}
