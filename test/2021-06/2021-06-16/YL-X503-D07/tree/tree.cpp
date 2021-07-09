/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2021年06月16日 星期三 08时36分33秒
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

int n, m, k, h[maxn], a[maxn];
struct node { int sum, ans, lazy, Min, Max, len; } Tree[maxn << 2];

inline int calc(int n) { return n * (n + 1) / 2; } 

inline void PushUp(int root)
{
	Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
	Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
	Tree[root].ans = Tree[lson].ans + Tree[rson].ans + Tree[lson].sum * Tree[rson].len;
}

inline void PushTag(int root, int val)
{
	Tree[root].sum = val * k * Tree[root].len; 
	Tree[root].ans = val * k * calc(Tree[root].len);
	Tree[root].Min = Tree[root].Max = val * k;
	Tree[root].lazy = val;	
}

inline void PushDown(int root)
{
	if ( Tree[root].lazy == 0 ) return ;
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
	Tree[root].len = r - l + 1;
	if ( l == r ) { Tree[root].sum = Tree[root].ans = Tree[root].Min = Tree[root].Max = a[l]; return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r); 
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].sum; 
	int ret = 0, Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
	return ret;
}

inline int Query2(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].ans + Tree[root].sum * (R - r); 
	int ret = 0, Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) ret += Query2(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query2(rson, Mid + 1, r, L, R);
	return ret;
}

inline int find(int root, int l, int r, int L, int R)
{
	if ( Tree[root].Min >= -k && Tree[root].Max <= k ) return n;
	if ( l == r ) return l;
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) { int x = find(lson, l, Mid, L, R); if ( x != n ) return x; } 
	if ( Mid < R ) return find(rson, Mid + 1, r, L, R);
	return n;
}

inline void Maintain(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Maintain(lson, l, Mid, L, R, val);
	if ( Mid < R ) Maintain(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int pos, int val)
{
	if ( l == r ) { Tree[root].sum += val; Tree[root].ans += val; Tree[root].Min += val; Tree[root].Max += val; return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
	else Modify(rson, Mid + 1, r, pos, val);
	PushUp(root);
}

inline int get1(int x) { return Query(1, 1, n, 1, x); }
inline int get2(int x) { return Query(1, 1, n, x, x); }

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &m, &k);
	REP(i, 1, n) { scanf("%lld", &h[i]); a[i] = h[i] - h[i - 1]; }
	++ n; Build(1, 1, n);
	while ( m -- ) 
	{
		int op, l, r, c; scanf("%lld%lld%lld", &op, &l, &r);
		if ( op == 1 ) 
		{
			int sum = (l > 1 ? get1(l - 1) : 0) * (r - l + 1) + Query2(1, 1, n, l, r);
			printf("%lld\n", sum);
		}
		if ( op == 2 ) { scanf("%lld", &c); Modify(1, 1, n, l, c); Modify(1, 1, n, r + 1, -c); }
		if ( op == 3 ) 
		{
			for ( int i = find(1, 1, n, l + 1, n); i <= r; i = find(1, 1, n, i + 1, n) ) 
			{
				if ( get2(i) > k ) 
				{
					int pos = i, L = i + 1, R = min(r, find(1, 1, n, i + 1, n) - 1);
					while ( L <= R ) 
					{
						int Mid = L + R >> 1;
						if ( get2(i) - k >= k * (Mid - i) - Query(1, 1, n, i + 1, Mid) ) { pos = Mid; L = Mid + 1; }
						else R = Mid - 1;
					}
					if ( pos > i ) 
					{
						int x = k * (pos - i) - Query(1, 1, n, i + 1, pos);
						Modify(1, 1, n, i, -x); Maintain(1, 1, n, i + 1, pos, 1);
					}
					int x = get2(i) - k; Modify(1, 1, n, i, -x); Modify(1, 1, n, pos + 1, x);
				}
				if ( get2(i) < -k ) 
				{
					int pos = i, L = l + 1, R = i - 1;
					while ( L <= R ) 
					{
						int Mid = L + R >> 1;
						if ( -k - get2(i) >= k * (i - Mid) + Query(1, 1, n, Mid, i - 1) ) { pos = Mid; R = Mid - 1; }
						else L = Mid + 1;
					}
					if ( pos < i ) 
					{
						int x = k * (i - pos) + Query(1, 1, n, pos, i - 1);
						Modify(1, 1, n, i, x); Maintain(1, 1, n, pos, i - 1, -1);
					}
					int x = -k - get2(i); Modify(1, 1, n, i, x); Modify(1, 1, n, pos - 1, -x);
				}
			}
		}
	}
    return 0;
 }
