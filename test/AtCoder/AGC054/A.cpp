/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年06月27日 星期日 19时48分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n; char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1);
	if ( s[1] != s[n] ) { puts("1"); return 0; } 
	REP(i, 2, n - 2) if ( s[i] != s[1] && s[i + 1] != s[1] ) 
	{
		puts("2"); return 0;
	}
	puts("-1");
    return 0;
}
