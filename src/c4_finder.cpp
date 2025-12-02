#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <array>
#include <algorithm>

using namespace std;

array<int,4> canonical_cycle(const array<int,4>& cyc) {
  vector<int> v(cyc.begin(), cyc.end());

  int n = 4;
  int pos_min = 0;
  for (int i = 1; i < n; ++i) {
    if (v[i] < v[pos_min]) pos_min = i;
  }

  vector<int> rot(4);
  for (int i = 0; i < n; ++i) {
    rot[i] = v[(pos_min + i) % n];
  }

  vector<int> rev(4);
  rev[0] = rot[0];
  rev[1] = rot[3];
  rev[2] = rot[2];
  rev[3] = rot[1];

  vector<int> best = rot;
  if (rev < best) best = rev;

  return {best[0], best[1], best[2], best[3]};
}

int main() {
  vector<string> vertices = {
    "x", "a", "b", "c", "d",
    "a_1", "a_2", "a_3",
    "b_1", "b_2", "b_3",
    "c_1", "c_2", "c_3",
    "d_1", "d_2", "d_3"
  };

  int n = (int)vertices.size();

  map<string,int> idx;
  for (int i = 0; i < n; ++i) {
    idx[vertices[i]] = i;
  }

  vector<pair<string,string>> edge_list = {
    {"x", "a"}, {"x", "b"}, {"x", "c"}, {"x", "d"},

    {"a", "a_1"}, {"a", "b_3"}, {"a", "d_2"},
    {"b", "b_1"}, {"b", "c_3"}, {"b", "a_2"},
    {"c", "c_1"}, {"c", "d_3"}, {"c", "b_2"},
    {"d", "d_1"}, {"d", "a_3"}, {"d", "c_2"},

    {"a_1", "a_2"}, {"a_1", "a_3"}, {"a_2", "a_3"},
    {"b_1", "b_2"}, {"b_1", "b_3"}, {"b_2", "b_3"},
    {"c_1", "c_2"}, {"c_1", "c_3"}, {"c_2", "c_3"},
    {"d_1", "d_2"}, {"d_1", "d_3"}, {"d_2", "d_3"},
  };

  vector<vector<bool>> adj(n, vector<bool>(n, false));
  for (auto &e : edge_list) {
    int u = idx[e.first];
    int v = idx[e.second];
    adj[u][v] = true;
    adj[v][u] = true;
  }

  auto has_edge = [&](int u, int v) {
    return adj[u][v];
  };

  set<array<int,4>> cycles4;

  for (int a = 0; a < n; ++a) {
    for (int b = a + 1; b < n; ++b) {
      for (int c = b + 1; c < n; ++c) {
        for (int d = c + 1; d < n; ++d) {
          array<int,4> quad = {a, b, c, d};
          sort(quad.begin(), quad.end()); // just to start from some order

          do {
            int v0 = quad[0];
            int v1 = quad[1];
            int v2 = quad[2];
            int v3 = quad[3];

            // Check edges v0-v1, v1-v2, v2-v3, v3-v0
            if (has_edge(v0, v1) &&
              has_edge(v1, v2) &&
              has_edge(v2, v3) &&
              has_edge(v3, v0)) {

              array<int,4> cyc = {v0, v1, v2, v3};
              auto canon = canonical_cycle(cyc);
              cycles4.insert(canon);
            }
          } while (next_permutation(quad.begin(), quad.end()));
        }
      }
    }
  }

  // 5) Output result
  if (cycles4.empty())
    cout << "No 4-cycles (C4) found in this graph.\n";
  else {
    cout << "Found " << cycles4.size() << " distinct 4-cycles:\n";
    for (const auto &cyc : cycles4) {
      cout << vertices[cyc[0]] << " - "
        << vertices[cyc[1]] << " - "
        << vertices[cyc[2]] << " - "
        << vertices[cyc[3]] << " - "
        << vertices[cyc[0]] << "\n";
    }
  }

  return 0;
}

