#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

const int mod = 1000000007;
struct Mint {
  ll x;
  Mint(ll x = 0) : x((x % mod + mod) % mod) {}
  Mint& operator*=(const Mint& a) {
    (x *= a.x) %= mod;
    return *this ;
  }
  Mint operator*(const Mint& a) const {
    Mint res(*this);
    return res *= a;
  }

  Mint pow(ll t) const {
    if (!t) return 1;
    Mint a = pow(t >> 1);
    a *= a;
    if (t & 1) a *= *this;
    return a;
  }

  ll val() {
    return x;
  }
};

struct P {
  ll x, a;
  P(ll x, ll a) : x(x), a(a) {}
};


int main() {

  ll N, A, B;
  cin >> N >> A >> B;
  vector<P> V;
  rep(i, N) {
    ll a; cin >> a;
    P add(a, 0);
    V.push_back(add);
  }
  Mint ma(A);

  // < : true
  auto comp = [&](const P& s, const P& t) -> bool {
    ll sa = s.a - min(s.a, t.a);
    ll ta = t.a - min(s.a, t.a);
    if (sa == 0 && ta == 0) {
      return s.x < t.x;
    }
    if (sa == 0) {
      // s.x < t.x * A.pow(ta) ?
      ll u = 1;
      rep(o, ta) {
        u *= A;
        if (s.x < t.x * u) return true;
      }
      return false;
    } else {
      // s.x * A.pos(sa) < t.x ?
      ll u = 1;
      rep(o, sa) {
        u *= A;
        if (s.x * u >= t.x) return false;
      }
      return true;
    }
  };

  auto sor = [&]() {
    rep(o, 200) {
      rep(i, N - 1) {
        if (!comp(V[i], V[i + 1])) {
          swap(V[i], V[i + 1]);
        }
      }
    } 
  };

  auto fin = [&]() {
    sor(); 
    for (auto v : V) {
      Mint r(v.x);
      r *= ma.pow(v.a);
      cout << r.val() << "\n";
    }
    exit(0);
  };


  if (A == 1) fin();

  ll cnt = 0;
  while (true) {
    if (cnt == B) fin();
    if (all_of(V.begin(), V.end(), [](P p) {
      return p.a > 0;
    })) {
      break;
    }
    cnt++;   
    int midx = 0;    
    rep(i, N) if (comp(V[i], V[midx])) midx = i;
    V[midx].a++;
  }

  sor();
  ll mo = B - cnt;
  rep(i, N) {
    V[i].a += (mo / N) + (i < mo % N ? 1 : 0);
  }

  fin();


}
