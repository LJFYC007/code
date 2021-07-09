/***************************************************************
	File name: dissolution.cpp
	Author: ljfcnyali
	Create time: 2021年01月21日 星期四 09时36分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, A[maxn], B[maxn], f[maxn], g[maxn], ans;

inline int Dis(int x, int y) { return max(abs(A[x] - A[y]), abs(B[x] - B[y])); }

int main()
{
    freopen("dissolution.in", "r", stdin);
    freopen("dissolution.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); A[i] = x + y; B[i] = x - y; } 
    REP(i, 2, n) { g[i] = Dis(i - 1, i); f[i] = f[i - 1] + g[i - 1]; } 
    REP(i, 3, n) 
    {
        int sum = 0;
        for ( int j = i - 1; j >= 2; -- j ) 
        {
            f[i] = max(f[i], f[j] + sum + Dis(j - 1, i));
            sum += g[j];
        }
        cout << f[i] << " ";
    }
    int ans = 0, sum = 0;
    for ( int i = n; i >= 2; -- i ) { ans = max(ans, f[i] + sum); sum += g[i]; } 
    printf("%d\n", ans);
    return 0;
}
