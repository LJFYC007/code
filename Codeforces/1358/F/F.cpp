/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 09时19分45秒
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

int n, A[maxn], B[maxn], ans;
string s;

inline void Solve()
{
    if ( B[1] > B[2] ) swap(B[1], B[2]);
    if ( B[1] < A[1] || B[2] < A[2] ) { puts("IMPOSSIBLE"); return ; }
    if ( B[1] == A[1] )
    {
        if ( (B[2] - A[2]) % B[1] != 0 ) { puts("IMPOSSIBLE"); return ; }
        ans += (B[2] - A[2]) / B[1];
        puts("BIG");
        printf("%lld\n", ans);
        return ;
    }
    ans += B[2] / B[1];
    B[2] %= B[1];
    Solve();
}

inline int Check()
{
    bool flag = true;
    REP(i, 1, n) if ( A[i] != B[i] ) { flag = false; break ; }
    if ( flag == true ) return 1;
    reverse(B + 1, B + n + 1);
    flag = true;
    REP(i, 1, n) if ( A[i] != B[i] ) { flag = false; break ; }
    reverse(B + 1, B + n + 1);
    if ( flag == true ) return 2;
    return 0;
}

inline int Get()
{
    bool flag = true;
    REP(i, 1, n - 1) if ( B[i] >= B[i + 1] ) { flag = false; break ; }
    if ( flag == true ) return 1;
    flag = true;
    REP(i, 1, n - 1) if ( B[i] <= B[i + 1] ) { flag = false; break ; }
    if ( flag == true ) return 2;
    return 0; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &A[i]);
    REP(i, 1, n) scanf("%lld", &B[i]);
    if ( n == 1 )
    {
        if ( A[1] != B[1] ) puts("IMPOSSIBLE");
        else puts("SMALL\n0");
        return 0;
    }
    while ( 1 ) 
    {
        if ( ans > 3000000 ) break ; 
        if ( Check() ) 
        {
            if ( Check() == 2 ) s += 'R';
            if ( ans > 200000 ) { printf("BIG\n%lld\n", ans); return 0; }
            printf("SMALL\n%lld\n", (int)s.size());
            reverse(s.begin(), s.end());
            cout << s << endl;
            return 0;
        }
        int flag = Get();
        if ( flag == 0 ) { puts("IMPOSSIBLE"); return 0; }
        if ( flag == 1 ) 
        {
            s += 'P'; ++ ans;
            for ( int i = n; i >= 2; -- i ) B[i] = B[i] - B[i - 1];
        }
        if ( flag == 2 ) 
        {
            s += 'R';
            reverse(B + 1, B + n + 1);
        }
    }
    if ( A[1] > A[2] ) swap(A[1], A[2]);
    Solve();
    return 0;
}
