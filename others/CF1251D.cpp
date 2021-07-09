/***************************************************************
	File name: CF1251D.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 21时24分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int T, n, s;
struct node
{
    int l, r;
    bool operator < (const node &a) const { return l > a.l || (l == a.l && r > a.r); }
} a[maxn];

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline bool Check(int x)
{
    int cnt = (n + 1) / 2, ret = 0;
    REP(i, 1, n)
        if ( cnt && a[i].r >= x ) { ret += max(a[i].l, x); -- cnt; }
        else ret += a[i].l;
    return ret <= s && !cnt;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(T);
    while ( T -- ) 
    {
        read(n); read(s);
        REP(i, 1, n) { read(a[i].l); read(a[i].r); }
        sort(a + 1, a + n + 1);
        int L = 0, R = s, ans = 0;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( Check(Mid) ) { ans = Mid; L = Mid + 1; }
            else R = Mid - 1;
        }
        cout << ans << endl;
    }
    return 0;
}
