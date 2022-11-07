/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int f[10];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1);
	bool flag = true;
	int lst1 = s[1] - 'A', lst2 = s[2] - 'A';
	REP(i, 3, str(s + 1)) 
	{
		if ( (lst1 + lst2) % 26 != s[i] -'A' ) flag = false;
		lst1 = lst2; lst2 = s[i] - 'A';
	}
	if ( flag ) puts("YES"); else puts("NO");
    return 0;
}
