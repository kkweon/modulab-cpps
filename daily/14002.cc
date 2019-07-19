#include <bits/stdc++.h>
using namespace std;

int N;
int X[1000];
vector<int> L[1000];

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> X[i];

    for (int j = 0; j < i; ++j) {
      if (X[j] < X[i] && L[i].size() < L[j].size() + 1) {
        L[i] = L[j];
      }
    }

    L[i].push_back(X[i]);
  }

  const auto& it =
      max_element(L, L + N, [](const vector<int>& xs, const vector<int>& ys) {
        return xs.size() < ys.size();
      });

  cout << it->size() << '\n';
  copy(it->begin(), it->end(), ostream_iterator<int>(cout, " "));
  cout << '\n';

  return 0;
}
