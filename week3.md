# Week 3

## Q1. Trapping Rain Water

- Time: O(N)
- Space: O(1)

```cpp
int trap(vector<int>& height) {
  int left = 0, left_max = 0;
  int right = height.size() - 1, right_max = 0;

  int area = 0;

  while (left < right) {
    if (height[left] < height[right]) {
      left_max = max(left_max, height[left]);
      area += max(left_max - height[left], 0);
      ++left;
    } else {
      right_max = max(right_max, height[right]);
      area += max(right_max - height[right], 0);
      --right;
    }
  }

  return area;
}
```

## Q2. Valid Parentheses

- Time: O(N)
- Space: O(N)

```cpp
bool isValid(string s) {
  stack<char> st;
  unordered_map<char, char> pp = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

  for (auto& c : s) {
    if (pp.count(c)) {
      // open
      st.push(c);
    } else {
      // close
      if (st.empty() || pp[st.top()] != c) return false;
      st.pop();
    }
  }

  return st.empty();
}
```

## Q3. Odd Even Jump

- Time: O(NlogN)
- Space: O(N)

```cpp
int oddEvenJumps(vector<int>& A) {
  int N = A.size();

  // value -> index
  map<int, int> m;
  m[A.back()] = N - 1;

  // Returns (can jump to j) where A[i] <= A[j]
  vector<bool> odd(N, false);
  // Returns (can jump to j) where A[i] >= A[j]
  vector<bool> even(N, false);

  odd.back() = true;
  even.back() = true;

  for (int i = N - 2; 0 <= i; --i) {
    auto lo = m.lower_bound(A[i]);
    auto hi = m.upper_bound(A[i]);

    if (lo != m.end()) {
      // find odd jump index
      odd[i] = even[lo->second];
    }

    if (hi != m.begin()) {
      // find even jump index
      even[i] = odd[(--hi)->second];
    }

    m[A[i]] = i;
  }

  return accumulate(odd.begin(), odd.end(), 0);
}
```

## Q4. Basic Calculator

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
 public:
  int calculate(string s) {
    stack<int> nums;

    int result = 0;
    int num = 0;

    int sign = 1;

    for (auto& c : s) {
      if (std::isdigit(c)) {
        num = num * 10 + static_cast<int>(c - '0');
      } else if (c == '+') {
        result += sign * num;
        num = 0;
        sign = 1;
      } else if (c == '-') {
        result += sign * num;
        num = 0;
        sign = -1;
      } else if (c == '(') {
        nums.push(result);
        nums.push(sign);

        result = 0;
        sign = 1;
      } else if (c == ')') {
        result += sign * num;

        auto _sign = nums.top();
        nums.pop();
        auto _final_result = nums.top();
        nums.pop();

        result = _final_result + _sign * result;
        num = 0;
      }
    }

    if (num != 0) {
      result += sign * num;
    }

    return result;
  }

 private:
  stack<char> m_ops;
  stack<int> m_nums;
};
```

## Q5. Decode String

- Time: O(N)
- Space: O(N)

```cpp
string decodeString(const string& s, int& i) {
  if (s.size() <= i) return "";
  string ans;

  while (i < s.size() && s[i] != ']') {
    if (!isdigit(s[i])) {
      ans.push_back(s[i++]);
    } else {
      int count = 0;
      while (i < s.size() && isdigit(s[i])) {
        count = 10 * count + (s[i++] - '0');
      }

      i++;
      string temp{move(decodeString(s, i))};
      while (count-- > 0) {
        ans += temp;
      }
      i++;
    }
  }

  return ans;
}

string decodeString(string s) {
  string ans;
  int p = 0;
  return decodeString(s, p);
}
```

## Q6. Stack Min

- Time: O(1)
- Space: O(N)

```cpp
class MinStack {
 public:
  /** initialize your data structure here. */
  MinStack() {}

  void push(int x) {
    if (x <= m_min) {
      m_s.push(m_min);
      m_min = x;
    }
    m_s.push(x);
  }

  void pop() {
    auto t = m_s.top();
    m_s.pop();
    if (t == m_min) {
      m_min = m_s.top();
      m_s.pop();
    }
  }

  int top() { return m_s.top(); }

  int getMin() { return m_min; }

 private:
  stack<int> m_s;
  int m_min = INT_MAX;
};
```

## Q7. Queue via Stacks

- Time: O(1)
- Space: O(N)

```cpp
class MyQueue {
 private:
  stack<int> s1;
  stack<int> s2;

 public:
  /** Initialize your data structure here. */
  MyQueue() {}

  /** Push element x to the back of queue. */
  void push(int x) { s1.push(x); }

  /** Removes the element from in front of queue and returns that element. */
  int pop() {
    auto t = peek();
    s2.pop();
    return t;
  }

  /** Get the front element. */
  int peek() {
    if (s2.empty()) {
      while (s1.size()) {
        s2.push(s1.top());
        s1.pop();
      }
    }
    return s2.top();
  }

  /** Returns whether the queue is empty. */
  bool empty() { return s1.empty() && s2.empty(); }
};
```
## Q8. Task Scheduler

- Time: O(N)
- Space: O(1)

```python
from collections import Counter


class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        """
        A X X A X X A

        A A A B, n = 2
        A B X A X X A

        A A A B B B, n = 2
        A X X A X X A
        A B X A B X A B
        """
        d = Counter()

        max_ = 0
        max_n = 0

        for t in tasks:
            d[t] += 1
            if max_ < d[t]:
                max_ = d[t]
                max_n = 1
            elif d[t] == max_:
                max_n += 1

        n_idle = (n - max_n + 1) * (max_ - 1) - (len(tasks) - max_n * max_)
        return len(tasks) + max(0, n_idle)
```

## Extra (Linked List)



