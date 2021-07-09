#include<bits/stdc++.h>
using namespace std;
#define MN 10005
#define INF (1e9+7)
struct bag{
	int f[MN],id;
};
stack<bag>L,R,HH;
int n,w,k,l,r,a[MN],b[MN];
void del(){
	if(L.empty()){
		bag tmp;
		tmp.f[0]=0;
		for(int i=1;i<=w;++i)tmp.f[i]=INF;
		while(!R.empty()){
		//	HH.push(R.top());
//			L.push(R.top());
			int x=R.top().id;
			for(int i=w;i>=a[x];--i)
				tmp.f[i]=min(tmp.f[i],tmp.f[i-a[x]]+b[x]);
			L.push(tmp);
			R.pop();
		}
//		while(!HH.empty()){
//			L.push(HH.top());
//			HH.pop();
//		}
	}
	L.pop();
}
void INS(){
	bag B;
//	cout<<"IIIIIIIIIIIIIIIIIIINS: "<<a[r]<<" "<<b[r]<<endl;
//	if(r>n){puts("SHIT!!!");exit(0);}
	B.f[0]=0;
	if(!R.empty())B=R.top();
	else {
//		cout<<"INSERR! "<<endl;
		for(int i=1;i<=w;++i)B.f[i]=INF;
	}
	bag tmp;
	for(int i=0;i<=w;++i)tmp.f[i]=B.f[i];
	for(int i=w;i>=a[r];--i){
		tmp.f[i]=min(tmp.f[i-a[r]]+b[r],tmp.f[i]);
	}
//	for(int i=0;i<=w;++i)cout<<tmp.f[i]<<" ";
//	cout<<endl;
	tmp.id=r;
	R.push(tmp);
	r++;
}
bool chk(){
	bag A,B;
	A.f[0]=0;B.f[0]=0;
	if(!L.empty())A=L.top();
	else for(int i=1;i<=w;++i)A.f[i]=INF;
	if(!R.empty())B=R.top();
	else for(int i=1;i<=w;++i)B.f[i]=INF;
//	cout<<"This chk: "<<L.size()<<" "<<R.size()<<endl;
	for(int i=0;i<=w;++i){
//		cout<<i<<": "<<A.f[i]<<" "<<B.f[w-i]<<endl;
		if(A.f[i]+B.f[w-i]<=k) return 1;
	//		else cout<<"chk : "<<i<<": "<<A.f[i]<<" "<<B.f[w-i]<<endl;
	}
	return 0;
}
int main(){
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	scanf("%d%d%d",&n,&w,&k);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&a[i],&b[i]);
	l=1;r=1;
	int ans=INF;
	for(l=1;l<=n;++l){	
		if(l>1)del();
//		cout<<"l: "<<l<<endl;
		while(!chk()){
			if(r>n){
				printf("%d",ans==INF?(-1):ans);
				return 0;
			}
			INS();
		}
		ans=min(ans,r-l);
//		cout<<"HI "<<l<<" "<<r<<endl;
	}
	printf("%d",(ans==INF)?(-1):ans);
	return 0;
}


