/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 09时20分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e9;

int a, b, c, A, B, C;
vector<int> x, y, z;
bool flag = false;

inline vector<int> Get(int n)
{
	vector<int> p;
	while ( n )
	{
		int m = sqrt(n); p.push_back(m);
		n -= m * m;
	}
	return p;
}

inline void Check()
{
	for ( auto it : x ) A -= it * it;
	for ( auto it : y ) B -= it * it;
	for ( int i = 0; i < x.size(); ++ i ) C -= x[i] * y[i];
	// printf("%lld %lld %lld\n", A, B, C);
}

namespace Subtask1
{
	inline void DFS2(int n, int m)
	{
		if ( !n ) 
		{
			if ( !m ) 
			{
				if ( flag ) swap(x, y);
				printf("%lld\n", (int)x.size());
				for ( auto it : x ) printf("%lld ", it); puts("");
				for ( auto it : y ) printf("%lld ", it); puts("");
				Check();
				exit(0);
			}
			return ;
		}

		int t = 0; if ( y.size() >= x.size() ) t = 1;
		int val = y.size() + 1 < x.size() ? x[y.size()] : 0;
		for ( int i = t; i * i <= n; ++ i ) 
		{	
			y.push_back(i); DFS2(n - i * i, m - val * i); y.pop_back();
			y.push_back(-i); DFS2(n - i * i, m + val * i); y.pop_back();
		}
	}

	inline void DFS1(int n)
	{
		if ( !n ) { DFS2(b, c); return ; } 
		for ( int i = 1; i * i <= n; ++ i ) 
		{
			x.push_back(i); DFS1(n - i * i); x.pop_back();
			x.push_back(-i); DFS1(n - i * i); x.pop_back();
		}
	}

	inline int main()
	{
		DFS1(a);
		puts("-1");
		return 0;
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &a, &b, &c);
	if ( a < 0 || b < 0 || a + b < c + c ) { puts("-1"); return 0; } 
	A = a; B = b; C = c;
	if ( a > b ) { swap(a, b); flag = true; } 	

	if ( a <= 10 && b <= 10 ) return Subtask1 :: main();
	x = Get(a); y = x;
	for ( int i = y.size() - 1; i >= 0; -- i ) 
	{
		int t = min((c - a) / y[i], INF);
		y[i] += t; a += t * x[i];
	}
	if ( a != c ) { puts("-1"); return 0; } 
	z = Get(b - c);
	for ( auto it : z ) { x.push_back(0); y.push_back(it); }
	if ( flag ) swap(x, y);
	printf("%lld\n", (int)x.size());
	for ( auto it : x ) printf("%lld ", it); puts("");
	for ( auto it : y ) printf("%lld ", it); puts("");

	Check();
    return 0;
}
