/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 20时03分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int A, B, C;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % 4; a = a * a % 4; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	cin >> A >> B >> C; A %= 10;
	int t = power(B, C) + 4;
	int val = 1; REP(i, 1, t) val = val * A % 10;
	printf("%lld\n", val);
	return 0;
}
