/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 11时10分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;
typedef __uint128_t u128;
inline u128 read() {
    static char buf[100]; scanf("%s", buf);
    u128 res = 0;
    for(int i = 0;buf[i];++i)
        res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);
    return res;
}
inline void output(u128 res) {
    if(res >= 16)
        output(res / 16);
    putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);
}

int n, q;
u128 a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &q);	
	REP(i, 1, n) a[i] = read();
	while ( q -- ) 
	{
		int op, l, r; u128 v;
		scanf("%d%d%d", &op, &l, &r);
		if ( op == 1 ) 
		{
			v = read();
			REP(i, l, r) a[i] /= v;
		}
		if ( op == 2 ) 
		{
			v = read();
			REP(i, l, r) a[i] &= v;
		}
		if ( op == 3 ) 
		{
			u128 ans = 0;
			REP(i, l, r) ans += a[i];
			output(ans); putchar('\n');
		}
	}
    return 0;
}
