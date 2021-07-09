/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月27日 星期六 09时26分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;

int n, nxt[maxn][26], ans, tot = 1, last = 1;
char s[maxn], t[maxn];
struct node { int Next[26], len, fa; } Tree[maxn];
bool vis[maxn][maxn];

inline void Extand(int c)
{
    int cur = ++ tot; Tree[cur].len = Tree[last].len + 1; 
    int p = last; last = cur;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot;
    Tree[clone] = Tree[q];
    Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) 
    {
        Tree[p].Next[c] = clone;
        p = Tree[p].fa;
    }
    Tree[q].fa = Tree[cur].fa = clone;
}

signed main()
{
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
	scanf("%d", &n); scanf("%s", s + 1); scanf("%s", t + 1);	
	REP(i, 0, 25) nxt[n + 1][i] = n + 1;
	for ( int i = n; i >= 1; -- i ) 
	{
		REP(j, 0, 25) nxt[i][j] = nxt[i + 1][j];
		nxt[i][s[i] - 'a'] = i;
	}
	REP(i, 1, n) Extand(t[i] - 'a');

	REP(i, 1, n) 
	{
		int now = 1, p = 1; 
		REP(j, i, n)
		{
			int c = t[j] - 'a'; p = Tree[p].Next[c];
			now = nxt[now][c] + 1; if ( now > n + 1 ) break ; 
			if ( !vis[p][j - i + 1] ) { ++ ans; vis[p][j - i + 1] = true; } 
		}
	}
	printf("%d\n", ans);
    return 0;
}
