# Chapter 2

## Q1. Remove Duplicates

- Time: O(N)
- Space: O(1)

```cpp
ListNode* deleteDuplicates(ListNode* head) {
  ListNode s(-1);
  auto ret = &s;

  auto curr = head;
  while (curr) {
    if (curr->next && curr->val == curr->next->val) {
      int val = curr->val;
      while (curr && curr->val == val) {
        curr = curr->next;
      }
    } else {
      ret->next = curr;
      ret = ret->next;
      curr = curr->next;
    }
  }

  ret->next = nullptr;
  return s.next;
}
```

## Q2. Kth element from Last

- Time: O(N)
- Space: O(1)

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
  ListNode sent(-1);
  sent.next = head;
  auto s = &sent;
  auto f = &sent;
  for (int i = 0; i <= n && f; ++i) f = f->next;
  while (f) s = s->next, f = f->next;
  auto tmp = s->next;
  if (tmp) s->next = s->next->next;
  delete tmp;
  return sent.next;
}
```

## Q3. Delete Middle Node

- Time: O(1)
- Space: O(1)

```cpp
void deleteNode(ListNode* node) {
  auto temp = node->next;
  *node = *temp;
  delete temp;
}
```

## Q4. Partition List

- Time: O(N)
- Space: O(1)

```cpp
ListNode* partition(ListNode* head, int x) {
  ListNode f(-1), s(-1);
  auto first = &f;
  auto second = &s;

  auto curr = head;
  while (curr) {
    if (curr->val < x) {
      set_and_forward(&first, &curr);
    } else {
      set_and_forward(&second, &curr);
    }
  }
  first->next = s.next;
  return f.next;
}

void set_and_forward(ListNode** node, ListNode** curr) {
  if (!node || !*node) return;
  (*node)->next = *curr;
  (*node) = (*node)->next;

  (*curr) = (*curr)->next;
  (*node)->next = nullptr;
}
```

## Q5. Sum Lists

- Time: O(max(N, M))
- Space: O(max(N, M))

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  int carry = 0;
  ListNode sent(-1);
  auto curr = &sent;

  while (l1 || l2) {
    carry += l1 ? l1->val : 0;
    carry += l2 ? l2->val : 0;
    if (l1) l1 = l1->next;
    if (l2) l2 = l2->next;

    curr->next = new ListNode(carry % 10);
    curr = curr->next;

    carry /= 10;
  }

  if (carry) curr->next = new ListNode(carry);

  return sent.next;
}
```

## Q6. Palindrome

- Time: O(N)
- Space: O(1)

```cpp
bool isPalindrome(ListNode* head) {
  if (!head) return true;
  int n = get_size(head);
  auto fast = head;
  for (int i = 0; i < n / 2 - 1; ++i) {
    fast = fast->next;
  }
  if (n & 1 && 3 <= n) fast = fast->next;
  fast->next = reverse(fast->next);
  auto fast_backup = fast;

  auto slow = head;
  fast = fast->next;

  while (slow && fast) {
    if (slow->val == fast->val) {
      slow = slow->next;
      fast = fast->next;
    } else {
      fast_backup->next = reverse(fast_backup->next);
      return false;
    }
  }
  fast_backup->next = reverse(fast_backup->next);
  return true;
}

int get_size(ListNode* node) {
  if (!node) return 0;
  int size = 0;
  while (node) {
    size++;
    node = node->next;
  }
  return size;
}

ListNode* reverse(ListNode* node) {
  if (!node) return nullptr;
  auto new_head = reverse(node->next);
  if (!new_head) return node;
  node->next->next = node;
  node->next = nullptr;
  return new_head;
}
```

## Q7. Intersection

- Time: O(N)
- Space: O(1)

```cpp
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
  int size1 = get_size(headA);
  int size2 = get_size(headB);
  int diff = abs(size1 - size2);
  if (size1 < size2)
    headB = forward(headB, diff);
  else
    headA = forward(headA, diff);
  while (headA != headB) headA = headA->next, headB = headB->next;
  return headA;
}
int get_size(ListNode* node) {
  if (!node) return 0;
  int c = 0;
  while (node) node = node->next, c++;
  return c;
}
ListNode* forward(ListNode* node, int step) {
  for (int i = 0; i < step && node; ++i) node = node->next;
  return node;
}
```

## Q8. Loop Detection

- Time: O(N)
- Space: O(1)

```cpp
bool hasCycle(ListNode* head) {
  auto slow = head;
  auto fast = head;
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) return true;
  }
  return false;
}
```

## Extra (Array / String)

- Time: Permutation O(N^2 \* N!)
- Space: O(N!)
- Link: [LeetCode](https://leetcode.com/problems/permutations)

```cpp
vector<vector<int>> ret;
vector<vector<int>> permute(vector<int>& nums) {
  go(nums, 0);
  return ret;
}

void go(vector<int>& xs, int idx) {
  if (xs.size() <= idx) {
    ret.push_back(xs);
    return;
  }

  for (int i = idx; i < xs.size(); ++i) {
    swap(xs[idx], xs[i]);
    go(xs, idx + 1);
    swap(xs[idx], xs[i]);
  }
}
```
