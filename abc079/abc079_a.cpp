#include<bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cin >> S; // 入力は数字っぽいけど、文字列で受け取っちゃう
    // Sは4文字からなる文字列で、前からi番目の文字はS[i]

    if ((S[0] == S[1] && S[1] == S[2]) || (S[1] == S[2] && S[2] == S[3])) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

}