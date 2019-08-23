# Week 5

## Q1. Serialize and Deserialize Binary Tree

- Time: O(N)
- Space: O(N)

```python
class Codec:
    def serialize(self, root):
        """Encodes a tree to a single string."""
        ret = []

        def helper(node):
            if not node:
                ret.append("null")
                return
            ret.append(str(node.val))
            helper(node.left)
            helper(node.right)

        helper(root)

        return ",".join(ret)


    def deserialize(self, data):
        """Decodes your encoded data to tree."""
        data = data.split(",")
        i = 0

        def go():
            nonlocal i
            v = data[i]
            i += 1
            if v == "null":
                return None
            node = TreeNode(int(v))
            node.left = go()
            node.right = go()
            return node

        return go()
```

## Q2. Binary Tree Maximum Path Sum

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
private:
  int max_val = INT_MIN;

public:
  int maxPathSum(TreeNode* root) {
    get_sum(root);
    return max_val;
  }

  int get_sum(TreeNode* root) {
    if (!root) return INT_MIN;
    auto l_sum = max(0, get_sum(root->left));
    auto r_sum = max(0, get_sum(root->right));
    max_val = max(max_val, l_sum + root->val + r_sum);
    return max(l_sum + root->val, r_sum + root->val);
  }
};
```

## Q3. Binary Tree Zigzag Level Order Traversal

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> q;
    q.push(root);
    bool left_to_right = true;

    vector<vector<int>> ret;

    while (q.size()) {
      queue<TreeNode*> next_q;
      vector<int> curr;
      while (q.size()) {
        auto node = q.front();
        q.pop();
        curr.emplace_back(node->val);

        if (node->left) next_q.push(node->left);
        if (node->right) next_q.push(node->right);
      }

      if (!left_to_right) {
        reverse(curr.begin(), curr.end());
      }
      ret.push_back(curr);
      left_to_right = !left_to_right;
      q = next_q;
    }

    return ret;
  }
};
```

## Q4. Validate Binary Search Tree

- Time: O(N)
- Space: O(N)

```go
func isValidBST(root *TreeNode) bool {
    if root == nil {
        return true
    }
    return check(root, math.MinInt64, math.MaxInt64)
}

func check(node *TreeNode, lower, upper int64) bool {
    if node == nil {
        return true
    }

    val := int64(node.Val)

    if !(lower < val && val < upper) {
        return false
    }

    return check(node.Left, lower, val) && check(node.Right, val, upper)
}
```

## Q5. Serialize and Deserialize BST

- Time: O(N)
- Space: O(N)

```cpp
class Codec {
public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    string ret;
    go(root, ret);
    // remove final space
    if (ret.size()) ret.pop_back();
    return ret;
  }

  void go(TreeNode* node, string& ret) {
    if (!node) return;
    ret += to_string(node->val);
    ret.push_back(' ');
    go(node->left, ret);
    go(node->right, ret);
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    istringstream ss(data);
    string token;

    queue<int> q;

    while (getline(ss, token, ' ')) {
      q.push(stoi(token));
    }

    return build_node(q);
  }

  TreeNode* build_node(queue<int>& q) {
    if (q.empty()) return nullptr;
    auto val = q.front();
    q.pop();
    queue<int> next_q;
    while (q.size() && q.front() < val) {
      next_q.push(q.front());
      q.pop();
    }
    auto node = new TreeNode(val);
    node->left = build_node(next_q);
    node->right = build_node(q);
    return node;
  }
};
```

## Q6. Binary Tree Right Side View

- Time: O(N)
- Space; O(N)

```cpp
class Solution {
public:
  vector<int> rightSideView(TreeNode\* root) {
    if (!root) return {};
    vector<int> ret;

    queue<TreeNode*> q;
    q.push(root);

    while (q.size()) {
      queue<TreeNode*> next_q;
      int val;
      while (q.size()) {
        auto node = q.front();
        q.pop();
        val = node->val;

        if (node->left) next_q.push(node->left);
        if (node->right) next_q.push(node->right);
      }
      q = next_q;
      ret.push_back(val);
    }

    return ret;
  }
};
```

## Q7. Lowest Common Ancestor of a Binary Tree

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    auto left = lowestCommonAncestor(root->left, p, q);
    auto right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
  }
};
```

## Q8. Symmetric Tree

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
public:
  bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return isSymmetricHelper(root->left, root->right);
  }
  bool isSymmetricHelper(TreeNode* l, TreeNode* r) {
    if (!l || !r) return l == r;
    if (l->val != r->val) return false;
    return isSymmetricHelper(l->left, r->right) &&
           isSymmetricHelper(l->right, r->left);
  }
};
```
