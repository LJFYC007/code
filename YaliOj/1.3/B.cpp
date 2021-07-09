/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月09日 星期四 15时22分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define DEP(i, a, b) for ( int i = (b), _end_ = (a); i >= _end_; -- i )
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, m, s = 0x3f3f3f3f;

inline int check1(int x)
{
	int sum = 0;
	REP(i, 1, x) sum += i * i;
	return sum;
}

inline int check2(int x)
{
	int sum = 0;
	REP(i, 1, x) sum += 2 * i;
	return sum;
}

inline void DFS(int R, int H, int V, int num, int S)
{
	if ( num == 1 ) S += R * R;
	if ( S >= s ) return ;
	if ( num == m )
	{
		if ( V == n ) s = min(S, s);
		return ;
	}
	if ( V >= n ) return ;
	if ( 2 * (n - V) / R + S > s ) return ;
//	for ( int i = R - 1; i >= m - num; -- i )
	DEP(i, m - num, min(R - 1, (int)sqrt(n - V)))
	{
		if ( check1(m - num) + V > n ) continue ;
		if ( check2(m - num) + S >= s ) continue ;
//		for ( int j = H - 1; j >= m - num; -- j )
		DEP(j, m - num, min(H - 1, (int)(n - V) / i / i))
		{
			int v = i * i * j;
			if ( v + V + check1(m - num - 1) > n ) continue ;
			int ss = 2 * i * j;
			if ( ss + S + check2(m - num - 1) >= s ) continue ; 
			DFS(i, j, V + v, num + 1, S + ss);
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	DFS((int)sqrt(n) + 1, n + 1, 0, 0, 0);
	printf("%d\n", s);
    return 0;
}
