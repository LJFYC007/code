/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月09日 星期四 16时43分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int n, a[110], sum, k, m;
bool flag, use[110];

inline void DFS(int x, int num, int S)
{
	if ( num > m ) return ;
	if ( num == m ) 
	{
		int j = -1;
		REP(i, 1, n) if ( !use[i] ) { use[i] = true; j = i; break ; }
		if ( j == -1 ) return ;
		DFS(j, a[j], S + 1);
	}
	if ( S == k ) { flag = true; return ; }
	REP(i, x + 1, n)
	{
		if ( use[i] ) continue ;
		use[i] = true;
		DFS(i, num + a[i], S);
		use[i] = false;
		int j = i;
		while ( a[i] == a[j] && i < n ) ++ i;
		-- i ;
		if ( i == n ) return ;
	}
}

inline int cmp(int x, int y)
{
	return x > y;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); sum += a[i]; }
	sort ( a + 1, a + n + 1, cmp );
	REP(i, a[1], sum)
	{
		if ( sum % i != 0 ) continue ;
		flag = false; 
		mem(use); use[n] = true; k = sum / i; m = i;
		DFS(1, a[1], 1);
		if ( flag == true ) { printf("%d\n", i); return 0; }
	}
    return 0;
}
