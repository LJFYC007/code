/*
	Problem:	easiest.cpp
	Time:		2020-09-30 17:25
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e7 + 10;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, a[maxn], fa[maxn], rmost[maxn], siz[maxn];

int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

const int N = 1e9;
unsigned z;
unsigned x = 123456789, y = 362436069;
unsigned gen()
{
	unsigned t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z % N + 1;
}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (siz[x] > siz[y]) swap(x, y);
	siz[y] += siz[x];
	fa[x] = y;
	rmost[y] = max(rmost[x], rmost[y]);
}
int main()
{
	file("easiest");
	cin >> n >> q >> z;
	REP(i, 1, n) a[i] = gen();
	REP(i, 1, n) fa[i] = i, rmost[i] = i, siz[i] = 1;
	i64 Ans = 0;
	while (q--)
	{
		int l = gen() % n + 1, r = gen() % n + 1;
		if (l > r) swap(l, r);
		i64 ans = 0;
		int x = rmost[find(l)];
		while (1)
		{
			if (x > r) break;
			ans += a[x];
			a[x] = 0;
			if (x == n) break;
			uni(x, x + 1);
			x = rmost[find(x)];
		}
		Ans ^= ans;
	}
	cout << Ans << endl;
	return 0;
}
