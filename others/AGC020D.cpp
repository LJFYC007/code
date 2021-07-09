/***************************************************************
	File name: AGC020D.cpp
	Author: ljfcnyali
	Create time: 2021年06月25日 星期五 21时23分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 1e5 + 10;

int T, A, B, C, D, k;

inline void print1(int l, int r)
{
	REP(i, l, r)
		if ( i % (k + 1) != 0 ) printf("A");
		else printf("B");
}

inline void print2(int l, int r)
{
	REP(i, l, r)
		if ( (A + B - i + 1) % (k + 1) != 0 ) printf("B");
		else printf("A");
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%lld%lld%lld%lld", &A, &B, &C, &D);
		k = max((A - 1) / (B + 1) + 1, (B - 1) / (A + 1) + 1);
		int l = 1, r = A + B, pos = 0;
		while ( l <= r ) 
		{
			int Mid = l + r >> 1;
			int xb = Mid / (k + 1), xa = Mid - xb;
			if ( Mid % (k + 1) == 0 ) -- xb;
			if ( B - xb <= (A - xa + 1) * k ) { pos = Mid; l = Mid + 1; }
			else r = Mid - 1;
		}
		if ( D <= pos ) print1(C, D);
		else if ( C > pos ) print2(C, D);
		else { print1(C, pos); print2(pos + 1, D); }
		puts("");
	}
    return 0;
}
