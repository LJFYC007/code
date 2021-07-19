/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 10时47分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int a[maxn];
bool vis[maxn];
vector< vector<int> > BBB;

int main()
{
    freopen("input.txt", "w", stdout);
	srand((unsigned long long)new char);
	int n = 100 - rand() % 2, m = rand() % 100 + 1, k = 1; 
	REP(i, 1, (n + 1) / 2) a[i] = a[n - i + 1] = rand() % m + 1;
	REP(i, 1, n - 1)	
	{
		vis[i] = rand() % 10 == 0;
		if ( !vis[i] && !vis[i - 1] && i > 1 ) vis[i] = true;
		if ( vis[i] ) ++ k;
	}
	vis[n] = true;
	printf("%d %d\n", k, m);
	for ( int i = 1; i <= n; ++ i ) 
	{
		vector<int> p;
		while ( !vis[i] ) { p.push_back(i); ++ i; } 
		p.push_back(i);
		BBB.push_back(p);
	}
	random_shuffle(BBB.begin(), BBB.end());
	for ( auto p : BBB)
	{
		printf("%d ", p.size());
		for ( auto it : p ) printf("%d ", a[it]); puts("");
	}
    return 0;
}
