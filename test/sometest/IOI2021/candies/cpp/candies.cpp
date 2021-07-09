/***************************************************************
	File name: candies.cpp
	Author: ljfcnyali
	Create time: 2021年06月25日 星期五 08时53分50秒
***************************************************************/
#include<bits/stdc++.h>
#include "candies.h"

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<LL, LL>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const LL maxn = 2e5 + 10;
const LL INF = 1e18;

LL n, q, Max, Min, sum, lim;
vector<pii> a[maxn];
struct node { LL Max, Min, lazy; } Tree[maxn << 2];

inline void PushTag(LL root, LL val) { Tree[root].Max += val; Tree[root].Min += val; Tree[root].lazy += val; }
inline void PushDown(LL root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Modify(LL root, LL l, LL r, LL L, LL R, LL val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; }
	LL Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	Tree[root].Max = max(Tree[rson].Max, Tree[lson].Max);
	Tree[root].Min = min(Tree[rson].Min, Tree[lson].Min);
}

inline LL Query(LL root, LL l, LL r)
{
	if ( l == r ) 
	{
		Max = max(Max, Tree[root].Max);
		Min = min(Min, Tree[root].Min);
		if ( Max - Min <= lim ) return 0;
		return Tree[root].Max == Max ? 1 : -1;
	}
	LL Mid = l + r >> 1; PushDown(root);
	if ( max(Tree[rson].Max, Max) - min(Tree[rson].Min, Min) <= lim )
	{
		Max = max(Tree[rson].Max, Max);
		Min = min(Tree[rson].Min, Min);
		return Query(lson, l, Mid);
	}
	return Query(rson, Mid + 1, r);
}

inline int find(LL root, LL l, LL r, LL op)
{
	if ( l == r ) return op == -1 ? lim + sum - Tree[root].Max : sum - Tree[root].Max;
	LL Mid = l + r >> 1; PushDown(root);
	if ( (op == 1 && Tree[rson].Min > Min) || (op == -1 && Tree[rson].Max < Max) ) return find(lson, l, Mid, op);
	return find(rson, Mid + 1, r, op);
}

vector<int> distribute_candies(vector<int> c, vector<int> l, vector<int> r, vector<int> v) 
{    
	n = c.size(); q = l.size();
	REP(i, 0, q - 1) 
	{
		a[l[i]].push_back(pii(i + 1, v[i]));
		a[r[i] + 1].push_back(pii(i + 1, -v[i]));
	}
	vector<int> ans(n);
	REP(i, 0, n - 1)
	{
		for ( auto it : a[i] ) { Modify(1, 0, q, it.first, q, it.second); sum += it.second; }
		Max = -INF; Min = INF; lim = c[i];
		LL op = Query(1, 0, q);
		if ( op == 0 ) ans[i] = sum - Min;
		else ans[i] = find(1, 0, q, op);
	}
	return ans;
}
