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

int k;

inline void Solve(vector<int> f, int val)
{
	if ( f.size() == 1 ) return ; 
	vector<int> a, b, c;

	for ( auto j : f ) 
	{
		if ( (j / val) % 3 == 0 ) a.push_back(j);
		if ( (j / val) % 3 == 1 ) b.push_back(j);
		if ( (j / val) % 3 == 2 ) c.push_back(j);
	}

	int k = f.size();

	for ( int i = 0; i < k / 3; ++ i ) 
	{
		for ( int j = 0; j < k / 3; ++ j ) 
			printf("%d %d %d\n", a[i], b[j], c[(i + j) % (k / 3)]);
	}

	Solve(a, val * 3);
	Solve(b, val * 3);
	Solve(c, val * 3);
}

bool vis[6010][6010];

int main()
{
	cin >> k;
	if ( k == 1 || k == 3 || (k % 3 == 0 && k % 9 == 0) ) 
	{
		vector<int> a;
		REP(i, 1, k) a.push_back(i);
		Solve(a, 1);
		return 0;
	}
	REP(i, 1, k) REP(j, i + 1, k) if ( !vis[i][j] )
		REP(o, j + 1, k) if ( !vis[i][o] && !vis[j][o] ) 
		{
			vis[i][j] = vis[i][o] = vis[j][o] = true;
			printf("%d %d %d\n", i, j, o);
			break ; 
		}

    return 0;
}
