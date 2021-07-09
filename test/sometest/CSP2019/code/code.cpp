#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int unsigned long long

const int maxn = 100;

int n, k;
char s[maxn];

signed main()
{
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
	cin >> n >> k;
	for ( int i = n, j = 4; i >= 3; -- i, j *= 2 )
	{
		int x = j / 4;
		if ( k % j < x || k % j >= (j - x) ) s[i] = '0';
		else s[i] = '1';
	}
	int x = 1llu << (n - 1);
	if ( k >= x ) s[1] = '1'; else s[1] = '0';
	if ( n > 1 ) 
	{
		x /= 2;
		if ( k < x || k >= x * 3 ) s[2] = '0'; else s[2] = '1';
	}
	REP(i, 1, n) printf("%c", s[i]); puts("");
	return 0;
}
