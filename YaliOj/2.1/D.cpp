/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年05月25日 星期六 08时21分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;
typedef long long LL;

LL m = 19260817, len, Hash[maxn], base[maxn], ans;
string s;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( cin >> s )
	{
		base[1] = m; len = s.length(); Hash[1] = s[0] - '0';
		REP(i, 2, len) base[i] = base[i - 1] * m;
		REP(i, 2, len) Hash[i] = Hash[i - 1] * m + s[i - 1] - '0';
		REP(i, 1, len)
		{
			if ( Hash[i] == (Hash[len] - Hash[len - i] * base[i]) ) printf("%d ", i);
		}
		puts("");
	}
    return 0;
}
