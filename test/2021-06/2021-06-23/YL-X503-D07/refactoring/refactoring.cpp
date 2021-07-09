/***************************************************************
	File name: refactoring.cpp
	Author: ljfcnyali
	Create time: 2021年06月23日 星期三 12时13分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, a[maxn], ans[maxn], ret = 0x3f3f3f3f, p[maxn], op, To[maxn];
pii AS[maxn], AT[maxn], BS[maxn], BT[maxn], A[maxn], B[maxn];
struct node 
{
	int val;
	bool operator < (const node &a) const { return op == 0 ? val > a.val : val < a.val; }
} ;
map<int, int> Map;

inline void Solve(pii *S, pii *T, int m)
{
	REP(i, 1, n) A[i] = B[i] = pii(0, 0);
	REP(i, 1, m) { A[S[i].first] = pii(1, S[i].second); B[T[i].first] = pii(1, T[i].second); }
	for ( int l = 1, r; l <= n; l = r + 1 ) 
	{
		r = l; int sum = A[l].first - B[l].first;
		while ( r <= n && sum ) { ++ r; sum += A[r].first - B[r].first; }
		REP(i, l, r) 
		{
			if ( A[i].first ) { op = 0; break ; }
			if ( B[i].first ) { op = 1; break ; } 
		}
		priority_queue<node> Q;
		if ( op == 0 ) 
		{
			REP(i, l, r)
			{
				if ( A[i].first ) Q.push({A[i].second});
				if ( B[i].first ) { p[i] = Q.top().val; Q.pop(); }
			}
		}
		else
		{
			for ( int i = r; i >= l; -- i ) 
			{
				if ( A[i].first ) Q.push({A[i].second});
				if ( B[i].first ) { p[i] = Q.top().val; Q.pop(); }
			}
		}
	}
}

inline void calc(int op)
{
	int m1 = 0, m2 = 0, m3 = 0, m4 = 0;
	REP(i, 1, n)
	{
		if ( a[i] % 2 == op ) AS[++ m1] = pii(i, a[i]);
		else BS[++ m2] = pii(i, a[i]);
		if ( i % 2 == 1 ) AT[++ m3] = pii(i, 0);
		else BT[++ m4] = pii(i, 0);
	}
	int sum = 0;
	REP(i, 1, m1) sum += abs(AS[i].first - AT[i].first);
	REP(i, 1, m2) sum += abs(BS[i].first - BT[i].first);
	if ( sum > ret ) return ;
	Solve(AS, AT, m1);
	Solve(BS, BT, m2);
	if ( sum < ret || p[1] < ans[1] ) 
	{
		ret = sum;
		REP(i, 1, n) ans[i] = p[i];
	}
}

int main()
{
    freopen("refactoring.in", "r", stdin);
    freopen("refactoring.out", "w", stdout);
	scanf("%d", &n); 
	int sum1 = 0, sum2 = 0;
	REP(i, 1, n) { scanf("%d", &a[i]); if ( a[i] & 1 ) ++ sum1; else ++ sum2; } 
	REP(i, 1, n) Map[a[i]] = true;
	int m = 0; 
	for ( auto it : Map ) 
	{ 
		++ m; if ( m % 2 != it.first % 2 ) ++ m;
		Map[it.first] = m; To[m] = it.first;
	}
	REP(i, 1, n) a[i] = Map[a[i]];
	if ( sum1 >= sum2 ) calc(1);
	if ( sum2 >= sum1 ) calc(0);
	REP(i, 1, n) printf("%d ", To[ans[i]]); puts("");
    return 0;
}
