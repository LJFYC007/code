/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 11时33分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, a[maxn], ans;

inline bool Check()
{
    int sum = 0, Min = 0;
    REP(i, 1, n) { sum += a[i]; Min = min(Min, sum); }
    if ( n - sum + 2 * Min == 2 * k ) 
    {
        REP(i, 1, n) printf("%d ", a[i]); puts("");
        return true;
    }
    return false;
}

inline void DFS(int x)
{
    if ( x == n + 1 ) 
    {
        if ( Check() ) ++ ans;
        return ; 
    }
    a[x] = 1; DFS(x + 1);
    a[x] = -1; DFS(x + 1);
}

int main()
{
    scanf("%d%d", &n, &k);
    DFS(1);
    printf("%d\n", ans);
    return 0;
}
