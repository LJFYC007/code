/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2021年06月25日 星期五 11时29分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int n, N;
struct NODE { int Min, num, lazy; } Tree[maxn << 2];

inline void PushUp(int root)
{
	Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
	if ( Tree[lson].Min < Tree[rson].Min) Tree[root].num = Tree[lson].num;
	else if ( Tree[lson].Min > Tree[rson].Min ) Tree[root].num = Tree[rson].num;
	else Tree[root].num = Tree[lson].num + Tree[rson].num;
}

inline void PushTag(int root, int val) { Tree[root].Min += val; Tree[root].lazy += val; }

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Build(int root , int l, int r)
{
	Tree[root].Min = Tree[root].lazy = 0; Tree[root].num = r - l + 1;
	if ( l == r ) return ;
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

struct data
{
	struct node 
	{ 
		int l, r, h, val; 
		bool operator <(const node &a) const { return h < a.h; }
	} ;
	vector<node> a;

	inline void Insert(int x1, int x2, int y1, int y2)
	{
		a.push_back({x1, x2, y1, 1});
		a.push_back({x1, x2, y2 + 1, -1});
	}

	int p[maxn];

	inline int Solve()
	{
		sort(a.begin(), a.end()); 
		int lst = 0, ret = 0; Build(1, 0, N);
		for ( int l = 0, r; l < a.size(); l = r + 1 )
		{
			r = l; while ( r + 1 < a.size() && a[l].h == a[r + 1].h ) ++ r;
			if ( Tree[1].Min == 0 ) ret += (a[l].h - lst) * (N + 1 - Tree[1].num);
			else ret += (a[l].h - lst) * (N + 1);
			REP(i, l, r) Modify(1, 0, N, a[i].l, a[i].r, a[i].val);
			lst = a[l].h;
		}
		return ret;
	}
} A[5][5];

signed main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
	scanf("%lld%lld", &n, &N); N = (N / 5) + 10;
	REP(o, 1, n)
	{
		int x1, x2, y1, y2; scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
		int x = 0;
		REP(i, 0, 4) if ( y1 <= y2 ) 
		{
			if ( x1 + (5 - x) % 5 <= x2 ) 
			{
				int a = (x1 + (5 - x) % 5) % 5, b = y1 % 5;
				A[a][b].Insert((x1 + (5 - x) % 5 - a) / 5, (x2 - a) / 5, (y1 - b) / 5, (y2 - b) / 5);
			}
			++ y1; x = (x + x2 - x1 + 1) % 5;
		}
	}
	int ans = 0;
	REP(i, 0, 4) REP(j, 0, 4) ans += A[i][j].Solve();
	printf("%lld\n", ans);
    return 0;
}
