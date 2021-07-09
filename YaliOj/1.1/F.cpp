/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 11时30分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

priority_queue <int, vector<int>, greater<int> > Q;
priority_queue <int,vector<int>,less<int> >q;
int Min, Max, n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { int x; scanf("%d", &x); q.push(x); Q.push(x); }
	while ( !q.empty() ) 
	{
		if ( q.size() == 1 ) { Min = q.top(); break ; }
		int x = q.top(); q.pop();
		int y = q.top(); q.pop();
		x = x * y + 1;
		q.push(x);
	}
	while ( !Q.empty() ) 
	{
		if ( Q.size() == 1 ) { Max = Q.top(); break ; }
		int x = Q.top(); Q.pop();
		int y = Q.top(); Q.pop();
		x = x * y + 1;
		Q.push(x);
	}
	printf("%d\n", Max - Min);
    return 0;
}
