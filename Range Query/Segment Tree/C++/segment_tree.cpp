#include <bits/stdc++.h>
using namespace std;
const int oo  = int(1e9 + 20);

//----------------------------------------------------------------------


template <typename T, class F = function<T(const T&, const T&)>>
class SegmentTree {
    int NEUTRAL;
    int n;
    vector<int> tree;
    F func;
public:
    
    SegmentTree(vector<int> values, int neutral, const F& f) : func(f) {
        NEUTRAL = neutral;
        
        n = values.size();
        tree.resize(n*2);
        // Build
        for (int i=0; i < n; i++){
            tree[n+i] = values[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = func(tree[i*2], tree[i*2+1]);
        }
    }
    
    void update(int index, int value) {
        tree[index+n] = value;
        index = index + n;
        for (int i = index; i > 1; i >>= 1){
            tree[i/2] = func(tree[i], tree[i^1]);
        }
    }
    
    int query(int l, int r) {
        int ans = NEUTRAL;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) {
                ans = func(ans, tree[l++]);
            }
            if (r&1) {
                ans = func(ans, tree[--r]);
            }
        }
        return ans;
    }
};

// Neutral
// Minimum -> oo
// Maximum -> -oo
// Sum     -> 0
// product -> 1

auto main() -> int {
    
    vector<int> values{1, 2, 4, 7, 3, 5, 6};
    
    // usage:
    //  auto func = [&](int i, int j) -> int { return max(i, j); };
    //  SegmentTree<int, decltype(func)> st(values, -oo, func);
    // or:
    SegmentTree<int> st(values, -oo, [&](int x, int y) -> int {return max(x, y);});
    
    cout << st.query(0, 0+1) << endl;
    // 1 -> [0, 1) or [0, 0]
    
    st.update(1, 100);
    
    cout << st.query(0, 4+1) << endl;
    // 100 -> [0, 5) or [0, 4]
    return 0;
}