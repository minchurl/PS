
N = int (input())
arr = list(map(int, input().split()))

mx = -1000001

for i in range(N):
    if arr[i] > mx:
        mx = arr[i]