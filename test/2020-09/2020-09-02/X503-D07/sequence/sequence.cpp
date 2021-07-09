/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2020年09月02日 星期三 19时09分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn], f[10];
LL ans;

inline void read(int &x) 
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%d", &n); REP(i, 1, n) read(a[i]);
    sort(a + 1, a + n + 1);
    REP(i, 1, 8) f[i] = f[i - 1] * 10 + 9;
    REP(i, 1, n)
    {
        int pos = i, lst = i;
        REP(j, 1, 8)
        {
            int L = pos + 1, R = n, val = f[j] - a[i];
            while ( L <= R ) 
            {
                int Mid = L + R >> 1;
                if ( a[Mid] <= val ) { pos = Mid; L = Mid + 1; }
                else R = Mid - 1;
            }
            ans += j * (pos - lst); lst = pos;
        }
        ans += 9 * (n - pos);
    }
    printf("%lld\n", ans);
    return 0;
}
