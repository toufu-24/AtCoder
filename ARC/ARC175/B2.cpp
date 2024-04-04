#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, a, b;
    string s;
    cin >> n >> a >> b >> s;

    int cost = 0;
    stack<int> st;
    vector<int> unmatched_left;

    for (int i = 0; i < 2 * n; ++i) {
        if (s[i] == '(') {
            st.push(i);
            unmatched_left.push_back(i);
        } else {
            if (!st.empty()) {
                st.pop();
                unmatched_left.pop_back();
            } else {
                cost += b; // 未対応の左括弧がない場合は")"を"("に変更する
            }
        }
    }

    // 未対応の左括弧があれば、その分を対応させるためにコストを加算
    for (int i = 0; i < unmatched_left.size(); ++i) {
        cost += a;
    }

    cout << cost << endl;

    return 0;
}
