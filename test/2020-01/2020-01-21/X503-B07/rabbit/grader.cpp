#include "rabbit.h"
#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;

ll CntLim;
ll N, K, Rab;

ll RandLL()
{
	return (1ll*rand()<<31) | rand();
}

ll Spawn()
{
	return RandLL() % N + 1;
}

void Play()
{
	int x = rand() % (K + 1);
    Rab = Rab + (rand() % 2 == 0 ? 1 : -1) * x;
}

bool ask(ll l, ll r)
{
	CntLim--;
	if(CntLim < 0)
	{
		cout << "0" << endl;
		cerr << "Too many queries" << endl;
		exit(0);
	}
	if(l==Rab && r==Rab)
	{
		cout << "1" << endl;
        cerr << CntLim << endl;
		exit(0);
	}
	int ret = false;
	if(l<=Rab && Rab<=r) ret = true;
	Play();	
	return ret;
}

signed main()
{
    srand(time(0));
	CntLim = 2048;
	cin >> N >> K;
	Rab = Spawn();
	catch_rabbit(N, K);
	return 0;
}
