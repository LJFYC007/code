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

const int maxn = 2e5 + 10;

int T, n, a[maxn];
bool op; vector<int> p;

inline void print(int x) 
{
	if ( op == 0 ) p.push_back(x);
	else p.push_back(n - x - 1);
}

inline void Solve()
{
	REP(i, 2, n) if ( a[i] == 1 ) 
	{
		if ( a[i + 1] == 1 ) 
		{
			a[i] = a[i + 1] = 0;
			print(i - 1); continue ; 
		}

		if ( a[i + 2] == 1 ) 
		{
			a[i] = a[i + 2] = 0;
			print(i); continue ; 
		}

		a[i] = 0; a[i + 2] = 1;
		print(i); print(i - 1);
	}		

	puts("YES");
	printf("%d\n", p.size());
	for ( auto it : p ) printf("%d ", it); puts("");
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
		int sum = 0; REP(i, 1, n) sum ^= a[i];
		if ( sum == 1 ) { puts("NO"); continue ; } 
		op = 0; p.clear();
		if ( a[n] == 0 ) 
		{
			reverse(a + 1, a + n + 1);
			op = 1; Solve();
		}
		else if ( a[1] == 0 ) Solve();
		else
		{
			for ( int i = 1, j; i <= n; i = j + 1 ) 
			{
				j = i;
				while ( j < n && a[j + 1] == a[i] ) ++ j;
				int num = j - i + 1;
				if ( a[i] == 1 ) 
				{
					if ( i == 1 && num % 2 == 0 )
					{
						if ( j == n ) { puts("NO"); goto Next; }
						while ( i <= j ) { print(i); i += 2; }
						break ; 
					}
					if ( j == n && num % 2 == 0 ) 
					{
						reverse(a + 1, a + n + 1);
					}
				}
				else
				{
				}
			}

			Solve();	
		}
		Next : ;
	}
    return 0;
}
