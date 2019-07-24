#include <bits/stdc++.h>
using namespace std;

int N, X[100000];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;

  int max_sum = numeric_limits<int>::min();

  for (int i = 0; i < N; ++i)  {
    cin >> X[i];
    max_sum = max({ max_sum, X[i], max_sum + X[i] });
  }

  cout << max_sum << '\n';

  return 0;
}
