/***************************************************************
	File name: AGC024F.cpp
	Author: ljfcnyali
	Create time: 2021年06月21日 星期一 16时29分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1 << 21;

int n, k, f[maxn][21], a[maxn][21], b[maxn][21];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &k);
	REP(i, 0, n) 
	{
		getchar();
		REP(j, 0, (1 << i) - 1)
		{
			char c = getchar();
			if ( c == '1' ) f[j + (1 << i)][i] = 1;
		}
	}
	REP(i, 0, (1 << n + 1) - 1) REP(j, 1, 20)
		for ( int k = j - 1; k >= 1; -- k ) if ( ((i >> j - 1) & 1) != ((i >> k - 1) & 1) )
		{
			int val = ((i >> j) << k);
			REP(o, 0, k - 1) val |= ((i >> o) & 1) << o;
			a[i][j] = k; b[i][j] = val; break ; 
		}

	for ( int i = (1 << n + 1) - 1; i >= 0; -- i ) for ( int j = 20; j >= 1; -- j ) if ( f[i][j] ) 
	{
		f[i >> j][0] += f[i][j]; f[i][j - 1] += f[i][j];
		if ( a[i][j] ) f[b[i][j]][a[i][j] - 1] += f[i][j];
	}

	for ( int j = 20; j >= 1; -- j ) REP(i, 0, (1 << j) - 1) if ( f[i + (1 << j)][0] >= k )
	{
		vector<int> p; REP(o, 1, j) { p.push_back(i % 2); i /= 2; } 
		reverse(p.begin(), p.end()); for ( auto it : p ) printf("%d", it); puts("");
		return 0;
	}
    return 0;
}
