#include<bits/stdc++.h>
using namespace std; 

template<int m> struct StaticModint{
    using mint = StaticModint;
  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    StaticModint() : _v(0) {}
    template <class T>
    StaticModint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        assert(_v);
        return pow(umod() - 2);
    }

    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs; }
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v; }

    friend ostream &operator<<(ostream &os, mint x) {
        os << x.val();
        return (os);
    }

  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }

};

using Modint998244353 = StaticModint<998244353>;
using Modint1000000007 = StaticModint<1000000007>;

using Mint = Modint1000000007;

template<class T> struct Matrix {
    int n, m;
    vector<vector<T>> M;

    Matrix() : n(0), m(0) { init(); }
    Matrix(int _n, int _m) : n(_n), m(_m) { init(); }
    Matrix(int _n) : n(_n), m(_n) { init(); }

    void init() {
        M.resize(n, vector<T>(m));
    }

    inline const vector<T> &operator[](int k) const { return (M.at(k)); }
    inline vector<T> &operator[](int k) { return (M.at(k)); }

    static Matrix I(int n) {
        Matrix mat(n);
        for(int i = 0; i < n; i++) mat[i][i] = 1;
        return (mat);
    }

    Matrix operator+=(const Matrix &B) {
        assert(n == B.n && m == B.m);
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) (*this)[i][j] += B[i][j];
        return (*this);
    }

    Matrix operator-=(const Matrix &B) {
        assert(n == B.n && m == B.m);
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) (*this)[i][j] -= B[i][j];
        return (*this);
    }

    Matrix operator*=(const Matrix &B) {
        assert(m == B.n);
        m = B.m;
        vector<vector<T>> C(n, vector<T>(B.m, 0));
        for(int i = 0; i < n; i++) for(int j = 0; j < B.m; j++) for(int k = 0; k < B.n; k++) C[i][j] += (*this)[i][k] * B[k][j];
        M.swap(C);
        return (*this);
    }

    Matrix pow(long long k) {
        assert(n == m);
        Matrix B = Matrix::I(n);
        while(k > 0) {
            if(k & 1) B *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        return B;
    }

    Matrix operator+(const Matrix &B) const { return (Matrix(*this) +=B); }
    Matrix operator-(const Matrix &B) const { return (Matrix(*this) -=B); }
    Matrix operator*(const Matrix &B) const { return (Matrix(*this) *=B); }

    friend ostream &operator<<(ostream &os, Matrix &p) {
        for(int i = 0; i < p.n; i++) {
            os << "[";
            for(int j = 0; j < p.m; j++){
                os << p[i][j] << (j == p.m - 1 ? "]\n" : ", ");
            }
        }
        return (os);
    }
};


int main() {

  int N; cin >> N;
  long long K; cin >> K;

  Matrix<Mint> A(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int a; cin >> a;
      A[i][j] = a;
    }
  }

  auto B = A.pow(K);

  Mint ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      ans += B[i][j];
    }
  }

  cout << ans << endl;


}

