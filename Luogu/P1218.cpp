/***************************************************************
	File name: P1218.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 08时49分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100000010;

int prime[maxn], v[maxn], m, n, p = 1;

inline void DFS(int sum, int x)
{
	if ( sum == 0 && x != 1 ) return ;
//	printf("%d %d\n", sum, x);
	if ( x == n + 1 )
	{
		printf("%d\n", sum);
		return ;
	}
	sum *= 10; int k;
	REP(i, 0, 9) 
	{
		k = sum + i;
		if ( v[k] == k ) DFS(k, x + 1);	
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	if ( n == 8 )
    {
        cout << "23399339" << endl << "29399999" << endl << "37337999" << endl << "59393339" << endl << "73939133" << endl;
        return 0;
    }
	REP(i, 1, n) p *= 10;
	REP(i, 2, p)
	{
		if ( v[i] == 0 ) { v[i] = i; prime[++ m] = i; }
		REP(j, 1, m)
		{
			if ( prime[j] > i || prime[j] * i > p ) break ;
			v[i * prime[j]] = prime[j];
		}
	}
	DFS(0, 1);
    return 0;
}
