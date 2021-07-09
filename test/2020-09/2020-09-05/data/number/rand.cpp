#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}

#include <ctime>
#include <cstdlib>

const int mod=998244353;

int rnd() {
	return (((1ll*rand())<<16) | rand())%mod;
}

int rnd_n(int l,int r) {
	return (((1ll*rand())<<16) | rand())%(r-l+1)+l;
}

int main() {
//	freopen("in.txt","w",stdout);
	srand((unsigned long long)new char + time(0));
//	int n=1000000000,m=5000;
//	int n=30,m=20; 
	int m=rand()%3+99998,n=rnd_n(m,1000000000);
//	int m=rand()%3+43,n=1000000/m;
	cout<<n<<' '<<m<<endl;
	for(int i=0;i<=m;++i) cout<<rnd()<<' '; cout<<endl;
	return 0;
}
