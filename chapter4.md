# Chapter 4

## Q1. K Closest Points to Origin

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
public:
  int dist(const vector<int>& xs) { return xs[0] * xs[0] + xs[1] * xs[1]; }

  vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    if (points.empty()) return {};

    int l = 0, r = points.size() - 1;

    while (l <= r) {
      int mid = partition(points, l, r);
      if (mid == K)
        break;
      else if (mid < K)
        l = mid + 1;
      else
        r = mid - 1;
    }

    return {points.begin(), points.begin() + K};
  }

  int partition(vector<vector<int>>& xs, int l, int r) {
    int w_idx = l;
    for (int i = l; i < r; ++i) {
      if (dist(xs[i]) < dist(xs[r])) swap(xs[w_idx++], xs[i]);
    }
    swap(xs[w_idx], xs[r]);
    return w_idx;
  }
};
```

## Q2. Merge k Sorted Lists

## Q3. Find Median from Data Stream

## Q4. Kth Largest Element in an Array

## Q5. Two Sum

## Q6. Group Anagrams

## Q7. Subarray Sum Equals K

## Q8. Palindrome Pairs

## Q9. Copy List with Random Pointer

## Q10. Insert Delete GetRandom O(1)
