/***************************************************************
	File name: AGC026E.cpp
	Author: ljfcnyali
	Create time: 2021年04月23日 星期五 20时32分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;

int n, m1, m2, A[maxn], B[maxn], belong[maxn];
char s[maxn]; 
string f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1);
	REP(i, 1, n + n) if ( s[i] == 'a' ) A[++ m1] = i, belong[i] = m1; else B[++ m2] = i, belong[i] = m2;
	REP(i, 1, n + n) if ( belong[i] == n ) f[n] = f[n] + s[i];
	belong[n + n + 1] = n + 1;
	for ( int i = n - 1; i >= 1; -- i ) 
	{
		if ( A[i] < B[i] ) 
		{
			for ( int j = B[i] + 1; j <= n + n; ++ j ) if ( s[j] == 'a' ) { f[i] = "ab" + f[belong[j]]; break ; } 
		}
		else
		{
			int x = A[i];
			for ( int j = B[i]; j <= x; ++ j ) 
			{
				if ( s[j] == 'b' ) x = max(x, A[belong[j]]);
				if ( belong[j] >= i ) f[i] = f[i] + s[j];
			}
			f[i] = f[i] + f[belong[x + 1]];
		}
		f[i] = max(f[i], f[i + 1]);
	}
	cout << f[1] << endl;
    return 0;
}
