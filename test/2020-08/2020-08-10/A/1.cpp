/*
	Problem:	A.cpp
	Time:		2020-08-10 16:16
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10, maxm = maxn * maxn;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, r, d, m;

struct Vector
{
	int x, y;
	Vector() {}
	Vector(int x, int y) : x(x), y(y) {}
	inline Vector operator + (Vector B) {return Vector(x + B.x, y + B.y);}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline int operator * (Vector B) {return x * B.y - y * B.x;}
}p[maxn];
inline int sqr(int x) {return x * x;}
inline int dist2(Vector i, Vector j) {return sqr(i.x - j.x) + sqr(i.y - j.y);}
inline int dist2(int i, int j) {return dist2(p[i], p[j]);}

int id[maxn];
inline bool cmp(int i, int j)
{
	if (!i) return 1;
	if (!j) return 0;
	return p[i] * p[j] > 0;
}
bool ins[maxn];

bool vis[maxn];
int mat[maxn];

bool match(int x)
{
	vis[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
		if (!mat[to[i]] || (!vis[mat[to[i]]] && match(mat[to[i]])))
		{
			mat[x] = to[i];
			mat[to[i]] = x;
			return 1;			
		}
	return 0;
}
void print(int x)
{
	for (int i = bg[x]; i; i = ne[i])
		if (to[i] == mat[x])
		{
			vis[to[i]] = 1;
			vis[x] = 1;
			printf("%d %d\n", x, to[i]);
			return;
		}
		else if (!vis[to[i]]) print(mat[to[i]]);
}
int main()
{
	file("A");
	cin >> n >> r >> d;
	r *= r;d *= d;
	REP(i, 1, n) p[i].x = read<int>(), p[i].y = read<int>();
	REP(i, 1, n) if (dist2(1, i) <= r) ins[i] = 1;
	REP(i, 1, n) if (!ins[i])
	{
		m = 0;
		id[0] = 0;
		REP(j, 1, n) if (ins[j] && dist2(i, j) <= d)
		{
			id[++m] = j;
			p[j] = p[j] - p[i];
		}
		p[0] = p[i] - p[1];
		sort(id, id + m + 1, cmp);
		REP(j, 1, m)
		{
            printf("%d ", id[j]);
			add(i, id[j]);
			p[id[j]] = p[id[j]] + p[i];
		}
        puts("");
	}
//	REP(x, 1, n) for (int i = bg[x]; i; i = ne[i]) printf("%d %d\n", x, to[i]);
	int ans = 0;
	REP(i, 1, n) if (bg[i] && !mat[i])
	{
		REP(j, 1, n) vis[j] = 0;
		if (match(i)) ans++;
	}
	cout << ans * 2 << endl;
	REP(i, 1, n) vis[i] = 0;
	REP(i, 1, n) if (!ins[i] && mat[i] && !vis[i]) print(i);
	return 0;
}
