#include<bits/stdc++.h>
using namespace std;
#define maxn 1010
#define min_(x,y) ((x)<(y)?(x):(y))
#define inf 0x3f3f3f3f
int h[maxn],n,m,k;
int qx[maxn],qy[maxn];
int ans,reg;
bool flag=1;
inline int findlo(int l,int r){
	int sum=inf;
	for(register int i=l;i<=r;i++){
		sum=min_(sum,h[i]);
	}
	return sum;
}
inline int calc(int xa,int ya,int xb,int yb){
	if(xa==xb)return abs(ya-yb);
	int cxk=findlo(xa,xb);
	return ya+yb-2*cxk+abs(xa-xb);
}
inline int calc2(int xa,int ya,int xb,int yb){
	return abs(xa-xb)+abs(ya-yb);
}
int main(){
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k;
	for(register int i=1;i<=n;i++){
		cin>>h[i];
		if(i==1)reg=h[i];
		if(i!=1 and reg!=h[i])flag=0;
	}
	cin>>m;
	for(register int i=1;i<=m;i++){
		cin>>qx[i]>>qy[i];
	}
	if(flag){
		for(register int i=1;i<=m;i++){
			for(register int j=i+1;j<=m;j++){
				if(calc2(qx[i],qy[i],qx[j],qy[j])<=k)ans++;
			}
		}
		cout<<ans;
		return 0;
	}
	//cout<<"@^#@$@^@$@#&@%$!#~!  "<<m<<endl;
	for(register int i=1;i<=m;i++){
		for(register int j=i+1;j<=m;j++){
			if(calc(qx[i],qy[i],qx[j],qy[j])<=k)ans++;
	//		cout<<i<<" "<<j<<" "<<qx[i]<<" "<<qy[i]<<" "<<qx[j]<<" "<<qy[j]<<" "<<calc(qx[i],qy[i],qx[j],qy[j])<<endl;
		}
	}
	cout<<ans;
	return 0;
}
