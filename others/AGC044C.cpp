/***************************************************************
	File name: AGC044C.cpp
	Author: ljfcnyali
	Create time: 2021年07月09日 星期五 15时52分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, tot = 1, ans[maxn], p[maxn]; char s[maxn];
struct node { int son[3]; bool lazy; } Tree[maxn << 5];

inline void PushTag(int root) { Tree[root].lazy ^= 1; swap(Tree[root].son[1], Tree[root].son[2]); }
inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	REP(i, 0, 2) PushTag(Tree[root].son[i]);
	Tree[root].lazy ^= 1;
}

inline void Insert(int x, int val)
{
	int p = 1;
	REP(i, 1, n)
	{
		if ( !Tree[p].son[x % 3] ) Tree[p].son[x % 3] = ++ tot;
		p = Tree[p].son[x % 3]; x /= 3;
	}
	Tree[p].son[0] = val; 
}

inline void DFS(int x, int dep, int w)
{
	if ( dep == n + 1 ) { ans[Tree[x].son[0]] = w; return ; } 
	PushDown(x); 
	REP(i, 0, 2) DFS(Tree[x].son[i], dep + 1, w + p[dep - 1] * i);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	m = 1; REP(i, 1, n) m *= 3;
	REP(i, 0, m - 1) Insert(i, i);
	p[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * 3;
	scanf("%s", s + 1);
	REP(i, 1, str(s + 1)) if ( s[i] == 'S' ) PushTag(1);
	else 
	{
		int p = 1;
		REP(i, 1, n)
		{
			PushDown(p);
			swap(Tree[p].son[0], Tree[p].son[1]);
			swap(Tree[p].son[0], Tree[p].son[2]);
			p = Tree[p].son[0];
		}
	}
	DFS(1, 1, 0);
	REP(i, 0, m - 1) printf("%d ", ans[i]); puts("");
    return 0;
}
