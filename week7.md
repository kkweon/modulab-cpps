# Week 7

## Q1. Clone Graph

- Time: O(N)
- Space: O(N)

```cpp
class Solution {
 private:
  // orig -> copy
  unordered_map<Node*, Node*> _copied;
  unordered_set<Node*> visited;

 public:
  Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    if (_copied.count(node)) return _copied[node];

    Node* copy = new Node(node->val, {});
    _copied.insert({node, copy});

    auto& original_list = node->neighbors;
    vector<Node*> copy_list;
    for (auto n : original_list) {
      copy_list.push_back(cloneGraph(n));
    }
    copy->neighbors = move(copy_list);

    return _copied[node];
  }
};
```

## Q2. Course Schedule

- Time: O(N^2)
- Space: O(N)

```cpp
class Solution {
 public:
  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<unordered_set<int>> graph(numCourses);
    vector<int> in_degrees(numCourses, 0);

    for (auto& course_preq : prerequisites) {
      auto& course = course_preq[0];
      auto& preq = course_preq[1];
      graph[preq].insert(course);
      in_degrees[course]++;
    }

    for (int i = 0; i < numCourses; ++i) {
      int j = 0;
      for (; j < numCourses; ++j) {
        if (in_degrees[j] == 0) {
          break;
        }
      }

      // didn't find degree = 0
      if (j == numCourses) {
        return false;
      }

      // mark visited
      in_degrees[j] = -1;

      for (auto& next : graph[j]) {
        in_degrees[next]--;
      }
    }

    return true;
  }
};
```

## Q3. Course Schedule II

- Time: O(|V|+|E|)
- Space: O(|V|+|E|)

```cpp
class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<int> ans;
    vector<int> in(numCourses, 0);
    vector<int> adj[numCourses];

    for (auto [course, preq] : prerequisites) {
      in[course]++;
      adj[preq].emplace_back(course);
    }

    queue<int> q;

    for (int i = 0; i < numCourses; ++i) {
      if (in[i] == 0) {
        q.push(i);
      }
    }

    while (!q.empty()) {
      auto t = q.front();
      q.pop();
      ans.emplace_back(t);

      for (auto& n : adj[t]) {
        in[n]--;

        if (in[n] == 0) {
          q.push(n);
        }
      }
    }

    if (ans.size() < numCourses) return {};

    return ans;
  }
};
```

## Q4. Reconstruct Itinerary

- Time: O(N)
- Space: O(N)

```python
from collections import defaultdict


class Solution:
    def findItinerary(self, tickets: List[List[str]]) -> List[str]:
        m = defaultdict(list)

        for from_, to in sorted(tickets, reverse=True):
            m[from_].append(to)

        def dfs(curr):
            ret = []

            while m[curr]:
                next_city = m[curr].pop()
                ret += dfs(next_city)

            ret.append(curr)

            return ret

        return dfs("JFK")[::-1]
```

## Q5. Evaluate Division

- Time: O(n_query x n_node)
- Space: O(n_query x n_node + n_node^2)

```cpp
class Solution {
 private:
  unordered_map<string, unordered_map<string, double>> m;
  unordered_set<string> visited;

 public:
  vector<double> calcEquation(vector<vector<string>>& equations,
                              vector<double>& values,
                              vector<vector<string>>& queries) {
    for (int i = 0; i < equations.size(); ++i) {
      auto& equation = equations[i];

      string& from = equation[0];
      string& to = equation[1];
      auto value = values[i];

      m[from][to] = value;
      m[to][from] = 1 / value;
    }

    vector<double> ret;

    for (auto& query : queries) {
      visited = unordered_set<string>();
      string& from = query[0];
      string& to = query[1];
      ret.push_back(dfs(from, to));
    }

    return ret;
  }

  double dfs(const string& from, const string& to, double acc = 1.0) {
    if (from == to && m.count(from)) return acc;
    for (auto [next, val] : m[from]) {
      if (visited.count(next)) continue;
      visited.insert(next);
      auto v = dfs(next, to, acc * val);
      if (0 < v) return v;
      visited.erase(next);
    }
    return -1.0;
  }
};
```

## Q6. Network Delay Time

- Time: O(N^2)
- Space: O(N)

```cpp
class Solution {
 public:
  int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    vector<int> dist(N + 1, INT_MAX);
    dist[K] = 0;

    for (int i = 0; i < N; ++i) {
      for (auto& u_v_w : times) {
        auto& u = u_v_w[0];
        auto& v = u_v_w[1];
        auto& w = u_v_w[2];

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
        }
      }
    }

    auto m = *max_element(dist.begin() + 1, dist.end());
    return m == INT_MAX ? -1 : m;
  }
};
```

## Q7. Is Graph Bipartite?

- Time: O(N^2)
- Space: O(N)

```cpp
class Solution {
 private:
  const int A = 1;
  const int B = -1;

 public:
  bool isBipartite(vector<vector<int>>& graph) {
    vector<int> colors(graph.size(), 1);

    for (int i = 0; i < graph.size(); ++i) {
      if (colors[i] == 0 && !paint(i, A, colors, graph)) {
        return false;
      }
    }

    return true;
  }

  bool paint(int node, int c, vector<int>& colors, vector<vector<int>>& g) {
    if (colors[node] != 0) return colors[node] == c;
    colors[node] = c;
    auto& next_nodes = g[node];
    for (auto& next_node : next_nodes) {
      if (!paint(next_node, -c, colors, g)) return false;
    }
    return true;
  }
};
```

## Extra (Tree)
