/***************************************************************
	File name: U95685.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 14时43分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;

int n, m, q, type, a[maxn], A, B, C, P, f[maxn];
unsigned int ans;

inline int rnd() { return A = (A * B + C) % P; }

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &q, &type);
    REP(i, 1, n) read(a[i]);
    if ( type == 1 ) scanf("%d%d%d%d", &A, &B, &C, &P);
    REP(o, 1, q)
    {
        int L, R;
        if ( type == 0 ) { read(L); read(R); }
        else { L = rnd() % n + 1; R = rnd() % n + 1; if ( L > R ) swap(L, R); }
        for ( int i = R; i >= L; -- i )      
        {
            f[i] = a[i] & 1;
            REP(j, i + 1, min(i + m, R)) f[i] &= ~f[j];
        }
        if ( !f[L] ) ans += o * o;
    }
    printf("%d\n", ans);
    return 0;
}
