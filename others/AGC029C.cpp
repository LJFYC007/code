/***************************************************************
	File name: AGC029C.cpp
	Author: ljfcnyali
	Create time: 2021年04月04日 星期日 10时25分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;

int n, a[maxn], tot;
pii Stack[maxn];

inline void Add()
{
	int len = Stack[tot].x, val = Stack[tot].y; 
	if ( len > 1 ) Stack[tot] = pii(len - 1, val); else -- tot;
	Stack[++ tot] = pii(1, val + 1);
}

inline bool Check(int x)
{
	tot = 1; Stack[1] = pii(a[1], 1); 
	REP(i, 2, n)
		if ( a[i] > a[i - 1] ) Stack[++ tot] = pii(a[i] - a[i - 1], 1);
		else
		{
			int len = a[i - 1];
			while ( len > a[i] ) 
			{
				int val = min(len - a[i], Stack[tot].x);	
				Stack[tot].x -= val; len -= val;
				if ( !Stack[tot].x ) -- tot;
			}
			while ( Stack[tot].y == x ) { len -= Stack[tot].x; -- tot; }
			if ( !tot ) return false;
			Add(); if ( len < a[i] ) Stack[++ tot] = pii(a[i] - len, 1);
		}
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	int l = 1, r = n, ans = 0;
	while ( l <= r ) 
	{
		int Mid = l + r >> 1;
		if ( Check(Mid) ) { ans = Mid; r = Mid - 1; }
		else l = Mid + 1;
	}
	printf("%d\n", ans);
    return 0;
}
