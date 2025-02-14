N = int(input())
arr = list(map(int, input().split()))
v = int(input())

res = 0
for i in arr:
    if (i == v):
        res += 1

print(res)