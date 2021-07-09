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

const int maxn = 1000100;

bool vis[maxn + 5];

int main()
{
	registerValidation();
	int n = inf.readInt(1, 1000000, "n");
	inf.readEoln();
	REP(i, 0, n)
	{
		int ai = inf.readInt(1, n, "ai");
		if (i < n - 1) inf.readSpace();
		else inf.readEoln();
		ensuref(!vis[ai], "Input must be a permutation.");
	}
	int q = inf.readInt(1, 20, "q");
	inf.readEoln();
	REP(i, 0, q) inf.readInt(0, 1000000, "K"), inf.readEoln();
	inf.readEof();
	return 0;
}
