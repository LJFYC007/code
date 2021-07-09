/***************************************************************
	File name: sam.cpp
	Author: ljfcnyali
	Create time: 2021年02月17日 星期三 11时26分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 20;

int T, n, k, ans;
struct SAM
{
	struct node { int Next[10], len, fa; } Tree[maxn];
	int tot = 1, last = 1;

	inline void Extand(int c)
	{
		int cur = ++ tot, p = last; Tree[cur].len = Tree[p].len + 1; last = cur; 
		while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; } 	
		if ( !p ) { Tree[cur].fa = 1; return ; } 
		int q = Tree[p].Next[c];
		if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; } 
		int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
		while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; } 
		Tree[q].fa = Tree[cur].fa = clone; 
	}
} f[maxn];

inline void DFS(int x)
{
	if ( x == n + 1 ) { ans += f[n].tot; return ; } 
	REP(j, 1, k)
	{
		f[x] = f[x - 1];
		f[x].Extand(j); 
		DFS(x + 1);
	}
}

int main()
{
    freopen("sam.in", "r", stdin);
    freopen("sam.out", "w", stdout);
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d", &n, &k);
		ans = 0; DFS(1);
		printf("%d\n", ans);
	}
    return 0;
}
