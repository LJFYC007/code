/***************************************************************
	File name: escape.cpp
	Author: ljfcnyali
	Create time: 2020年04月19日 星期日 13时01分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3010;
const int INF = 1e9;
const long double eps = 1e-12;

int n, L, A[maxn], B[maxn], C[maxn];
long double W[maxn], f[maxn];

inline bool Check(long double x)
{
    REP(i, 1, n) W[i] = A[i] - B[i] * x;
    REP(i, 1, n) f[i] = -INF;
    REP(i, 1, n)
    {
        f[i] = max(f[i], f[i - 1] + W[i]);
        int Max = 0, pos = 0;
        int Maxx = f[i], Pos = -1;
        for ( int j = i; j >= 1; -- j ) 
        {
            if ( i - j + 1 > L ) break ; 
            if ( C[j] > Max ) { Max = C[j]; pos = j; }
            f[i] = max(f[i], f[j - 1] + W[pos]);
            if ( f[j - 1] + W[pos] > Maxx ) { Maxx = f[j - 1] + W[pos]; Pos = j; }
        }
    }
    if ( f[n] >= 0 ) return true;
    return false;
}

signed main()
{
    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);
    scanf("%lld%lld", &n, &L);
    REP(i, 1, n) scanf("%lld%lld%lld", &A[i], &B[i], &C[i]); 
    long double L = 0, R = INF, ans = 0;
    REP(i, 1, 100)
    {
        long double Mid = (L + R) / 2.0;
        if ( Check(Mid) ) { L = Mid + eps; ans = Mid; }
        else R = Mid - eps;
    }
    cout << setprecision(9) << scientific;
    cout << ans << endl;
    return 0;
}
