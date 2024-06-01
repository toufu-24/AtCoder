#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

template <class T>
struct PersistentSegmentTree
{
    struct Node
    {
        T sum;
        Node *left, *right;
        Node(T sum) : sum(sum), left(nullptr), right(nullptr) {}
        Node(Node *left, Node *right) : left(left), right(right), sum(0)
        {
            if (left)
                sum += left->sum;
            if (right)
                sum += right->sum;
        }
    };

    Node *build(const vector<T> &data, int l, int r)
    {
        if (l + 1 == r)
            return new Node(data[l]);
        int m = (l + r) / 2;
        return new Node(build(data, l, m), build(data, m, r));
    }

    T query(Node *node, int l, int r, int x, int y)
    {
        if (!node || y <= l || r <= x)
            return 0;
        if (x <= l && r <= y)
            return node->sum;
        int m = (l + r) / 2;
        return query(node->left, l, m, x, y) + query(node->right, m, r, x, y);
    }

    Node *update(Node *node, int l, int r, int x, int y, T val)
    {
        if (!node || y <= l || r <= x)
            return node;
        if (x <= l && r <= y)
        {
            T total = (r - l) * val; // Here assuming uniform value, customize as needed
            return new Node(total);
        }
        int m = (l + r) / 2;
        return new Node(update(node->left, l, m, x, y, val), update(node->right, m, r, x, y, val));
    }

    int n;
    Node *root;

    PersistentSegmentTree(vector<T> &data)
    {
        n = data.size();
        root = build(data, 0, n);
    }

    T query(int l, int r)
    {
        return query(root, 0, n, l, r);
    }

    void update(int l, int r, T val)
    {
        root = update(root, 0, n, l, r, val);
    }
};

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);

    PersistentSegmentTree<int> seg(A);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        // 右側に対して / A[i] する
        seg.update(i + 1, N, A[i]);

        ans += seg.query(i + 1, N);

        // バージョンを戻す
        seg.update(i + 1, N, 1);
    }
}