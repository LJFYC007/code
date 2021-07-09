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

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int m = n - 1;
	int K = atoi(argv[2]);
	vector<pair<pair<int, int>, int> > ed;
	REP(i, 1, n)
		ed.pb(mp(mp(rnd.next(0, i - 1), i), rnd.next(1, 1000)));
	static int p[maxn + 5];
	REP(i, 0, n) p[i] = i + 1;
//	shuffle(p, p + n);
//	shuffle(ALL(ed));
	printf("%d %d %d\n", n, m, K);
	REP(i, 0, n)
	{
		printf("%d", rnd.next(1, 10000));
		if (i < n - 1) printf(" ");
		else printf("\n");
	}
	for (auto u : ed)
	{
		printf("%d %d %d\n", p[u.x.x], p[u.x.y], u.y);
	}
	return 0;
}
