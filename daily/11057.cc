// https://www.acmicpc.net/problem/11057
#include <bits/stdc++.h>
using namespace std;

int memo[10][1001];
const int MOD = 1e4 + 7;

int go(int prev, int len, int max_len) {
  if (len == max_len) return 1;

  auto& ret = memo[prev][len];
  if (ret != -1) return ret;

  int count = 0;
  for (int i = prev; i <= 9; ++i) {
    count += go(i, len + 1, max_len);
    count %= MOD;
  }

  return ret = count;
}

int get_count(int n) {
  memset(memo, -1, sizeof(memo));
  int count = 0;
  for (int i = 0; i <= 9; ++i) {
    count += go(i, 1, n);
    count %= MOD;
  }
  return count;
}

int main() {
  int N;
  cin >> N;
  cout << get_count(N) << '\n';
  return 0;
}
