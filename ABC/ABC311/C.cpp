#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<vector<int>> graph;
bool flag = false;
int start = -1;
void search_closed_circuit_DFS(int v, vector<bool> &visited, set<int> &pass)
{
    for (int i = 0; !flag && i < graph[v].size(); i++)
    {
        if (pass.count(graph[v][i]))
        {
            flag = true;
            start = graph[v][i];
            return;
        }
        else
        {
            pass.insert(graph[v][i]);
            search_closed_circuit_DFS(graph[v][i], visited, pass);
            if (flag)
            {
                return;
            }
            pass.erase(graph[v][i]);
        }
    }
}

void a_search_closed_circuit_DFS(int base, int v, vector<bool> &visited, vector<int> &closed_circuit)
{
    visited[v] = true;
    for (int i = 0; !flag && i < graph[v].size(); i++)
    {
        if (graph[v][i] == base)
        {
            flag = true;
            closed_circuit.push_back(base);
            return;
        }
        else
        {
            if (visited[graph[v][i]])
                continue;
            closed_circuit.push_back(graph[v][i]);
            a_search_closed_circuit_DFS(base, graph[v][i], visited, closed_circuit);
            if (flag)
                return;
            closed_circuit.pop_back();
        }
    }
}

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    graph.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        graph[i].push_back(A[i] - 1);
    }

    // 同一頂点を複数回含まない有向閉路を求める
    for (int i = 0; i < N; i++)
    {
        vector<bool> visited(N, 0);
        set<int> pass;
        vector<int> closed_circuit;
        search_closed_circuit_DFS(i, visited, pass);
        if (flag)
            break;
    }
    flag = false;
    vector<bool> visited(N, 0);
    vector<int> ans;
    a_search_closed_circuit_DFS(start, start, visited, ans);

    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] + 1 << " ";
    }
}