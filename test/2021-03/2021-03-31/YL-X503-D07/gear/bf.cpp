#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define pdd pair<double, double>
#define x first
#define y second

const int maxn = 1e5 + 10;
const double pi = acos(-1);

int n, m, Begin[maxn], Next[maxn], To[maxn], e, fa[maxn], dis[maxn];
pdd a[maxn];

pdd operator + (pdd a, pdd b) { return pdd(a.x + b.x, a.y + b.y); } 
pdd operator - (pdd a, pdd b) { return pdd(a.x - b.x, a.y - b.y); } 
inline double len(pdd a) { return sqrt(a.x * a.x + a.y * a.y); }
inline pdd change(pdd a, double theta) { return pdd(a.x * cos(theta) - a.y * sin(theta), a.x * sin(theta) + a.y * cos(theta)); }

inline pdd Merge(pdd a, pdd b, pdd c)
{
	double theta = atan2(c.y, c.x) + pi;
	return a + change(b, theta);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, double theta)
{
	a[u] = change(a[u], theta);
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i], theta);
}

inline pdd Get(int x)
{
	if ( x == 1 ) return pdd(-1, 0);
	return Get(fa[x]) + a[x];
//	return Merge(Get(fa[x]), a[x], a[fa[x]]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("gear.in", "r", stdin);
	freopen("gear1.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 2, n) { scanf("%d", &fa[i]); add(fa[i], i); }
	REP(i, 1, n) a[i] = pdd(-1, 0);
	while ( m -- ) 
	{
		int op, x, y; scanf("%d%d%d", &op, &x, &y);
		if ( op == 1 ) 
		{
			double theta = y / 180.0 * pi;
			// a[x] = change(a[x], theta);
			DFS(x, theta);
		}
		else 
		{
			pdd a1 = Get(x), a2 = Get(y);
			// cout << a1.x << " " << a1.y << endl;
			// cout << a2.x << " " << a2.y << endl;
			printf("%.6lf\n", len(Get(x) - Get(y)));
		}

// 		REP(i, 1, n) { pdd t = Get(i); cout << t.x << " " << t.y << endl; } 
	}
	return 0;
}
