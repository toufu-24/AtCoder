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

struct TrieNode {
    map<char, TrieNode *> children;
    vector<int> string_ids; // この接頭辞を持つ文字列のインデックスを保存
    int count;              // この接頭辞を持つ文字列の数

    TrieNode() : count(0) {}

    ~TrieNode() {
        for (auto &pair : children) {
            delete pair.second;
        }
    }
};

class Trie {
  private:
    TrieNode *root;

  public:
    Trie() : root(new TrieNode()) {}

    ~Trie() {
        delete root;
    }

    // 文字列の挿入
    void insert(const string &s, int id) {
        TrieNode *node = root;
        for (char c : s) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->string_ids.push_back(id);
            node->count++;
        }
    }

    // 最小の文字列長を計算
    int getMinLength(const string &s, int id) {
        TrieNode *node = root;
        int prefix_len = 0;
        int min_len = s.length(); // 最初は文字列自体の長さ

        // トライ木をたどりながら最小長を計算
        for (size_t i = 0; i < s.length() && node; i++) {
            char c = s[i];
            if (!node->children[c])
                break;

            node = node->children[c];
            prefix_len++;

            // この接頭辞を持つ他の文字列との比較
            for (int other_id : node->string_ids) {
                if (other_id < id) { // 既に処理済みの文字列とのみ比較
                    string &other = strings[other_id];
                    int new_len = other.length() + s.length() - 2 * prefix_len;
                    min_len = min(min_len, new_len);
                }
            }
        }

        return min_len;
    }

    static vector<string> strings; // 文字列を格納する静的配列
};

vector<string> Trie::strings; // 静的メンバの定義

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    Trie trie;
    Trie::strings.resize(n);

    int max_len = 0;
    for (int i = 0; i < n; i++) {
        cin >> Trie::strings[i];
        max_len = max(max_len, (int)Trie::strings[i].length());
    }

    if (max_len > 13) {
        for (int i = 0; i < n; i++) {
            int ans = trie.getMinLength(Trie::strings[i], i);
            cout << ans << "\n";
            trie.insert(Trie::strings[i], i);
        }
    } else {
        map<string, int> st;
        for (int i = 0; i < n; i++) {
            string s = Trie::strings[i];
            int curr_len = s.size();
            int tmp = curr_len;

            // 最長の共通接頭辞を探索
            while (!s.empty()) {
                if (st.count(s)) {
                    tmp = s.size();
                    break;
                }
                s.pop_back();
            }

            // 空文字列の場合の処理
            int ans;
            if (s.empty()) {
                ans = curr_len;
            } else {
                ans = min(curr_len, st[s] + curr_len - 2 * tmp);
            }
            cout << ans << '\n';

            // 全ての接頭辞を登録
            string t;
            for (char c : Trie::strings[i]) {
                t += c;
                if (!st.count(t)) {
                    st[t] = curr_len;
                } else {
                    st[t] = min(st[t], curr_len);
                }
            }
        }
    }
}