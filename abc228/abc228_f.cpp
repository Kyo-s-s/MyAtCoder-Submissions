#include<bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, n) for (ll i = 0; i < (n); i++)

template< class T >
struct CumulativeSum2D {
  vector< vector< T > > data;

  CumulativeSum2D(int W, int H) : data(W + 1, vector< T >(H + 1, 0)) {}

  void add(int x, int y, T z) {
    ++x, ++y;
    if(x >= data.size() || y >= data[0].size()) return;
    data[x][y] += z;
  }

  void build() {
    for(int i = 1; i < data.size(); i++) {
      for(int j = 1; j < data[i].size(); j++) {
        data[i][j] += data[i][j - 1] + data[i - 1][j] - data[i - 1][j - 1];
      }
    }
  }

  T query(int sx, int sy, int gx, int gy) const {
    return (data[gx][gy] - data[sx][gy] - data[gx][sy] + data[sx][sy]);
  }
};

template<typename T> class SparseTable_2D {
private:
    const int R, C;
    vector<int> LogTable;
    T**** Table;
public:
    SparseTable_2D(const vector<vector<T> >& v) : R((int)v.size()), C((int)v[0].size()), LogTable(max(R, C) + 1){
        for(int i = 2; i <= max(R, C); ++i){
            LogTable[i] = LogTable[i >> 1] + 1;
        }
        Table = new T***[LogTable[R] + 1];
        for(int k = 0; k <= LogTable[R] ; ++k){
            Table[k] = new T**[LogTable[C] + 1];
            for(int l = 0; l <= LogTable[C]; ++l){
                Table[k][l] = new T*[R];
                for(int i = 0; i < R; ++i){
                    Table[k][l][i] = new T[C];
                }
            }
        }
        for(int i = 0; i < R; ++i){
            for(int j = 0; j < C; ++j){
                Table[0][0][i][j] = v[i][j];
            }
        }
        for(int k = 1; (1 << k) <= R; ++k){
            for(int i = 0; i + (1 << k) <= R; ++i){
                for(int j = 0; j < C; ++j){
                    Table[k][0][i][j] = max(Table[k - 1][0][i][j], Table[k - 1][0][i + (1 << (k - 1))][j]);
                }
            }
        }
        for(int k = 0; (1 << k) <= R; ++k){
            for(int l = 1; (1 << l) <= C; ++l){
                for(int i = 0; i + (1 << k) <= R; ++i){
                    for(int j = 0; j + (1 << l) <= C; ++j){
                        Table[k][l][i][j] = max(Table[k][l - 1][i][j], Table[k][l - 1][i][j + (1 << (l - 1))]);
                    }
                }
            }
        }
    }
    ~SparseTable_2D(){
        for(int i = 0; i <= LogTable[R]; ++i){
            for(int j = 0; j <= LogTable[C]; ++j){
                for(int k = 0; k < R; ++k){
                    delete[] Table[i][j][k];
                }
                delete[] Table[i][j];
            }
            delete[] Table[i];
        }
        delete[] Table;
    }
    T query(const int lx, const int ly, const int rx, const int ry){
        const int kx = LogTable[rx - lx];
        const int ky = LogTable[ry - ly];
        return max({Table[kx][ky][lx][ly], Table[kx][ky][rx - (1 << kx)][ly], Table[kx][ky][lx][ry - (1 << ky)], Table[kx][ky][rx - (1 << kx)][ry - (1 << ky)]});
    }
};

int main() {

  ll H, W, h1, w1, h2, w2; 
  cin >> H >> W >> h1 >> w1 >> h2 >> w2;
  vector<vector<ll>> A(H, vector<ll>(W));
  CumulativeSum2D<ll> cs(H, W);
  rep(h, H) rep(w, W) {
    cin >> A[h][w];
    cs.add(h, w, A[h][w]);
  }

  cs.build();

  h2 = min(h1, h2);
  w2 = min(w1, w2);
  
  vector<vector<ll>> T(H, vector<ll>(W, 0));
  rep(h, H - h2 + 1) rep(w, W - w2 + 1) {
    T[h][w] = cs.query(h, w, h + h2, w + w2);
  }

  SparseTable_2D st(T);
  h2 = min(h1, h2);
  w2 = min(w1, w2);
  
  ll ans = 0;
  rep(h, H - h1 + 1) rep(w, W - w1 + 1) {
    ll black = cs.query(h, w, h + h1, w + w1);
    ll white = st.query(h, w, h + h1 - h2 + 1, w + w1 - w2 + 1);
    ans = max(ans, black - white);
  }

  cout << ans << endl;

}
