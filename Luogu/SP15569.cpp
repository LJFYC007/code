/***************************************************************
	File name: SP15569.cpp
	Author: ljfcnyali
	Create time: 2019年05月24日 星期五 13时40分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

typedef long long LL;
const int maxn = 500010;
const int Max = 19260817;

LL Hash1[maxn], Hash2[maxn], base[maxn], n, ans;
char s[maxn];

inline bool check(int l, int r, int L, int R)
{
	if ( Hash1[r] - Hash1[l - 1] * base[r - l + 1] == Hash2[L] - Hash2[R + 1] * base[R - L + 1] )
		return true;
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); getchar();
	scanf("%s", s + 1);
	REP(i, 1, n) Hash1[i] = Hash1[i - 1] * Max + s[i] - '0';
	for ( int i = n; i >= 1; -- i ) Hash2[i] = Hash2[i + 1] * Max - s[i] + '0' + 1;
	base[0] = 1;
	REP(i, 1, n) base[i] = base[i - 1] * Max;
	REP(i, 1, n - 1)
	{
		if ( s[i] == s[i + 1] ) continue ;
		int l = 1, r;
		if ( i < n - i ) r = i; else r = n - i;
		while ( l <= r ) 
		{
			int Mid = (l + r) / 2;
			if ( check(i - Mid + 1, i, i + 1, i + Mid) ) l = Mid + 1;
			else r = Mid - 1;
		}
		ans += r;
	}
	printf("%lld\n", ans);
    return 0;
}
