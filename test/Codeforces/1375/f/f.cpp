/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2020年07月07日 星期二 15时22分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

pii a, b, c;

inline void Sort()
{
    if ( a.first > b.first ) swap(a, b);
    if ( a.first > c.first ) swap(a, c);
    if ( b.first > c.first ) swap(b, c);
}

signed main()
{
    cin >> a.first >> b.first >> c.first;
    a.second = 1; b.second = 2; c.second = 3;
    cout << "First" << endl; fflush(stdout);

    Sort();
    cout << c.first - b.first << endl; fflush(stdout);

    int x; cin >> x; 
    while ( x == a.second ) 
    {
        a.first += c.first - b.first; Sort();
        cout << c.first - b.first << endl; fflush(stdout);
        cin >> x;
    }
    if ( x == 0 ) return 0;
    c.first += c.first - b.first;
     
    cout << 2 * c.first - a.first - b.first << endl; fflush(stdout);
    cin >> x; if ( x == 0 ) return 0;
    if ( x == a.second ) a.first += 2 * c.first - a.first - b.first;
    else if ( x == b.second ) b.first += 2 * c.first - a.first - b.first;
    Sort();
    cout << b.first - a.first << endl; fflush(stdout);
    cin >> x; if ( x == 0 ) return 0;
    return 0;
}
