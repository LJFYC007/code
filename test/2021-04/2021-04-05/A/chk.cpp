/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2021年04月05日 星期一 15时47分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 20;

int n, q, a[maxn], m, Edge[maxn][maxn], s, k;
bool vis[maxn];

inline bool check() 
{
	int p = s;
	REP(i, 1, n) p = Edge[p][a[i]];
	return vis[p];
}

int main()
{
    freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &q); int num = 0;
	freopen("output.txt", "r", stdin);
	scanf("%d", &m);
	REP(i, 1, m) REP(j, 1, n) scanf("%d", &Edge[i][j]);
	scanf("%d", &s);
	scanf("%d", &k);  REP(i, 1, k) { int x; scanf("%d", &x); vis[x] = true; } 
	REP(i, 1, n) a[i] = i;
	do
	{
		if ( check() ) ++ num;
	} while ( next_permutation(a + 1, a + n + 1) );
	if ( num != q ) puts("WA");
	else puts("YES");
    return 0;
}
