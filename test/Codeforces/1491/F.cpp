/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年03月05日 星期五 10时04分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n;
bool vis[maxn];

int main()
{
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); int pos = 0; vector<int> ans;
		REP(i, 2, n) if ( !pos ) 
		{
			printf("? 1 %d\n", i - 1);
			printf("%d\n", i); REP(j, 1, i - 1) printf("%d\n", j); fflush(stdout);
			int x; scanf("%d", &x);
			if ( x != 0 ) { pos = i; ans.push_back(i); } 
		}
		else 
		{
			printf("? 1 %d\n", pos - 1);
			printf("%d\n", i); REP(j, 1, pos - 1) printf("%d\n", j); fflush(stdout);
			int x; scanf("%d", &x);
			if ( x != 0 ) ans.push_back(i); 
		}

		int l = 1, r = pos - 1, ret = 0;
		while ( l <= r ) 
		{
			int Mid = l + r >> 1;
			printf("? 1 %d\n", Mid);
			printf("%d\n", pos); REP(j, 1, Mid) printf("%d\n", j); fflush(stdout);
			int x; scanf("%d", &x);
			if ( x != 0 ) { r = Mid - 1; ret = Mid; } 
			else l = Mid + 1;
		}
		ans.push_back(ret);

		REP(i, 1, n) vis[i] = false;
		for ( auto it : ans ) vis[it] = true;
		printf("! %d ", (int)(n - ans.size()));
		REP(i, 1, n) if ( !vis[i] ) printf("%d ", i);
		puts(""); fflush(stdout);
	}
    return 0;
}
