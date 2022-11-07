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
const int INF = 1e8;

vector<int> ans, a, b; int pos;

void Solve(int l, int r)
{
	if ( l > r ) return ;
	int Mid = l + r >> 1, val = query(Mid, Mid);
	if ( !val ) { ans.push_back(Mid); val = 1; }
	else pos = Mid;
	Solve(l, Mid - val); Solve(Mid + val, r);
}

std::pair<std::vector<int>,std::vector<int> > solve()
{
	Solve(-INF, INF);
	for ( auto it : ans ) 
	{
		if ( query(it, pos) == 0 ) a.push_back(it);
		if ( query(pos, it) == 0 ) b.push_back(it);
	}
	return pair<vector<int>, vetor<int> >(a, b);
}
