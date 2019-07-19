#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int N;
LL X[1000];
LL DP[1000];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  memset(DP, 0, sizeof(DP));
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> X[i];

    DP[i] = X[i];

    for (int j = 0; j < i; ++j) {
      if (X[j] < X[i] && DP[i] < DP[j] + X[i]) {
        DP[i] = DP[j] + X[i];
      }
    }
  }

  auto m = max_element(DP, DP + N);
  cout << *m << '\n';

  return 0;
}
