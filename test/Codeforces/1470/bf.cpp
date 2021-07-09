/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年01月06日 星期三 09时37分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, p, a[maxn], b[maxn];

inline int pre(int x) { return x == 1 ? n : x - 1; }

inline int suf(int x) { return x % n + 1; }

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d%d", &n, &k, &p);
    REP(i, 1, n) a[i] = k;
    REP(o, 1, 100)
    {
        REP(i, 1, n) b[i] = 0;
        REP(i, 1, n)
        {
            if ( i != p ) { b[pre(i)] += a[i] / 2; b[suf(i)] += a[i] - (a[i] / 2); }
            else b[suf(i)] += a[i];
        }
        REP(i, 1, n) a[i] = b[i];
        REP(i, 1, n) printf("%d ", a[i]); puts("");
    }
    return 0;
}
