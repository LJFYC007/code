/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, n1, n2;
struct node { int x, l, r; } a[maxn], b[maxn];
vector<node> A, B; 
vector<int> t;
bool vis[maxn], use[6];

inline bool cmp(node a, node b) { return a.x < b.x || (a.x == b.x && a.l < b.l); }
inline bool Check(int i, int j) { return B[j].l <= A[i].x && A[i].x <= B[j].r && A[i].l <= B[j].x && B[j].x <= A[i].r; }

inline void DFS(int x)
{
	if ( vis[x] ) return ; 
	vis[x] = true; t.push_back(x);
	if ( x < 7 ) { REP(i, 0, 7) if ( Check(x, i) ) DFS(7 + i); }
	else { REP(i, 0, 6) if ( Check(i, x - 7) ) DFS(i); }
}

inline bool Solve(int x)
{
	if ( x == 1 ) 
	{
		if ( t.size() != 2 ) return false ; 
		int u = t[0], v = t[1] - 7;
		return B[v].l < A[u].x && A[u].x == B[v].r && A[u].l < B[v].x && B[v].x < A[u].r;
	}
	if ( x == 2 || x == 3 ) 
	{
		if ( t.size() != 3 ) return false;
		int u = t[0], v = t[1] - 7, w = t[2] - 7;
		if ( B[v].x > B[w].x ) swap(v, w);
		if ( !(B[v].x == A[u].l && A[u].r == B[w].x && B[v].l == B[w].l && B[w].l <= A[u].x && A[u].x < B[w].r && B[w].r == B[v].r) )
			return false;
		if ( B[w].l == A[u].x && x == 3 ) return true;
		if ( B[w].l < A[u].x && x == 2 ) return true;
		return false;
	}
	if ( x == 4 ) 
	{
		if ( t.size() != 4 ) return false;
		int u = t[0], v = t[1], w = t[2] - 7, k = t[3] - 7;
		if ( A[u].x > A[v].x ) swap(u, v);
		if ( B[w].x > B[k].x ) swap(w, k);

		if ( !(B[w].l < A[u].x && A[u].x < A[v].x && A[v].x == B[w].r && A[u].x == B[k].l && A[v].x == B[k].r) ) return false;
		if ( !(B[w].x == A[u].l && A[u].l == A[v].l && A[u].r == A[v].r && B[k].x == A[v].r) ) return false;	
		return true;
	}
	if ( x == 5 ) 
	{
		if ( t.size() != 3 ) return false;
		int u = t[0], v = t[1], w = t[2] - 7;
		if ( A[u].x > A[v].x ) swap(u, v);
		return B[w].x == A[u].l && A[u].l == A[v].l && A[u].r == A[v].r && A[u].x == B[w].l && A[v].x == B[w].r;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n)
	{
		int op; scanf("%d", &op);
		if ( op == 0 ) { ++ n1; scanf("%d%d%d", &a[n1].l, &a[n1].r, &a[n1].x); }
		if ( op == 1 ) { ++ n2; scanf("%d%d%d", &b[n2].l, &b[n2].r, &b[n2].x); }
	}
	sort(a + 1, a + n1 + 1, cmp);
	sort(b + 1, b + n2 + 1, cmp);

	for ( int i = 1, j; i <= n1; i = j )
	{
		j = i; int Min = a[i].l, Max = a[i].r;
		while ( j <= n1 && a[j].x == a[i].x )
		{
			if ( a[j].l <= Max ) Max = max(Max, a[j].r); 
			else 
			{
				A.push_back({a[j].x, Min, Max});
				Min = a[j].l; Max = a[j].r;
			}
			++ j;
		}
		A.push_back({a[i].x, Min, Max});
	}	

	for ( int i = 1, j; i <= n2; i = j )
	{
		j = i; int Min = b[i].l, Max = b[i].r;
		while ( j <= n2 && b[j].x == b[i].x )
		{
			if ( b[j].l <= Max ) Max = max(Max, b[j].r); 
			else 
			{
				B.push_back({b[j].x, Min, Max});
				Min = b[j].l; Max = b[j].r;
			}
			++ j;
		}
		B.push_back({b[i].x, Min, Max});
	}	

	//for ( auto it : A ) cerr << it.x << " " << it.l << " " << it.r << endl;
	if ( A.size() != 7 || B.size() != 8 ) { puts("No"); return 0; }	
	for ( int i = 0; i < A.size(); ++ i ) if ( !vis[i] ) 
	{
		t.clear(); DFS(i); sort(t.begin(), t.end());

/*
		cerr << endl;
		for ( auto it : t ) 
		{
			if ( it < 7 ) cerr << A[it].x << " " << A[it].l << " " << A[it].r << endl;
			else cerr << B[it - 7].x << " " << B[it - 7].l << " " << B[it - 7].r << endl;
		}
		*/
		//return 0;

		REP(i, 1, 5) if ( !use[i] && Solve(i) ) { use[i] = true; break ; }
	}
	//REP(i, 1, 5) cerr << use[i] << " "; cerr << endl;
	REP(i, 1, 5) if ( !use[i] ) { puts("No"); return 0; }
	REP(i, 0, 14) if ( !vis[i] ) { puts("No"); return 0; }
	puts("Yes");
    return 0;
}
