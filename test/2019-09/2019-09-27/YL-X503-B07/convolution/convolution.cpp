/***************************************************************
	file name: convolution.cpp
	author: ljfcnyali
	create time: 2019年09月27日 星期五 19时08分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long ll;

const int maxn = 100010;

int a[maxn], b[maxn], n, m, f[20][20], c[maxn];

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("convolution.in", "r", stdin);
    freopen("convolution.out", "w", stdout);
    scanf("%d%d", &n, &m);
    rep(i, 0, (1 << n) - 1) read(a[i]);
    rep(i, 0, (1 << n) - 1) read(b[i]);
    rep(i, 0, m - 1) rep(j, 0, m - 1) scanf("%d", &f[i][j]);
    rep(i, 0, (1 << n) - 1)
        rep(j, 0, (1 << n) - 1)
            c[i | j] = max(c[i | j], f[a[i]][b[j]]);
    rep(i, 0, (1 << n) - 1) printf("%d ", c[i]);
    return 0;
}

