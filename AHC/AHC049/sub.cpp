//  ------------------------------------------------------------
//  Durability-Constrained Transport  (N = 20 固定)
//  Simulated Annealing + Stack grouping
//  C++17  (g++ -std=c++17 -O2)
//  ------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---- 定数 ----
constexpr int N = 20;
constexpr int CELL = N * N - 1;          // (0,0) 以外の箱数
constexpr int MAX_STACK = 10;            // 1スタック上限
constexpr double TIME_LIMIT = 1.8;       // 実行時間 (秒)
constexpr double T0  = 1e4;              // 初期温度
constexpr double T_END = 1e-2;           // 最終温度
constexpr ll INF_COST = (1LL<<60);       // 壊れた解のペナルティ

// ---- 座標 ↔ ID 変換 ----
struct Pos { int x, y; };
inline int manhattan(const Pos& a, const Pos& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// ---- グローバル入力 ----
array<array<int,N>,N> W, D;          // weight, durability
array<Pos, N*N> id2pos;              // id → 座標

// ---- 乱数 ----
static std::mt19937_64 rng(42);

// ---- 解の表現 ----
struct Solution{
    array<int, CELL> order;          // 訪問順 permutation
    vector<int> stack_size;          // 各スタックの個数
};

// ---- 評価（T を返す。壊れたら INF_COST）----
ll evaluate(const Solution& sol){
    ll totalMove = 0;
    int idx = 0;
    const Pos ORI{0,0};
    for(int s=0; s<(int)sol.stack_size.size(); ++s){
        int L = sol.stack_size[s];
        // --- スタック中のデータをローカル配列へコピー ---
        static int wt[MAX_STACK+2];
        static int dur[MAX_STACK+2];
        static Pos pos[MAX_STACK+2];
        for(int i=0;i<L;++i){
            int id = sol.order[idx+i];
            pos[i] = id2pos[id];
            wt[i]  = W[pos[i].x][pos[i].y];
            dur[i] = D[pos[i].x][pos[i].y];
        }
        idx += L;

        // --- 距離配列 ---
        static int suffixMove[MAX_STACK+2];
        // dist from origin to first pick
        int distStart = manhattan(ORI, pos[0]);
        // suffixMove[L-1] = dist(last, origin)
        suffixMove[L-1] = manhattan(pos[L-1], ORI);
        for(int i=L-2;i>=0;--i){
            suffixMove[i] = manhattan(pos[i], pos[i+1]) + suffixMove[i+1];
        }
        // --- 重み prefix ----
        static int suffixW[MAX_STACK+2];
        suffixW[L] = 0;
        for(int i=L-1;i>=0;--i) suffixW[i] = suffixW[i+1] + wt[i];

        // --- 耐久チェック ---
        for(int i=0;i<L-1;++i){                 // top 箱は weightAbove=0
            ll weightAbove = suffixW[i+1];
            ll need = (ll)suffixMove[i] * weightAbove;
            if(need > dur[i]) return INF_COST; // 壊れる
        }
        // --- 移動回数加算 ---
        ll pathLen = distStart + suffixMove[0];     // suffixMove[0] には最後の origin 戻りも含む
        for(int i=0;i<L-1;++i) pathLen += manhattan(pos[i], pos[i+1]); // ただし重複加算を避ける
        totalMove += pathLen;
        if(totalMove >= INF_COST) return INF_COST;
    }
    return totalMove;
}

// ---- 操作列生成（最良解から）----
void appendPath(vector<char>& ops, const Pos& from, const Pos& to){
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    char v = dx > 0 ? 'D' : 'U';
    for(int k=0;k<abs(dx);++k) ops.push_back(v);
    char h = dy > 0 ? 'R' : 'L';
    for(int k=0;k<abs(dy);++k) ops.push_back(h);
}
vector<char> build_ops(const Solution& sol){
    vector<char> ops;
    const Pos ORI{0,0};
    Pos cur = ORI;
    int idx = 0;
    for(int sz : sol.stack_size){
        for(int i=0;i<sz;++i){
            int id = sol.order[idx++];
            Pos p = id2pos[id];
            appendPath(ops, cur, p);
            ops.push_back('1');               // pick
            cur = p;
        }
        appendPath(ops, cur, ORI);            // return & auto-deliver
        cur = ORI;
    }
    return ops;
}

// ---- 近傍生成 ----
Solution mutate(const Solution& base){
    Solution nxt = base;
    std::uniform_int_distribution<int> distOp(0, 2);
    int opType = distOp(rng);
    if(opType == 0){ // swap-2
        std::uniform_int_distribution<int> distIdx(0, CELL-1);
        int a = distIdx(rng), b = distIdx(rng);
        if(a>b) swap(a,b);
        swap(nxt.order[a], nxt.order[b]);
    }else if(opType == 1 && nxt.stack_size.size()>1){ // shiftCut
        std::uniform_int_distribution<int> distS(0, (int)nxt.stack_size.size()-2);
        int s = distS(rng);
        if(nxt.stack_size[s] > 1){
            nxt.stack_size[s]--;
            nxt.stack_size[s+1]++;
        }
    }else{ // reverse 区間
        std::uniform_int_distribution<int> distL(0, CELL-2);
        int l = distL(rng);
        std::uniform_int_distribution<int> distR(l+1, CELL-1);
        int r = distR(rng);
        while(l<r){
            swap(nxt.order[l], nxt.order[r]);
            ++l; --r;
        }
    }
    return nxt;
}

// ---- SA 本体 ----
Solution simulated_annealing(Solution init){
    Solution best = init, cur = init;
    ll bestCost = evaluate(best);
    ll curCost  = bestCost;

    const double logAlpha = log(T_END / T0);
    const auto t0 = chrono::steady_clock::now();
    long long iter = 0;

    while(true){
        double elapsed = chrono::duration<double>(chrono::steady_clock::now() - t0).count();
        if(elapsed > TIME_LIMIT) break;
        double T = T0 * exp(logAlpha * elapsed / TIME_LIMIT);  // 時間比例で冷却
        Solution cand = mutate(cur);
        ll candCost = evaluate(cand);
        double acceptProb = (candCost < curCost) ? 1.0
                           : exp((double)(curCost - candCost) / T);
        if(acceptProb > std::uniform_real_distribution<double>(0.0, 1.0)(rng)){
            cur = std::move(cand);
            curCost = candCost;
            if(curCost < bestCost){
                best = cur;
                bestCost = curCost;
            }
        }
        ++iter;
    }
    // cerr << "iter=" << iter << "  bestT=" << bestCost << endl;
    return best;
}

// ---- main ----
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _N; cin >> _N;  // 仕様では常に 20
    for(int i=0;i<N;++i)for(int j=0;j<N;++j) cin >> W[i][j];
    for(int i=0;i<N;++i)for(int j=0;j<N;++j) cin >> D[i][j];

    // id → 座標
    for(int i=0;i<N;++i)for(int j=0;j<N;++j) id2pos[i*N+j] = {i,j};

    // --- 初期解（リング外周から順に訪問、固定スタック長 MAX_STACK） ---
    Solution init;
    int ptr = 0;
    for(int d=2*N-2; d>=0; --d){              // マンハッタン距離降順
        for(int i=0;i<N;++i){
            int j = d - i;
            if(j<0||j>=N) continue;
            if(i==0 && j==0) continue;
            init.order[ptr++] = i*N + j;
        }
    }
    init.stack_size.clear();
    int rest = CELL;
    while(rest){
        int take = min<int>(MAX_STACK, rest);
        init.stack_size.push_back(take);
        rest -= take;
    }

    // --- SA で改善 ---
    Solution best = simulated_annealing(init);

    // --- 操作列を出力 ---
    vector<char> ops = build_ops(best);
    for(char c : ops) cout << c << '\n';
    return 0;
}
