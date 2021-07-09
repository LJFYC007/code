#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss
#define lson root << 1
#define rson root << 1 | 1
const int maxn = 50010;

struct node
{
	LL l, r, sum;
	bool flag; // if flag = 1 -> sqrt not change -> pass it
} Tree[maxn * 6];

LL n, a[maxn];

inline void push_up(LL root)
{
	Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
	Tree[root].flag = (Tree[lson].flag && Tree[rson].flag) ? true : false;
}

inline void Build(LL root, LL l, LL r)
{
	Tree[root].l = l; Tree[root].r = r;
	if ( l == r )
	{
		Tree[root].sum = a[l];
		Tree[root].flag = (a[l] == 0 || a[l] == 1 ) ? true : false; 
		return ;
	}
	LL Mid = l + r >> 1;
	Build(lson, l, Mid);
	Build(rson, Mid + 1, r);
	push_up(root);
}

inline void Update(LL root, LL l, LL r, LL L, LL R)
{
	if ( Tree[root].flag == true ) return ;
	//printf("%d %d %d %d ", l, r, Tree[root].sum, Tree[root].flag);
	if ( l == r ) 
	{
		Tree[root].sum = a[l];
		Tree[root].flag = (a[l] == 0 || a[l] == 1 ) ? true : false;
		return ;
	}
	LL Mid = l + r >> 1;
	if ( L <= Mid ) Update(lson, l, Mid, L, R);
	if ( R > Mid ) Update(rson, Mid + 1, r, L, R);
	push_up(root);
	//printf("%d %d %d %d\n", l, r, Tree[root].sum, Tree[root].flag);
}

inline LL query(LL root, LL l, LL r, LL L, LL R)
{
	//printf("%d %d %d %d %d\n", root, l, r, L, R);
	if ( L <= l && r <= R ) return Tree[root].sum;
	if ( l == r ) return Tree[l].sum;
	LL Mid = l + r >> 1, sum = 0;
	if ( L <= Mid ) sum += query(lson, l, Mid, L, R);
	if ( R > Mid ) sum += query(rson, Mid + 1, r, L, R);
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	Build(1, 1, n);
	//REP(i, 1, 7) printf("%d %d %d %d\n", Tree[i].l, Tree[i].r, Tree[i].sum, Tree[i].flag);
	REP(k, 1, n)
	{
		LL opt, l, r, c;
		scanf("%lld%lld%lld%lld", &opt, &l, &r, &c);
		if ( opt == 0 ) 
		{
			REP(i, l, r) a[i] = sqrt(a[i]);
			Update(1, 1, n, l, r);
			//REP(i, 1, 7) printf("%d %d %d %d\n", Tree[i].l, Tree[i].r, Tree[i].sum, Tree[i].flag);
			//return 0;
		}
		else if ( opt == 1 )
		{
			printf("%lld\n", query(1, 1, n, l, r));
		}
	}
	return 0;
}

