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

int a[maxn + 5];

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
	int n = atoi(argv[1]);
	int type = atoi(argv[3]);
	int l = int(n * 0.25), r = int(n * 0.5);
	if (n == 250000)
	{
		l = int(n * 0.1);
		r = int(n * 0.9);
	}
	if (type == 1) l = 0, r = n;
	static int p[maxn + 5];
	memset(p, 0, sizeof p);
	REP(i, 0, r) p[i] = 1;
	shuffle(p, p + n);
	vector<int> vl, vr;
	REP(i, 0, n) if (p[i]) vl.pb(i); else vr.pb(i);
	vector<int> u, v;
	REP(i, l, r)
		if (rnd.next(l, r) > i) u.pb(i);
		else v.pb(i);
	static int pp[maxn + 5];
	REP(i, l, l + SZ(u)) pp[i] = 1;
	REP(i, l + SZ(u), r) pp[i] = 0;
	shuffle(pp + l, pp + r);
	REP(i, 0, l) a[i] = vl[i];
	REP(i, l, r)
		if (pp[i]) a[i] = vl[u.back()], u.pop_back();
		else a[i] = vl[v.back()], v.pop_back();
	REP(i, r, n)
		a[i] = vr[i - r];
	shuffle(a + r, a + n);
	printf("%d\n", n);
	REP(i, 0, n)
	{
		printf("%d", a[i] + 1);
		if (i < n - 1) printf(" ");
		else printf("\n");
	}
	int qn = atoi(argv[2]);
	printf("%d\n", qn);
	REP(i, 0, qn) 
	{
		printf("%d\n", rnd.next(0, n));
	}
	return 0;
}
