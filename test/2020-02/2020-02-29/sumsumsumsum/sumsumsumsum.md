$$
\sum_{i=1}^k\sum_{j=1}^k\sum_{x=i}^j\sum_{y=x}^jdis(a_x,a_y)\\
f(k)=\sum_{i=1}^k\sum_{j=i}^kdis(a_i,a_j)\times i\times(k-j)\\
f(k+1)=f(k)+\sum_{i=1}^k\sum_{j=i}^kdis(a_i,a_j)\times i+\sum_{i=1}^{k+1}dis(a_i,a_{k+1})\times i\\
f(k+1)=f(k)+\sum_{i=1}^{k+1}\sum_{j=i}^{k+1}dis(a_i,a_j)\times i\\
\sum_{i=1}^{k}(dis[a_i]+dis[a_k]-2dis[LCA(a_i,a_k)])\times i\\
\sum_{i=1}^kdis[a[i]]\times i + dis[a_k]\times ()
$$

