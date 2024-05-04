#include<bits/stdc++.h>
using namespace std; 


int main() {
  
  int H, W; std::cin >> H >> W;
  vector<string> C(H);
  for (int i = 0; i < H; i++) {
    cin >> C[i];
  }

  for (int w = 0; w < W; w++) {
    int x = 0;
    for (int h = 0; h < H; h++) {
      x += (C[h][w] == '#');
    }
    cout << x << " \n"[w + 1 == W];
  }
}
