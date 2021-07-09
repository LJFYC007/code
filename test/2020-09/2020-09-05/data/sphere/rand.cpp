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
int rnd() {
	return rand()%(2001)-1000;
}
//int rnd() {
//	return rand()%(21)-10;
//} 
int Abs(int x) {
	if(x==0 && rnd()&1) return 1; 
	return x>0?x:-x;
} 
int main() {
	srand((unsigned long long)new char + time(0));
	int n=rand()%4+17; cout<<n<<endl;
	for(int i=1;i<=n;++i) cout<<rnd()<<' '<<rnd()<<' '<<rnd()<<' '<<Abs(rnd())<<endl;
	
//	cout<<5<<endl;
//	cout<<0<<' '<<0<<' '<<0<<' '<<200<<endl;
//	cout<<0<<' '<<0<<' '<<0<<' '<<300<<endl;
//	cout<<0<<' '<<0<<' '<<0<<' '<<400<<endl;
//	cout<<502<<' '<<-502<<' '<<502<<' '<<732<<endl;
//	cout<<-502<<' '<<502<<' '<<-502<<' '<<732<<endl;
	
//	cout<<4<<endl;
//	cout<<0<<' '<<100<<' '<<-100<<' '<<200<<endl;
//	cout<<-100<<' '<<100<<' '<<0<<' '<<200<<endl;
//	cout<<300<<' '<<200<<' '<<-100<<' '<<333<<endl;
//	cout<<400<<' '<<-535<<' '<<323<<' '<<444<<endl;
	
	return 0;
}
