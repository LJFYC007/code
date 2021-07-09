#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long

const int maxn = 1e5 + 10;
const int N = 2e9;

int n, x[maxn], a[maxn], b[maxn], tot = 1, Root = 1, num;
struct node { int lson, rson, sum1, sum2, sum3, sum4, tag, num; } Tree[maxn << 5];

inline void PushTag(int root) { Tree[root].tag ^= 1; swap(Tree[root].sum1, Tree[root].sum2); swap(Tree[root].sum3, Tree[root].sum4); } 

inline void PushDown(int root)
{
	if ( !Tree[root].tag ) return ; Tree[root].tag = 0;
	if ( ls(root) ) PushTag(ls(root)); 
	if ( rs(root) ) PushTag(rs(root));
}

inline void PushUp(int root)
{
	Tree[root].sum1 = Tree[ls(root)].sum1 + Tree[rs(root)].sum1;
	Tree[root].sum2 = Tree[ls(root)].sum2 + Tree[rs(root)].sum2;
	Tree[root].sum3 = Tree[ls(root)].sum3 + Tree[rs(root)].sum3;
	Tree[root].sum4 = Tree[ls(root)].sum4 + Tree[rs(root)].sum4;
	Tree[root].num = Tree[ls(root)].num + Tree[rs(root)].num;
}

inline void Maintain(int root, int l, int r, int L, int R)
{
	if ( !root ) return ; 
	if ( L <= l && r <= R ) { PushTag(root); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Maintain(ls(root), l, Mid, L, R);
	if ( Mid < R ) Maintain(rs(root), Mid + 1, r, L, R);
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( !root ) return 0;
	if ( L <= l && r <= R ) return Tree[root].num;
	int Mid = l + r >> 1, ret = 0; PushDown(root);
	if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
	if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
	return ret;
}

inline void Modify(int &root, int l, int r, int pos, int a, int b, int op)
{
	if ( !root ) root = ++ tot;
	if ( l == r ) 
	{
		++ Tree[root].num;
		if ( op == 0 ) { Tree[root].sum2 += a; Tree[root].sum4 += b; }
		else { Tree[root].sum1 += a; Tree[root].sum3 += b; } 
		return ;
	}
	int Mid = l + r >> 1; PushDown(root);
	if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, a, b, op);
	else Modify(rs(root), Mid + 1, r, pos, a, b, op);
	PushUp(root);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) { scanf("%lld%lld%lld", &x[i], &a[i], &b[i]); x[i] %= (a[i] + b[i]); } 

	int num1 = 0, num2 = 0;
	REP(i, 1, n)
	{
		bool op1 = false, op2 = false;
		if ( b[i] > x[i] ) num1 += x[i] / a[i]; 
		if ( a[i] > x[i] ) num2 += x[i] / b[i];
		if ( a[i] <= x[i] && b[i] <= x[i] ) 
		{
			int val = x[i] / a[i] + x[i] / b[i];
			Maintain(Root, 1, N, N - val, N);
			int pos = Query(Root, 1, N, 1, N - val - 1);
			Modify(Root, 1, N, N - val, x[i] / a[i], x[i] / b[i], pos & 1);
		}

		int sum1 = num1 + Tree[1].sum2, sum2 = num2 + Tree[1].sum3; 
		if ( sum1 > sum2 ) op1 = true;
		sum1 = num1 + Tree[1].sum1; sum2 = num2 + Tree[1].sum4; 
		if ( sum1 < sum2 ) op2 = true;

		if ( op1 && op2 ) puts("First");
		else if ( !op1 && !op2 ) puts("Second");
		else if ( op1 && !op2 ) puts("Alice");
		else if ( !op1 && op2 ) puts("Bob");
	}
	return 0;
}
