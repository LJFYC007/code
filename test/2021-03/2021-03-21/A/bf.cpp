/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 09时01分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1);
	REP(i, 1, n) a[i] = i;
	do
	{
		bool ret = true;
		REP(i, 1, n - 1)		
		{
			bool flag = (a[i] == a[i + 1] * 2) | (a[i] * 2 == a[i + 1]);
			if ( flag && s[i] == '0' ) ret = false;
			if ( !flag && s[i] == '1' ) ret = false;
		}
		if ( ret ) ++ ans;
	} while ( next_permutation(a + 1, a + n + 1) ) ;
	printf("%d\n", ans);
    return 0;
}
