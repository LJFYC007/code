$$
\sum_{i=1}^n\sum_{j=1}^ngcd(a_i,a_j)\times gcd(i,j)\\
\sum_{d=1}^nd\sum_{i=1}^n\sum_{j=1}^n[gcd(i,j)=d]gcd(a_i,a_j)\\
\sum_{d=1}^nd\sum_{i=1}^{\frac{n}{d}}\sum_{j=1}^{\frac{n}{d}}[gcd(i,j)=1]gcd(a_{id},a_{jd})\\
\sum_{d=1}^nd\sum_{i=1}^{\frac{n}{d}}\sum_{j=1}^{\frac{n}{d}}\sum_{p|i,p|j}\mu(p)gcd(a_{id},a_{jd})\\
\sum_{d=1}^nd\sum_{p=1}^{\frac{n}{d}}\mu(p)\sum_{i=1}^{\frac{n}{pd}}\sum_{j=1}^{\frac{n}{pd}}gcd(a_{ipd},a_{jpd})\\
\sum_{t=1}^n\sum_{d|t}d\times \mu(\frac{t}{d})\sum_{i=1}^{\frac{n}{t}}\sum_{j=1}^{\frac{n}{t}}gcd(a_{it},a_{jt})\\
=\sum_{t=1}^n\phi(t)f(t)
$$

$$
f(t)=\sum_{i=1}^{\frac{n}{t}}\sum_{j=1}^{\frac{n}{t}}gcd(a_{it},a_{jt})\\
\sum_{d=1}^{n}d\sum_{i=1}^{\frac{n}{t}}\sum_{j=1}^{\frac{n}{t}}\sum_{d|p,p|a_{it},p|a_{jt}}\mu(p)\\
\sum_{d=1}^{n}d\sum_{p=1}^{\frac{n}{d}}\mu(p)(\sum_{i\in s}[pd|i])^2\\
\sum_{p=1}^n(\sum_{i\in s}[p|i])^2)\phi(p)
$$

$$
=\sum_{t=1}^n\sum_{p=1}^n\phi(t)\phi(p)(\sum_{i\in s}[p|i])^2)
$$

