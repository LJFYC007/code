/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年05月27日 星期一 11时00分37秒
***************************************************************/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<vector>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

struct node
{
	int a[5][5], sum;
} p1, p2;

int a[5][5], Hash[1000010];
int Max = 19260817;

inline int js(node x)
{
	int sum = 0;
	REP(i, 1, 4) REP(j, 1, 4) if ( x.a[i][j] != a[i][j] ) ++ sum;
	return sum;
}

inline bool cha(node x)
{
	int sum = 0, cnt = 32768;
	REP(i, 1, 4) REP(j, 1, 4) { sum += x.a[i][j] * cnt; cnt /= 2; }
//	cerr << sum << endl;
	if ( Hash[sum] ) return true;
	Hash[sum] = 1; return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 1, 4) REP(j, 1, 4) scanf("%1d", &p1.a[i][j]);
	p1.sum = 0;
	REP(i, 1, 4) REP(j, 1, 4) scanf("%1d", &a[i][j]);
	queue<node> Q; Q.push(p1);
	while ( !Q.empty() ) 
	{
		p1 = Q.front(); Q.pop();
		int x = js(p1);
//		REP(i, 1, 4) { REP(j, 1, 4) cerr << p1.a[i][j] << " " ; cerr << endl; }
//		cerr << endl;
		if ( x == 0 ) { printf("%d\n", p1.sum); return 0; }
		if ( cha(p1) ) continue ;
		p1.sum ++;
		REP(i, 1, 4)
			REP(j, 1, 3)
			{
				if ( p1.a[i][j] != p1.a[i][j + 1] ) 
				{
					swap(p1.a[i][j], p1.a[i][j + 1]);
					Q.push(p1);
					swap(p1.a[i][j], p1.a[i][j + 1]);
				}
			}
		REP(i, 1, 3)
			REP(j, 1, 4)
			{
				if ( p1.a[i][j] != p1.a[i + 1][j] ) 
				{
					swap(p1.a[i][j], p1.a[i + 1][j]);
					Q.push(p1);
					swap(p1.a[i][j], p1.a[i + 1][j]);
				}
			}
	}
    return 0;
}
