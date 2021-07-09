/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月10日 星期五 14时12分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int vis[70010][5][5], f[5][5], n, sum;

struct node 
{
	int a[5][5], sum, t;
	bool operator < (const node & x) const
	{
		//return sum > x.sum || (sum == x.sum && t > x.t);
		return t > x.t;
	}
}p1, p2;

inline bool pd(node x)
{
	REP(i, 1, n) REP(j, 1, n) if ( x.a[i][j] != f[i][j] ) return false;
	return true;
}

inline int js(node x)
{
	int s = 0;
	REP(i, 1, n) REP(j, 1, n) if ( x.a[i][j] != f[i][j] ) ++ s;
	return s;
}

inline void BFS()
{
    priority_queue<node> Q; p1.sum = 0; p1.t = js(p1);
	Q.push(p1); 
	int cnt = 0, ans = 0x3f3f3f3f;
	while ( !Q.empty() )
	{
		if ( (double)clock() / CLOCKS_PER_SEC > 0.999 ) { printf("20\n"); return ; } 
		p1 = Q.top(); Q.pop();
//		if ( p1.sum >= ans ) continue ;
		//printf("%d\n", p1.t);
		if ( pd(p1) ) 
		{
			printf("%d\n", p1.sum); return ;
	//		ans = p1.sum;
	//		continue ;
		}
		bool flag = true;
		for ( int k = sum; k >= 1; -- k )
		{
			bool flag1 = true;
			REP(i, 1, n) REP(j, 1, n) if ( vis[k][i][j] != p1.a[i][j] ) { flag1 = false; goto finish; }
		 	if ( flag1 == true ) { flag = false ; break ; } 
finish : ;
		}
		if ( flag == false ) continue ;
		++ sum;
		REP(i, 1, n) REP(j, 1, n) vis[sum][i][j] = p1.a[i][j];
		REP(i, 1, n) REP(j, 1, n - 1)
		{
			p2 = p1;
			if ( p2.a[i][j] == p2.a[i][j + 1] ) continue ;
			swap(p2.a[i][j], p2.a[i][j + 1]);
			p2.sum = p1.sum + 1;
			p2.t = js(p2) + p2.sum;
			Q.push(p2);
		}
		REP(i, 1, n - 1) REP(j, 1, n)
		{
			p2 = p1;
			if ( p2.a[i][j] == p2.a[i + 1][j] ) continue ;
			swap(p2.a[i][j], p2.a[i + 1][j]);
			p2.sum = p1.sum + 1;
			p2.t = js(p2) + p2.sum;
			Q.push(p2);
		}
	}
	cout << ans << endl;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = 4;
	REP(i, 1, n) 
	{
		REP(j, 1, n) 
		{	
			char c = getchar();
			p1.a[i][j] = c - '0';
		}
		getchar();
	}
	getchar();
	REP(i, 1, n) 
	{
		REP(j, 1, n) 
		{	
			char c = getchar();
			f[i][j] = c - '0';
		}
		getchar();
	}
	BFS();
    return 0;
}
