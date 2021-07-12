/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年07月12日 星期一 15时59分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int m, k, a[maxn][maxn], s1[maxn], s2[maxn], pos, w, ccc;
map<int, int> Map;

inline int Check(int i)
{
	int sum = s2[i + 1] + s2[i - 1];
	REP(j, 1, m) sum -= 2 * a[i][j] * a[i][j];
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &m, &k);
	REP(i, 1, k) REP(j, 1, m) 
	{
		scanf("%d", &a[i][j]);
		s1[i] += a[i][j]; s2[i] += a[i][j] * a[i][j];
	}
	REP(i, 1, k - 1) ++ Map[s1[i + 1] - s1[i]];
	REP(i, 2, k) if ( Map[s1[i] - s1[i - 1]] == 1 ) { pos = i; break ; } 
	REP(i, 1, k) if ( i != pos && i + 1 != pos && i + 2 != pos ) 
	{
		w = s2[i + 2] + s2[i] - s2[i + 1] - s2[i + 1];
		ccc = -(s1[pos] - s1[pos - 1]) + (s1[i + 1] - s1[i]);
		break ; 
	}
	REP(i, 1, m)
	{
		a[pos][i] += ccc;
		if ( Check(pos) == w ) { printf("%d %d\n", pos - 1, a[pos][i]); break ; } 
		a[pos][i] -= ccc;
	}
	fflush(stdout);
    return 0;
}
