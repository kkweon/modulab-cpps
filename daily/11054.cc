#include <bits/stdc++.h>
using namespace std;

int N;
int X[1000];
int INC[1000];
int DEC[1000];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> X[i];

    INC[i] = 1;
    DEC[i] = 1;

    for (int j = 0; j < i; ++j) {
      if (X[j] < X[i] && INC[i] < INC[j] + 1) {
        INC[i] = INC[j] + 1;
      }
    }
  }

  for (int i = N - 2; 0 <= i; --i) {
    for (int j = N - 1; i < j; --j) {
      if (X[i] > X[j] && DEC[i] < DEC[j] + 1) {
        DEC[i] = DEC[j] + 1;
      }
    }
  }

  int max_len = 0;

  for (int i = 0; i < N; ++i) {
    int len = INC[i] + DEC[i] - 1;
    max_len = max(max_len, len);
  }

  cout << max_len << '\n';

  return 0;
}
