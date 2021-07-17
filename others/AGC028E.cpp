/***************************************************************
	File name: AGC028E.cpp
	Author: ljfcnyali
	Create time: 2021年07月14日 星期三 21时36分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, Max, a[maxn], p[maxn], q[maxn];
string s, t;
struct Segment
{
	struct node { int Max; } Tree[maxn << 2];
#define lson root << 1
#define rson root << 1 | 1

	inline void Modify(int root, int l, int r, int pos, int val)
	{
		if ( l == r ) { Tree[root].Max = val; return ; } 
		int Mid = l + r >> 1; 
		if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
		else Modify(rson, Mid + 1, r, pos, val);
		Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
	}

	inline int Query(int root, int l, int r, int L, int R)
	{
		if ( L <= l && r <= R ) return Tree[root].Max;
		int Mid = l + r >> 1, ret = -INF;
		if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid, L, R));
		if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r, L, R));
		return ret;
	}
} A[2];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n)
	{
		scanf("%d", &a[i]);
		if ( a[i] > Max ) { Max = a[i]; ++ m; p[i] = q[a[i]] = 2; }
		else p[i] = q[a[i]] = 1;
	}
	REP(i, 1, n * 4 + 4) A[0].Tree[i].Max = A[1].Tree[i].Max = -INF;
	A[0].Modify(1, 1, n + 1, n + 1, 0);
	for ( int i = n; i >= 1; -- i ) REP(j, 0, 1)
		A[(j + p[i]) % 2].Modify(1, 1, n + 1, a[i], A[j].Query(1, 1, n + 1, a[i] + 1, n + 1) + p[i]);

	int sum = 0, pos = 0, lst = 0;
	REP(i, 1, n) if ( a[i] > pos ) 
	{
		if ( sum <= m && A[(m - sum) % 2].Query(1, 1, n + 1, a[i], a[i]) >= m - sum 
				&& m - sum >= p[i] ) { t += '0'; sum += p[i]; pos = a[i]; }
		else t += '1';
	}
	else t += '0';
	if ( sum != m ) { puts("-1"); return 0; }
	sum = pos = 0;
	REP(i, 1, n) 
	{
		A[0].Modify(1, 1, n + 1, a[i], -INF);
		A[1].Modify(1, 1, n + 1, a[i], -INF);
		bool flag = false; 
		if ( m - sum <= 1 ) 
		{
			REP(j, pos + 1, n + 1) 
			{
				int w = A[(m - sum) % 2].Query(1, 1, n + 1, j, j);
				if ( w >= m - sum && m - sum >= q[j] )
					flag = true;
			}
		}
		else 
			flag = A[(m - sum) % 2].Query(1, 1, n + 1, pos + 1, n + 1) >= m - sum;

		if ( (flag && (a[i] < lst|| p[i] == 2)) || (a[i] < lst && a[i] < pos)) { s += '0'; lst = max(lst, a[i]); }
		else { s += '1'; if ( a[i] > pos ) { sum += p[i]; pos = a[i]; } }
	}
	if ( s < t ) cout << s << endl; else cout << t << endl;
    return 0;
}
