#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

struct Pos
{
    int y, x;
};

struct Judge
{
    void set_temperature(const vector<vector<int>> &temperature)
    {
        for (const vector<int> &row : temperature)
        {
            for (int i = 0; i < row.size(); i++)
            {
                cout << row[i] << (i == row.size() - 1 ? "\n" : " ");
            }
        }
        cout.flush();
    }

    int measure(int i, int y, int x)
    {
        cout << i << " " << y << " " << x << endl; // endl does flush
        int v;
        cin >> v;
        if (v == -1)
        {
            cerr << "something went wrong. i=" << i << " y=" << y << " x=" << x << endl;
            exit(1);
        }
        return v;
    }

    void answer(const vector<int> &estimate)
    {
        cout << "-1 -1 -1" << endl;
        for (int e : estimate)
        {
            cout << e << endl;
        }
    }
};

struct Solver
{
    const int L;
    const int N;
    const int S;
    const vector<Pos> landing_pos;
    Judge judge;

    Solver(int L, int N, int S, const vector<Pos> &landing_pos) : L(L), N(N), S(S), landing_pos(landing_pos), judge()
    {
    }

    void solve()
    {
        // sort(landing_pos.begin(), landing_pos.end());
        const vector<vector<int>> temperature = create_temperature();
        judge.set_temperature(temperature);
        const vector<int> estimate = predict(temperature);
        judge.answer(estimate);
    }

    vector<vector<int>> create_temperature()
    {
        vector<vector<int>> temperature(L, vector<int>(L, 0));
        // set the temperature to i * 10 for i-th position
        int max_temperature = 1000;
        int each_temperature = max_temperature / N;
        for (int i = 0; i < N; i++)
        {
            temperature[landing_pos[i].y][landing_pos[i].x] = i * each_temperature;
        }
        return temperature;
    }

    vector<int> predict(const vector<vector<int>> &temperature)
    {
        vector<int> estimate(N);
        for (int i_in = 0; i_in < N; i_in++)
        {
            // you can output comment
            cout << "# measure i=" << i_in << " y=0 x=0" << endl;

            vector<int> measured_values;
            ld loop_num = 4000 / (ld)N;
            for (int i = 0; i < loop_num; i++)
            {
                measured_values.push_back(judge.measure(i_in, 0, 0));
            }
            ll average = 0;
            for (int v : measured_values)
            {
                average += v;
            }
            average /= measured_values.size();

            // answer the position with the temperature closest to the measured value
            int min_diff = 9999;
            for (int i_out = 0; i_out < N; i_out++)
            {
                const Pos &pos = landing_pos[i_out];
                int diff = abs(temperature[pos.y][pos.x] - average);
                if (diff < min_diff)
                {
                    min_diff = diff;
                    estimate[i_in] = i_out;
                }
            }
        }
        return estimate;
    }
};

int main()
{
    int L, N, S;
    cin >> L >> N >> S;
    vector<Pos> landing_pos(N);
    for (int i = 0; i < N; i++)
    {
        cin >> landing_pos[i].y >> landing_pos[i].x;
    }

    Solver solver(L, N, S, landing_pos);
    solver.solve();
}
