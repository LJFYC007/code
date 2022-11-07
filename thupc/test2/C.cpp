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

const int maxn = 4e8 + 10;

int n = 3, a[100], cnt = 0, gggg;
short Map[maxn];
bool Vis[maxn];

inline int ZIP(vector< vector<int> > a)
{
	int b = 0;
	REP(i, 0, n - 1) REP(j, 0, n - 1) b = b * 9 + a[i][j] - 1;
	return b;
}

inline void dfs(vector< vector<int> > a, int num)
{
	if ( num > gggg ) return ;			
	int b = ZIP(a);
	if ( num > Map[b] ) return ;
	if ( Vis[b] && num >= Map[b] ) return ;
	++ cnt;
	Map[b] = num; Vis[b] = true;
	REP(i, 0, n - 1) REP(j, 0, n - 1)		
	{
		swap(a[i][j], a[i][(j + 1) % n]);
		dfs(a, num + 1);
		swap(a[i][j], a[i][(j + 1) % n]);
		swap(a[i][j], a[(i + 1) % n][j]);
		dfs(a, num + 1);
		swap(a[i][j], a[(i + 1) % n][j]);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	memset(Map, 10, sizeof(Map));
	REP(i, 1, n * n) a[i] = i;
	vector< vector<int> > b(n);
	REP(i, 0, n - 1) REP(j, 0, n - 1) b[i].push_back(a[j + i * n + 1]);
	REP(ooo, 1, 20)
	{
		gggg = ooo;
		mem(Vis);
		cnt = 0;
		dfs(b, 0);
		cerr << ooo << " " << cnt << endl;
		if ( cnt == 362880 ) break ; 

	}	
	do
	{
		vector< vector<int> > b(n);
		REP(i, 0, n - 1) REP(j, 0, n - 1) b[i].push_back(a[j + i * n + 1]);
		if ( Map[ZIP(b)] == gggg )
		{
			REP(i, 1, n * n) printf("%d ", a[i]); puts("");
			printf("%d\n", Map[ZIP(b)]);
		}
	} while ( next_permutation(a + 1, a + n * n + 1) ) ;
    return 0;
}
