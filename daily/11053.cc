#include <bits/stdc++.h>
using namespace std;

int N;
int xs[1000];

int get_longest_increasing_sequence() {

  vector<int> ret;

  for (int i = 0; i < N; ++i) {
    if (ret.empty() || ret.back() < xs[i]) {
      ret.push_back(xs[i]);
    } else {
      auto x = lower_bound(ret.begin(), ret.end(), xs[i]);
      *x = xs[i];
    }
  }

  return static_cast<int>(ret.size());
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  for (int i = 0; i < N; ++i) cin >> xs[i];

  cout << get_longest_increasing_sequence() << '\n';

  return 0;
}
