/***************************************************************
	File name: CF1231E.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 19时30分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

string a, b, A, B;
int T, n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        cin >> a >> b;
        A = a; B = b;
        sort(A.begin(), A.end()); sort(B.begin(), B.end());
        if ( A != B ) { puts("-1"); continue ; }
        ans = n;
        REP(x, 0, b.size() - 1)
        {
            int i = x, ret = n;
            REP(j, 0, a.size() - 1)
                if ( i < n && a[j] == b[i] ) { ++ i; -- ret; }
            ans = min(ans, ret);
        }
        printf("%d\n", ans);
    }
    return 0;
}
