#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;
const double alpha = 0.7;

int n, k, a[maxn][3], K, tot, Rub[maxn], cnt;
double f[maxn], g[maxn], ans;
struct point
{
	int x, y; double val;
	point(int a = 0, int b = 0, double c = 0) { x = a; y = b; val = c; }
	bool operator < (const point &a) const { return K == 0 ? x < a.x : y < a.y; }
} p[maxn];
struct node { int size, lson, rson, Maxx, Maxy, Minx, Miny; point x; double Min; } Tree[maxn << 4];
queue<int> Q;

inline int NewNode() { return cnt > 0 ? Rub[cnt --] : ++ tot; }

inline void PushUp(int root)
{
	Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
	Tree[root].Min = Tree[root].x.val;
    Tree[root].Maxx = Tree[root].Minx = Tree[root].x.x;
    Tree[root].Maxy = Tree[root].Miny = Tree[root].x.y;
    if ( ls(root) )
    {
		Tree[root].Min = min(Tree[root].Min, Tree[ls(root)].Min);
        Tree[root].Maxx = max(Tree[root].Maxx, Tree[ls(root)].Maxx);
        Tree[root].Minx = min(Tree[root].Minx, Tree[ls(root)].Minx);
        Tree[root].Maxy = max(Tree[root].Maxy, Tree[ls(root)].Maxy);
        Tree[root].Miny = min(Tree[root].Miny, Tree[ls(root)].Miny);
    }
    if ( rs(root) )
    {
		Tree[root].Min = min(Tree[root].Min, Tree[rs(root)].Min);
        Tree[root].Maxx = max(Tree[root].Maxx, Tree[rs(root)].Maxx);
        Tree[root].Minx = min(Tree[root].Minx, Tree[rs(root)].Minx);
        Tree[root].Maxy = max(Tree[root].Maxy, Tree[rs(root)].Maxy);
        Tree[root].Miny = min(Tree[root].Miny, Tree[rs(root)].Miny);
    }
}

inline void Rebuild(int &root, int l, int r, int dim)
{
	if ( l > r ) { root = 0; return ; }
	int Mid = l + r >> 1; root = NewNode();
	K = dim; nth_element(p + l, p + Mid, p + r + 1);
	Tree[root].x = p[Mid];
	Rebuild(ls(root), l, Mid - 1, dim ^ 1); Rebuild(rs(root), Mid + 1, r, dim ^ 1);
	PushUp(root);
}

inline void Access(int root, int num)
{
	if ( ls(root) ) Access(ls(root), num);
	num += Tree[ls(root)].size + 1; p[num] = Tree[root].x; Rub[++ cnt] = root;
	if ( rs(root) ) Access(rs(root), num);
}

inline void Check(int &root, int dim)
{
	if ( Tree[root].size * alpha <= Tree[ls(root)].size || Tree[root].size * alpha <= Tree[rs(root)].size )
	{
		Access(root, 0); Rebuild(root, 1, Tree[root].size, dim);
	}
}

inline void Insert(int &root, point x, int dim)
{
	if ( !root )
	{
		root = NewNode(); ls(root) = rs(root) = 0; Tree[root].x = x;
		Tree[root].Maxx = Tree[root].Minx = x.x;
		Tree[root].Maxy = Tree[root].Miny = x.y;
		Tree[root].size = 1; Tree[root].Min = x.val;
		return ;
	}
	if ( (dim == 0 && x.x <= Tree[root].x.x) || (dim == 1 && x.y <= Tree[root].x.y) ) Insert(ls(root), x, dim ^ 1);
	else Insert(rs(root), x, dim ^ 1);
	PushUp(root); Check(root, dim);
}

#define sqr(x) (x) * (x)

inline int dis(point a, point b) { return sqr(b.x - a.x) + sqr(b.y - a.y); }

inline int dis2(point x, int root)
{
	bool flag1 = Tree[root].Minx <= x.x && x.x <= Tree[root].Maxx, flag2 = Tree[root].Miny <= x.y && x.y <= Tree[root].Maxy;
	if ( flag1 && flag2 ) return 0;
	if ( flag1 ) return (x.y >= Tree[root].Maxy ? x.y - Tree[root].Maxy : Tree[root].Miny - x.y);
	if ( flag2 ) return (x.x >= Tree[root].Maxx ? x.x - Tree[root].Maxx : Tree[root].Minx - x.x);
	return min(min(dis(x, point(Tree[root].Maxx, Tree[root].Maxy, 0)), dis(x, point(Tree[root].Maxx, Tree[root].Miny, 0))),
			   min(dis(x, point(Tree[root].Minx, Tree[root].Maxy, 0)), dis(x, point(Tree[root].Minx, Tree[root].Miny, 0))));
}

signed main()
{
	freopen("inv.in", "r", stdin);
	freopen("inv.out", "w", stdout);
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) REP(j, 1, k) scanf("%lld", &a[i][j]);
	if ( k == 1 )
	{
		REP(i, 1, n) g[i] = INF;
		REP(i, 1, n)
		{
			f[i] = INF;
			REP(j, 0, a[i][1] - 1) f[i] = f[i] < (g[j] + (a[i][1] - j) * (a[i][1] - j)) ? f[i] : (g[j] + (a[i][1] - j) * (a[i][1] - j));
			g[a[i][1]] = f[i];
			printf("%.4lf\n", sqrt(f[i]));
		}
		return 0;
	}
	int Root = 1; tot = 1;
	Insert(Root, point(0, 0, 0), 0);
	REP(i, 1, n)
	{
		point x = point(a[i][1], a[i][2], 0);
		ans = Tree[Root].x.val + dis(x, Tree[Root].x);
		while ( !Q.empty() ) Q.pop(); Q.push(Root);
		while ( !Q.empty() )
		{
			int root = Q.front(); Q.pop();
			if ( ls(root) && dis2(x, ls(root)) + Tree[ls(root)].Min < ans )
			{
				Q.push(ls(root));
				ans = min(ans, Tree[ls(root)].x.val + dis(x, Tree[ls(root)].x));
			}
			if ( rs(root) && dis2(x, rs(root)) + Tree[rs(root)].Min < ans )
			{
				Q.push(rs(root));
				ans = min(ans, Tree[rs(root)].x.val + dis(x, Tree[rs(root)].x));
			}
		}
		Insert(Root, point(a[i][1], a[i][2], ans), 0);
		printf("%.4lf\n", sqrt(ans));
	}
	return 0;
}
