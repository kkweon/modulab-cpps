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

- Time: O(N log K)
- Space: O(N)

```cpp
class Compare {
 public:
  bool operator()(const ListNode* l, const ListNode* r) const {
    return l->val > r->val;
  }
};
class Solution {
 public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

    for (auto list_node : lists) {
      if (list_node != nullptr) {
        pq.push(list_node);
      }
    }

    ListNode head(-1);
    auto curr = &head;

    while (pq.size()) {
      auto list_node = pq.top();
      pq.pop();
      curr->next = list_node;
      if (list_node->next) {
        pq.push(move(list_node->next));
      }
      curr = curr->next;
    }

    return head.next;
  }
};
```

## Q3. Find Median from Data Stream

- Time: O(log N)
- Space: O(N)

```cpp
class MedianFinder {
 private:
  priority_queue<int> lower;
  priority_queue<int, vector<int>, greater<int>> upper;

 public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
    lower.push(num);
    auto t = lower.top();
    lower.pop();
    upper.push(t);

    if (lower.size() < upper.size()) {
      auto t = upper.top();
      upper.pop();
      lower.push(t);
    }
  }

  double findMedian() {
    if (lower.size() == upper.size()) return 0.5 * (lower.top() + upper.top());
    return lower.top();
  }
};
```

## Q4. Kth Largest Element in an Array

- Time: O(N)
- Space: O(1)

```cpp
class Solution {
 public:
  int findKthLargest(vector<int>& nums, int k) {
    int l = 0, r = static_cast<int>(nums.size()) - 1;
    while (l <= r) {
      auto mid = partition(nums, l, r);
      if (mid == k - 1)
        return nums[mid];
      else if (mid < k - 1)
        l = mid + 1;
      else
        r = mid - 1;
    }
    return -1;
  }

  /**
   * QuickSelect
   */
  int partition(vector<int>& nums, int l, int r) {
    int w_idx = l;
    for (int i = l; i < r; ++i) {
      if (nums[i] > nums[r]) swap(nums[w_idx++], nums[i]);
    }
    swap(nums[w_idx], nums[r]);
    return w_idx;
  }
};
```

## Q5. Two Sum

- Time: O(N)
- Space: O(N)

```rust
use std::collections::HashMap;

impl Solution {
  pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let mut m: HashMap<i32, i32> = HashMap::new();

    for (j, n) in nums.iter().enumerate() {
      if let Some(&i) = m.get(n) {
          return vec![i, j as i32];
      }
      m.insert(target - n, j as i32);
    }

    return Vec::new();
  }
}
```

## Q6. Group Anagrams

- Time: O(NK log k)
- Space: O(NK)

```rust
use std::collections::HashMap;

impl Solution {
  pub fn group_anagrams(strs: Vec<String>) -> Vec<Vec<String>> {
    let mut m: HashMap<String, Vec<String>> = HashMap::new();

    for word in strs {
      let mut chars = word.chars().clone().collect::<Vec<_>>();
      chars.sort();
      let key: String = chars.into_iter().collect::<String>();
      m.entry(key).or_insert_with(Vec::new).push(word);
    }

    m.into_iter().map(|(_, xs)| xs).collect::<Vec<Vec<String>>>()
  }
}
```

## Q7. Subarray Sum Equals K

- Time: O(N)
- Space: O(N)

```rust
use std::collections::HashMap;

impl Solution {
  pub fn subarray_sum(nums: Vec<i32>, k: i32) -> i32 {
    let mut count = 0;
    let mut sum = 0;
    let mut map = HashMap::new();
    map.insert(0, 1);

    for n in nums {
      sum += n;

      if let Some(c) = map.get(&(sum - k)) {
        count += c;
      }

      *map.entry(sum).or_insert(0) += 1;
    }

    count
  }
}
```

## Q8. Palindrome Pairs

- Time: -
- Space: -


## Q9. Copy List with Random Pointer

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
 public:
  Node* copyRandomList(Node* head) {
    auto curr = head;
    while (curr) {
      curr->next = new Node(curr->val, curr->next, nullptr);
      curr = curr->next->next;
    }

    curr = head;
    while (curr) {
      if (curr->random) curr->next->random = curr->random->next;
      curr = curr->next->next;
    }

    Node t(-1, nullptr, nullptr);
    auto t_it = &t;

    curr = head;
    while (curr) {
      t_it->next = move(curr->next);
      curr->next = move(t_it->next->next);

      t_it = t_it->next;
      curr = curr->next;
    }

    return t.next;
  }
};
```

## Q10. Insert Delete GetRandom O(1)

- Time: O(1)
- Space: O(N)

```cpp
class Solution {
 public:
  Node* copyRandomList(Node* head) {
    auto curr = head;
    while (curr) {
      curr->next = new Node(curr->val, curr->next, nullptr);
      curr = curr->next->next;
    }

    curr = head;
    while (curr) {
      if (curr->random) curr->next->random = curr->random->next;
      curr = curr->next->next;
    }

    Node t(-1, nullptr, nullptr);
    auto t_it = &t;

    curr = head;
    while (curr) {
      t_it->next = move(curr->next);
      curr->next = move(t_it->next->next);

      t_it = t_it->next;
      curr = curr->next;
    }

    return t.next;
  }
};
```
