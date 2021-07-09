#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )

const int maxn = 510;

struct node
{
	int u, v;
	double w;
} a[maxn * maxn];

int num, s, p, x[maxn], y[maxn], f[maxn];
double ans[maxn];

inline double dis(int u, int v)
{
	return sqrt((x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v]));
}

inline int cmp(node a, node b)
{
	return a.w < b.w;
}

inline int find(int x)
{
	return f[x] == x ? x : f[x] = find(f[x]);
}

int main()
{
	scanf("%d%d", &s, &p);
	REP(i, 1, p)
	{
		scanf("%d%d", &x[i], &y[i]);
		REP(j, 1, i - 1)
		{
			a[++ num].u = i;
			a[num].v = j;
			a[num].w = dis(i, j);
// 			printf("%d %d %.2lf\n", a[num].u, a[num].v, a[num].w);
		}
	}
	sort ( a + 1, a + num + 1, cmp ) ;
	int cnt = 0;
	REP(i, 1, p) f[i] = i;
	REP(i, 1, num)
	{
		int fx = find(a[i].u), fy = find(a[i].v);
		if ( fx != fy )
		{
			ans[++ cnt] = a[i].w;
			f[fx] = fy;
		}
	}
	sort ( ans + 1, ans + cnt + 1 );
	//REP(i, 1, cnt) printf("%.2lf ", ans[i]);
	printf("%.2lf\n", ans[cnt - s + 1]);
	return 0;
}
