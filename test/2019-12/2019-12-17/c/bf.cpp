#include<bits/stdc++.h>
using namespace std;
#define INF 1e18
#define LL long long
struct data{
	int w,v;
	data(int W=0,int V=0){
		w=W;v=V;
	}
	bool friend operator<(data a,data b){
		if(a.w!=b.w)return a.w<b.w;
		return a.v<b.v;
	}
};
deque<data>Q;
multiset<data>S;
#define itset multiset<data>::iterator
int m,Mod,w,v;
LL tmp[505],f[505];
char ch[5];
namespace lie{
#define Itset multiset<int>::iterator
	multiset<int>S[2];
	LL sum[2];
	void work(){
		for(int i=1;i<=m;++i){
			memset(ch,0,sizeof(ch));
			scanf("%s",ch+1);
			if(ch[1]=='I'){
				scanf("%d%d",&w,&v);
				w%=2;
				if(ch[2]=='F')Q.push_front(data(w,v));
				else Q.push_back(data(w,v));
				S[w].insert(v);
				sum[w]+=v;
			}
			if(ch[1]=='D'){
				data w;
				if(ch[2]=='F'){
					w=Q.front();Q.pop_front();
				}
				else {w=Q.back();Q.pop_back();}
				Itset it=S[w.w].lower_bound(w.v);
				S[w.w].erase(it);
				sum[w.w]-=w.v;
			}
			if(ch[1]=='Q'){
				LL ans=0;
				int l,r;
				scanf("%d%d",&l,&r);
				if(l==0){
					if(S[1].size()%2==0) ans=max(ans,sum[0]+sum[1]);
					else ans=max(ans,sum[0]+sum[1]-(*S[1].begin()));
				}
				if(r==1){
					if(S[1].size()%2==1) ans=max(ans,sum[0]+sum[1]);
						else ans=max(ans,sum[0]+sum[1]-(*S[1].begin()));
				}
				printf("%lld\n",ans);
			}
		}
	}
}
int main(){
    freopen("c.in", "r", stdin);
    freopen("c1.out", "w", stdout);
	int rub;
	scanf("%d",&rub);
	scanf("%d%d",&m,&Mod);
	if(Mod==2){
		lie::work();
		return 0;
	}
	memset(f,-0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=m;++i){
		memset(ch,0,sizeof(ch));
		scanf("%s",ch+1);
		if(ch[1]=='I'){
			scanf("%d%d",&w,&v);
			if(ch[2]=='F')Q.push_front(data(w,v));
			else Q.push_back(data(w,v));
			S.insert(data(w,v));
			for(int i=0;i<Mod;++i){
				tmp[i]=f[i];
			}
			for(int i=0;i<Mod;++i){
				f[(i+w)%Mod]=max(f[(i+w)%Mod],tmp[i]+(LL)v);
			}
			//out();
		}
		if(ch[1]=='D'){
			data w;
			if(ch[2]=='F'){
				w=Q.front();Q.pop_front();
			}
			else {w=Q.back();Q.pop_back();}
			itset it=S.lower_bound(w);
			S.erase(it);
			for(int i=0;i<Mod;++i){
				f[i]=-INF;
			}
			f[0]=0;
			for(itset it=S.begin();it!=S.end();++it){
				int w=(*it).w,v=(*it).v;
				for(int i=0;i<Mod;++i){
					tmp[i]=f[i];
				}
				for(int i=0;i<Mod;++i)
					f[(i+w)%Mod]=max(f[(i+w)%Mod],tmp[i]+(LL)v);
				for(int i=0;i<Mod;++i)
					f[i]=max(f[i],tmp[i]);
			}
		}
		if(ch[1]=='Q'){
			int l,r;
			scanf("%d%d",&l,&r);
			LL ans=-1;
			for(int j=l;j<=r;++j)
				ans=max(ans,f[j]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
