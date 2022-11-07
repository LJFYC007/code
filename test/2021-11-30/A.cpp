#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int f[maxn], n;
bool vis[maxn];

int query(std::vector<int>);

inline bool Check(vector<int> a, int pos)
{
	if ( a.empty() ) return false;
	vector<int> b = a; b.push_back(pos);
	return query(a) == query(b);
}

inline void Solve(int x)
{
	vector<int> a; vis[x] = true;
	REP(i, 1, n) if ( !vis[i] ) a.push_back(i);
	if ( Check(a, x) )
	{
		int l = 0, r = a.size() - 1, pos;
		while ( l <= r ) 
		{
			int Mid = l + r >> 1;
			vector<int> b; REP(i, l, Mid) b.push_back(a[i]);
			if ( Check(b, x) ) { r = Mid - 1; pos = Mid; } 
			else l = Mid + 1;
		}

		Solve(a[pos]);
		Solve(x);
	}
	else
	{
		vector<int> Edge[maxn];
		REP(i, 2, n) if ( vis[i] ) Edge[f[i]].push_back(i);
		queue<int> Q; Q.push(1);
		vector<int> a; 
		while ( !Q.empty() ) 
		{
			int u = Q.front(); Q.pop(); a.push_back(u);
			for ( auto v : Edge[u] ) Q.push(v);
		}

		reverse(a.begin(), a.end());
		int l = 0, r = a.size() - 1, pos;
		while ( l <= r ) 
		{
			int Mid = l + r >> 1;
			vector<int> b; REP(i, l, Mid) b.push_back(a[i]);
			if ( Check(b, x) ) { r = Mid - 1; pos = Mid; } 
			else l = Mid + 1;
		}

		f[x] = a[pos];
	}
}

vector<int> solve(int N)
{
	vis[1] = true; n = N;
	REP(i, 2, n) if ( !vis[i] ) 
		Solve(i);
	vector<int> a; REP(i, 2, n) a.push_back(f[i]); return a;
}