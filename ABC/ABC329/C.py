N = int(input())
S = input()
st = set()
tmp = ""
tmp += S[0]
st.add(tmp)
for i in range(1, N):
    if S[i] == S[i - 1]:
        tmp += S[i]
        st.add(tmp)
    else:
        st.add(tmp)
        tmp = ""
        tmp += S[i]
        st.add(tmp)
st.add(tmp)
print(len(st))
