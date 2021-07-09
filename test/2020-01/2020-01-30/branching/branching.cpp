#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const double eps = 1e-8;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, size[maxn];
int pa[maxn], dis2[maxn], dis1[maxn], hv[maxn], p[maxn], tot;
vector<int> sum1[maxn], sum2[maxn], sum3[maxn], sum4[maxn];
vector<int> a[maxn];
bool use[maxn];
double f[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Get_Root(int u)
{
	size[u] = 1; hv[u] = -1; use[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( use[v] ) continue ;
        Get_Root(v); size[u] += size[v];
		if ( hv[u] == -1 || size[v] > size[hv[u]] ) hv[u] = v;
    }
	use[u] = false;
}

inline void Get_Dis(int u, int t)
{
	use[u] = true;
	if ( dis2[u] >= 0 )
	{
		while ( sum3[t].size() <= dis2[u] ) { sum3[t].push_back(0); sum4[t].push_back(0); }
		++ sum3[t][dis2[u]]; sum4[t][dis2[u]] += dis2[u];
	}
	dis2[u] = dis1[u]; a[u].push_back(dis1[u]);
	while ( sum1[t].size() <= dis1[u] ) { sum1[t].push_back(0); sum2[t].push_back(0); }
	++ sum1[t][dis1[u]]; sum2[t][dis1[u]] += dis1[u];
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( use[v] ) continue ;
		dis1[v] = dis1[u] + 1; Get_Dis(v, t);
    }
	use[u] = false;
}

inline void Solve(int last, int u)
{
	Get_Root(u); int x = u; while ( hv[x] > 0 && size[hv[x]] > size[u] / 2 ) x = hv[x];
	u = x; pa[u] = last;
	sum1[u].clear(); sum2[u].clear(); sum3[u].clear(); sum4[u].clear();
	dis1[u] = 0; Get_Dis(u, u);
	REP(i, 1, sum1[u].size() - 1) { sum1[u][i] += sum1[u][i - 1]; sum2[u][i] += sum2[u][i - 1] ;}
	REP(i, 1, sum3[u].size() - 1) { sum3[u][i] += sum3[u][i - 1]; sum4[u][i] += sum4[u][i - 1] ;}
	use[u] = true;
	for ( int i = Begin[u]; i; i = Next[i] ) if ( !use[To[i]] ) Solve(u, To[i]);
}

inline void Solve1(int x, int dis1, int dis2, int &cnt, int &sum)
{
	if ( dis1 < 0 ) return ;
	dis1 = min(dis1, LL(sum1[x].size()) - 1);
	cnt += sum1[x][dis1]; sum += sum2[x][dis1];
	sum += sum1[x][dis1] * dis2;
}

inline void Solve2(int x, int dis1, int dis2, int &cnt, int &sum)
{
	if ( dis1 < 0 ) return ;
	dis1 = min(dis1, LL(sum3[x].size()) - 1);
	cnt -= sum3[x][dis1]; sum -= sum4[x][dis1];
	sum -= sum3[x][dis1] * dis2;
}

inline void Query(int x, int d, int &cnt, int &sum)
{
	tot = 1; p[1] = x;
	while ( pa[p[tot]] ) { p[tot + 1] = pa[p[tot]]; ++ tot; }
	cnt = sum = 0;
	REP(i, 1, tot)
	{
		int u = a[x][tot - i];
		Solve1(p[i], d - u, u, cnt, sum);
		if ( i > 1 ) Solve2(p[i - 1], d - u, u, cnt, sum);
	}
}

inline int Solve3(int x, int y)
{
	int disx = a[x].size() - 1, disy = a[y].size() - 1;
	if ( disx < disy ) { swap(x, y); swap(disx, disy); }
	int X = x, Y = y;
	while ( disx > disy ) { -- disx; X = pa[X]; }
	while ( X != Y ) { -- disx; X = pa[X]; Y = pa[Y]; }
	return a[x][disx] + a[y][disx];
}

signed main()
{
	freopen("branching.in", "r", stdin);
	freopen("branching.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
	REP(i, 1, n) dis2[i] = -1;
	Solve(0, 1);
	REP(i, 1, n)
	{
		int L = 0, R = n, sum1 = 0, sum2 = 0;
		while ( L <= R )
		{
			int Mid = L + R >> 1;
			Query(i, Mid, sum1, sum2);
			int sum = sum1 * Mid - sum2;
			if ( sum <= n ) { L = Mid + 1; f[i] = Mid + (n - sum) * 1.0 / sum1; }
			else R = Mid - 1;
		}
	}
	REP(i, 1, m)
	{
		int x, y; scanf("%lld%lld", &x, &y);
		printf("%.7lf\n", min(1.0 * Solve3(x, y), f[y]));
	}
	return 0;
}
