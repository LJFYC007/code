/***************************************************************
	File name: P3498.cpp
	Author: ljfcnyali
	Create time: 2019年05月24日 星期五 13时28分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

typedef long long LL;
const int maxn = 200010;
const int Max = 19260817;

LL Hash1[maxn], Hash2[maxn], a[maxn], n, ans[maxn], cnt, sum, base[maxn];
set<LL> S;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
	base[0] = 1;
	REP(i, 1, n) { Hash1[i] = Hash1[i - 1] * Max + a[i]; base[i] = base[i - 1] * Max; }
	for ( int i = n; i >= 1; -- i) Hash2[i] = Hash2[i + 1] * Max + a[i];
	REP(k, 1, n)
	{
		if ( n / k < sum ) break ; 
		S.clear(); int p = 0;
		for ( int i = k; i <= n; i += k ) 
		{
			LL t1 = Hash1[i] - Hash1[i - k] * base[k];
			LL t2 = Hash2[i - k + 1] - Hash2[i + 1] * base[k];
			LL t3 = t1 * t2;
			if ( S.count(t3) ) continue ;
			S.insert(t3); ++ p;
		}
		if ( p > sum ) { sum = p; cnt = 1; ans[1] = k; }
		else if ( p == sum ) ans[++ cnt] = k;
	}
	printf("%lld %lld\n", sum, cnt);
	REP(i, 1, cnt) printf("%lld ", ans[i]); puts("");
    return 0;
}
