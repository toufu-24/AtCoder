// I use the following code as a library.
// https://github.com/gishi523/kd-tree

// MIT License

// Copyright (c) 2017 gishi523

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
#ifndef __KDTREE_H__
#define __KDTREE_H__

#include <vector>
#include <numeric>
#include <algorithm>
#include <exception>
#include <functional>

namespace kdt {
/** @brief k-d tree class.
 */
template <class PointT>
class KDTree {
  public:
    /** @brief The constructors.
     */
    KDTree() : root_(nullptr) {};
    KDTree(const std::vector<PointT> &points) : root_(nullptr) { build(points); }

    /** @brief The destructor.
     */
    ~KDTree() { clear(); }

    /** @brief Re-builds k-d tree.
     */
    void build(const std::vector<PointT> &points) {
        clear();

        points_ = points;

        std::vector<int> indices(points.size());
        std::iota(std::begin(indices), std::end(indices), 0);

        root_ = buildRecursive(indices.data(), (int)points.size(), 0);
    }

    /** @brief Clears k-d tree.
     */
    void clear() {
        clearRecursive(root_);
        root_ = nullptr;
        points_.clear();
    }

    /** @brief Validates k-d tree.
     */
    bool validate() const {
        try {
            validateRecursive(root_, 0);
        } catch (const Exception &) {
            return false;
        }

        return true;
    }

    /** @brief Searches the nearest neighbor.
     */
    int nnSearch(const PointT &query, double *minDist = nullptr) const {
        int guess;
        double _minDist = std::numeric_limits<double>::max();

        nnSearchRecursive(query, root_, &guess, &_minDist);

        if (minDist)
            *minDist = _minDist;

        return guess;
    }

    /** @brief Searches k-nearest neighbors.
     */
    std::vector<int> knnSearch(const PointT &query, int k) const {
        KnnQueue queue(k);
        knnSearchRecursive(query, root_, queue, k);

        std::vector<int> indices(queue.size());
        for (size_t i = 0; i < queue.size(); i++)
            indices[i] = queue[i].second;

        return indices;
    }

    /** @brief Searches neighbors within radius.
     */
    std::vector<int> radiusSearch(const PointT &query, double radius) const {
        std::vector<int> indices;
        radiusSearchRecursive(query, root_, indices, radius);
        return indices;
    }

  private:
    /** @brief k-d tree node.
     */
    struct Node {
        int idx;       //!< index to the original point
        Node *next[2]; //!< pointers to the child nodes
        int axis;      //!< dimension's axis

        Node() : idx(-1), axis(-1) { next[0] = next[1] = nullptr; }
    };

    /** @brief k-d tree exception.
     */
    class Exception : public std::exception {
        using std::exception::exception;
    };

    /** @brief Bounded priority queue.
     */
    template <class T, class Compare = std::less<T>>
    class BoundedPriorityQueue {
      public:
        BoundedPriorityQueue() = delete;
        BoundedPriorityQueue(size_t bound) : bound_(bound) { elements_.reserve(bound + 1); };

        void push(const T &val) {
            auto it = std::find_if(std::begin(elements_), std::end(elements_),
                                   [&](const T &element) { return Compare()(val, element); });
            elements_.insert(it, val);

            if (elements_.size() > bound_)
                elements_.resize(bound_);
        }

        const T &back() const { return elements_.back(); };
        const T &operator[](size_t index) const { return elements_[index]; }
        size_t size() const { return elements_.size(); }

      private:
        size_t bound_;
        std::vector<T> elements_;
    };

    /** @brief Priority queue of <distance, index> pair.
     */
    using KnnQueue = BoundedPriorityQueue<std::pair<double, int>>;

    /** @brief Builds k-d tree recursively.
     */
    Node *buildRecursive(int *indices, int npoints, int depth) {
        if (npoints <= 0)
            return nullptr;

        const int axis = depth % PointT::DIM;
        const int mid = (npoints - 1) / 2;

        std::nth_element(indices, indices + mid, indices + npoints, [&](int lhs, int rhs) {
            return points_[lhs][axis] < points_[rhs][axis];
        });

        Node *node = new Node();
        node->idx = indices[mid];
        node->axis = axis;

        node->next[0] = buildRecursive(indices, mid, depth + 1);
        node->next[1] = buildRecursive(indices + mid + 1, npoints - mid - 1, depth + 1);

        return node;
    }

    /** @brief Clears k-d tree recursively.
     */
    void clearRecursive(Node *node) {
        if (node == nullptr)
            return;

        if (node->next[0])
            clearRecursive(node->next[0]);

        if (node->next[1])
            clearRecursive(node->next[1]);

        delete node;
    }

    /** @brief Validates k-d tree recursively.
     */
    void validateRecursive(const Node *node, int depth) const {
        if (node == nullptr)
            return;

        const int axis = node->axis;
        const Node *node0 = node->next[0];
        const Node *node1 = node->next[1];

        if (node0 && node1) {
            if (points_[node->idx][axis] < points_[node0->idx][axis])
                throw Exception();

            if (points_[node->idx][axis] > points_[node1->idx][axis])
                throw Exception();
        }

        if (node0)
            validateRecursive(node0, depth + 1);

        if (node1)
            validateRecursive(node1, depth + 1);
    }

    static double distance(const PointT &p, const PointT &q) {
        double dist = 0;
        for (size_t i = 0; i < PointT::DIM; i++)
            dist += (p[i] - q[i]) * (p[i] - q[i]);
        return sqrt(dist);
    }

    /** @brief Searches the nearest neighbor recursively.
     */
    void nnSearchRecursive(const PointT &query, const Node *node, int *guess, double *minDist) const {
        if (node == nullptr)
            return;

        const PointT &train = points_[node->idx];

        const double dist = distance(query, train);
        if (dist < *minDist) {
            *minDist = dist;
            *guess = node->idx;
        }

        const int axis = node->axis;
        const int dir = query[axis] < train[axis] ? 0 : 1;
        nnSearchRecursive(query, node->next[dir], guess, minDist);

        const double diff = fabs(query[axis] - train[axis]);
        if (diff < *minDist)
            nnSearchRecursive(query, node->next[!dir], guess, minDist);
    }

    /** @brief Searches k-nearest neighbors recursively.
     */
    void knnSearchRecursive(const PointT &query, const Node *node, KnnQueue &queue, int k) const {
        if (node == nullptr)
            return;

        const PointT &train = points_[node->idx];

        const double dist = distance(query, train);
        queue.push(std::make_pair(dist, node->idx));

        const int axis = node->axis;
        const int dir = query[axis] < train[axis] ? 0 : 1;
        knnSearchRecursive(query, node->next[dir], queue, k);

        const double diff = fabs(query[axis] - train[axis]);
        if ((int)queue.size() < k || diff < queue.back().first)
            knnSearchRecursive(query, node->next[!dir], queue, k);
    }

    /** @brief Searches neighbors within radius.
     */
    void radiusSearchRecursive(const PointT &query, const Node *node, std::vector<int> &indices, double radius) const {
        if (node == nullptr)
            return;

        const PointT &train = points_[node->idx];

        const double dist = distance(query, train);
        if (dist < radius)
            indices.push_back(node->idx);

        const int axis = node->axis;
        const int dir = query[axis] < train[axis] ? 0 : 1;
        radiusSearchRecursive(query, node->next[dir], indices, radius);

        const double diff = fabs(query[axis] - train[axis]);
        if (diff < radius)
            radiusSearchRecursive(query, node->next[!dir], indices, radius);
    }

    Node *root_;                 //!< root node
    std::vector<PointT> points_; //!< points
};
} // namespace kdt

#endif // !__KDTREE_H__
struct ans_data {
    int before_x, before_y;
    int after_x, after_y;
};
constexpr int n = 1000;
void output(vector<ans_data> &ans) {
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].before_x << " " << ans[i].before_y << " " << ans[i].after_x << " " << ans[i].after_y << endl;
    }
}

pair<int, vector<ans_data>> execute(vector<pair<int, int>> a_b) {
    int cost = 0;
    vector<pair<int, int>> already_made;
    already_made.push_back({0, 0});

    vector<ans_data> ans;
    kdt::KDTree<pair<int, int>> kdtree;
    for (int i = 0; i < n; i++) {
        auto want_make = a_b[i];
        // already_madeの中で，want_makeよりもfirstもsecondも小さいものから選ぶ
        int min_diff = 1e18;
        pair<int, int> min_diff_pair = {0, 0};
        for (int j = 0; j < already_made.size(); j++) {
            auto made = already_made[j];
            if (made.first > want_make.first || made.second > want_make.second) {
                continue;
            }
            int diff = abs(made.first - want_make.first) + abs(made.second - want_make.second);
            if (diff < min_diff) {
                min_diff = diff;
                min_diff_pair = made;
            }
        }
        // want_makeとmin_diff_pairの間に等間隔に4つの座標を追加
        int xDiff = want_make.first - min_diff_pair.first, yDiff = want_make.second - min_diff_pair.second;
        cost += xDiff + yDiff;
        pair<int, int> prev_added = min_diff_pair;
        for (int j = 1; j <= 4; j++) {
            pair<int, int> next_added = {min_diff_pair.first + j * xDiff / 5, min_diff_pair.second + j * yDiff / 5};
            ans.push_back({prev_added.first, prev_added.second, next_added.first, next_added.second});
            already_made.push_back(next_added);
            prev_added = next_added;
        }
        ans.push_back({prev_added.first, prev_added.second, want_make.first, want_make.second});
        already_made.push_back(want_make);
    }
    return {cost, ans};
}

int32_t main() {
    ld start = clock();
    constexpr ld TIME_LIMIT = 1.9 * CLOCKS_PER_SEC;
    int _n;
    cin >> _n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<pair<int, int>> a_b(n);
    for (int i = 0; i < n; i++) {
        a_b[i] = {a[i], b[i]};
    }
    sort(all(a_b), [](pair<int, int> x, pair<int, int> y) {
        return x.first + x.second < y.first + y.second;
    });
    // 0を要素に持つ奴を先頭に持ってくる
    for (int i = 0; i < n; i++) {
        if (a_b[i].first == 0 || a_b[i].second == 0) {
            auto tmp = a_b[i];
            a_b.erase(a_b.begin() + i);
            a_b.insert(a_b.begin(), tmp);
        }
    }

    auto [cost, ans] = execute(a_b);
    ld end = clock();
    random_device seed_gen;
    mt19937 engine(seed_gen());
    int cnt = 0;
    while (end - start < TIME_LIMIT) {
        cnt++;
        int idx1 = uniform_int_distribution<int>(0, n - 1)(engine);
        int idx2 = uniform_int_distribution<int>(0, n - 1)(engine);
        swap(a_b[idx1], a_b[idx2]);
        auto [new_cost, new_ans] = execute(a_b);
        if (new_cost < cost) {
            cost = new_cost;
            ans = new_ans;
        } else {
            swap(a_b[idx1], a_b[idx2]);
        }
        end = clock();
    }
    output(ans);
    cerr << "cnt: " << cnt << endl;
}
