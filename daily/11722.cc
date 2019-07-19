#include <bits/stdc++.h>
using namespace std;

int N;
int X[1000];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  vector<int> ret;
  for (int i = 0; i < N; ++i)  {
    cin >> X[i];

    if (ret.empty() || ret.back() > X[i]) {
      ret.push_back(X[i]);
    } else {
      auto l = lower_bound(ret.begin(), ret.end(), X[i], [](int x, int y) {
          return x > y;
          });
      *l = X[i];
    }
  }

  cout << ret.size() << '\n';

  return 0;
}
