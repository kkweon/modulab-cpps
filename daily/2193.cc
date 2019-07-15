// https://www.acmicpc.net/problem/2193
#include <bits/stdc++.h>
using namespace std;

using LL = long long;

LL memo[2][91];

LL go(int prev, int len, int max_len) {
  if (len == max_len) return 1;
  auto& ret = memo[prev][len];
  if (ret != -1) return ret;

  LL count = 0;
  count += go(0, len + 1, max_len);
  if (prev == 0) count += go(1, len + 1, max_len);
  return ret = count;
}

LL get_count(int n) {
  memset(memo, -1, sizeof(memo));
  return go(1, 1, n);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;
  cin >> N;
  cout << get_count(N) << '\n';

  return 0;
}
