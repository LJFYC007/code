/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 18时38分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int n, L, R, now;
struct node
{
    int d, id;
    bool operator < (const node &a) const { return d < a.d; }
} a[maxn];
vector<int> p;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    if ( n == 1 ) { printf("1 2\n"); return 0; }
    REP(i, 1, n) { scanf("%d", &a[i].d); a[i].id = i; }
    sort(a + 1, a + n + 1);
    if ( a[1].d == 1 ) 
    {
        p.push_back(a[1].id * 2 - 1); p.push_back(a[1].id * 2);
        now = 2;
    }
    else
    {
        p.push_back(a[1].id * 2 - 1); p.push_back(a[2].id * 2 - 1);
        p.push_back(a[1].id * 2); p.push_back(a[2].id * 2);
        now = 3;
    }
    while ( now <= n ) 
    {

    }
    return 0;
}
