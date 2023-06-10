# #include <bits/stdc++.h>
# using namespace std;

# vector<int> sum;
# int main()
# {
#     int N;
#     cin >> N;
#     vector<int> A(N);
#     for (int i = 0; i < N; i++)
#     {
#         cin >> A[i];
#     }
#     sum.resize(A[N - 1] + 1, 0);

#     int A_index = 1;
#     bool plus = false;
#     for (int i = 0; i < A[N - 1]; i++)
#     {
#         if (i != 0 && A_index < N && i == A[A_index])
#         {
#             plus = !plus;
#             A_index++;
#         }
#         if (plus)
#         {
#             sum[i + 1] = sum[i] + 1;
#         }
#         else
#         {
#             sum[i + 1] = sum[i];
#         }
#     }
#     int Q;
#     cin >> Q;
#     for (int i = 0; i < Q; i++)
#     {
#         int l, r;
#         cin >> l >> r;
#         cout << sum[r] - sum[l] << endl;
#     }
# }

#上記のコードをpythonで書き直したもの

N = int(input())
A = list(map(int, input().split()))
sum = [0] * (A[N - 1] + 1)

A_index = 1
plus = False
for i in range(A[N - 1]):
    if i != 0 and A_index < N and i == A[A_index]:
        plus = not plus
        A_index += 1
    if plus:
        sum[i + 1] = sum[i] + 1
    else:
        sum[i + 1] = sum[i]

Q = int(input())
for i in range(Q):
    l, r = map(int, input().split())
    print(sum[r] - sum[l])
