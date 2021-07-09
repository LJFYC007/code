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

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	const int al = 500;
	const int maxbl = 1010;
	int bl = atoi(argv[2]);
	int q = atoi(argv[3]);
	double skew = atof(argv[4]);
	printf("%d\n", n);
	REP(i, 0, n)
	{
		static char a[al + 5];
		REP(j, 0, al) a[j] = rnd.wnext('a', 'z', -skew);
		a[al] = 0;
		printf("%s\n", a);
	}
	static char b[maxbl + 5];
	REP(j, 0, bl) b[j] = rnd.wnext('a', 'z', skew);
	b[bl] = 0;
	if (bl == 1) b[0] = 'y';
	printf("%s\n", b);
	printf("%d\n", q);
	REP(i, 0, q)
	{
		int x = rnd.wnext(1, bl, -1);
		int y = rnd.wnext(x, bl, 1);
		printf("%d %d %d\n", rnd.wnext(1, 1 << n, 1), x, y);
	}
	return 0;
}
