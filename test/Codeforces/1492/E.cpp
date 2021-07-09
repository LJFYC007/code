/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年02月24日 星期三 09时42分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2.5e5 + 10;

int n, m;
vector<int> a[maxn];

inline void Solve(int num)
{
	REP(i, 2, n)
	{
		vector<int> p; REP(j, 1, m) if ( a[i][j] != a[1][j] ) p.push_back(j);
		if ( p.size() > 2 + num ) return ;
		if ( p.size() <= 2 ) continue ; 
		if ( p.size() == 3 ) 
		{
			REP(j, 0, 2) 
			{ 
				int x = a[1][p[j]]; a[1][p[j]] = a[i][p[j]]; 
				Solve(num - 1); a[1][p[j]] = x;
			}
			return ;
		}
		else
		{
			REP(j, 0, 3) REP(k, j + 1, 3)
			{
				int x = a[1][p[j]], y = a[1][p[k]];
				a[1][p[j]] = a[i][p[j]]; a[1][p[k]] = a[i][p[k]];
				Solve(num - 2); a[1][p[j]] = x; a[1][p[k]] = y;
			}
			return ;
		}
	}
	puts("Yes");
	REP(i, 1, m) printf("%d ", a[1][i]); puts(""); exit(0);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { a[i].resize(m + 1); REP(j, 1, m) scanf("%d", &a[i][j]); }
	Solve(2); puts("No");
    return 0;
}
