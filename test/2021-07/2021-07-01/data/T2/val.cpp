#ifdef __WIN32
#define CR_MUST_IN_EOL
#endif

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wshadow"
#include "testlib.h"
#pragma GCC diagnostic pop

#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 150;

int d[maxn + 5];
vector<int> adj[maxn + 5];

int main()
{
	registerValidation();
	int n = inf.readInt(1, 150, "n");
	inf.readSpace();
	int m = inf.readInt(1, 500, "m");
	inf.readSpace();
	inf.readInt(1, 2, "K");
	inf.readEoln();
	REP(i, 0, n)
	{
		inf.readInt(1, 10000, "a_i");
		if (i < n - 1) inf.readSpace();
		else inf.readEoln();
	}
	REP(i, 0, m)
	{
		int x = inf.readInt(1, n, "x");
		inf.readSpace();
		int y = inf.readInt(1, n, "y");
		inf.readSpace();
		--x, --y;
		adj[x].pb(y);
		++d[y];
		inf.readInt(1, 1000, "z");
		inf.readEoln();
	}
	queue<int> q;
	REP(i, 0, n) if (!d[i]) q.push(i);
	while (!q.empty())
	{
		int x = q.front(); q.pop();
		for (auto y : adj[x]) if (!--d[y]) q.push(y);
	}
	REP(i, 0, n)
	{
		ensuref(!d[i], "Graph must be acyclic.");
	}
	inf.readEof();
	return 0;
}
