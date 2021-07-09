#ifndef GAME_H
#define GAME_H
#include<bits/stdc++.h>
using namespace std;
int start_game();
void put(int x,int y);
std::vector<int> query(int x);
#define xassert(x) if(!(x)){printf("Invalid\n");exit(0);}
int T;
vector<int> PPP;
namespace test{
	std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count()/100);
	int cnt;
	std::vector<int> vt[25];
	inline bool chkmin(int &a,int b){return a>b?a=b,1:0;}

}
void put(int x,int y){
	using namespace test;
	xassert(1<=x && x<=20);
	xassert(1<=y && y<=100);
	xassert(++cnt<=99);
	int XXX = rnd() % 20 + 1;
	vt[XXX].push_back(cnt);
	if ( cnt == 1 ) T = XXX;
	if ( XXX == T ) PPP.push_back(cnt);
	if ( x == T ) PPP.push_back(y);
	vt[x].push_back(y);
}
std::vector<int> query(int x){
	using namespace test;
	xassert(1<=x && x<=20);
	xassert(++cnt!=100);
	int XXX = rnd() % 20 + 1;
	vt[XXX].push_back(cnt);
	if ( cnt == 1 ) T = XXX;
	if ( XXX == T ) PPP.push_back(cnt);
	sort(vt[x].begin(),vt[x].end());return vt[x];
}
bool make_game(){
	using namespace test;
	PPP.clear();
	for(int i=1;i<=20;++i)vt[i].clear();
	cnt=0;
	int XXX;
	vt[XXX = start_game()].push_back(100);
	xassert(cnt==99);
	int x,y=205;
	for(int i=1;i<=20;++i)if(chkmin(y,vt[i].size())){
		x=i;
	}
	if(!y)return 0;
	for(int i=x+1;i<=20;++i)if(vt[i].size()==y)return 0;
	sort(vt[x].begin(),vt[x].end());
	if ( unique(vt[x].begin(), vt[x].end()) != vt[x].end() && x == XXX )
	{
		sort(vt[x].begin(),vt[x].end());
		cerr << x << " " << XXX <<  " " << T << endl;
		for ( auto i : vt[x] ) printf("%d ", i); puts("");
		for ( auto i : PPP ) printf("%d ", i); puts("");
		cerr << endl;
	}
	vt[x].erase(unique(vt[x].begin(),vt[x].end()),vt[x].end());
	if(vt[x].size()<y)
	{
		return 0;
	}
	if(vt[x].back()!=100)return 0;
	return 1;
}
int main(){
	int s1=0,s2=10000;
	for(int i=1;i<=s2;++i){
		if(make_game())++s1;
	}
	printf("%.2lf%%\n",s1*100./s2);
	return 0;
}
#endif /* !GAME_H */
