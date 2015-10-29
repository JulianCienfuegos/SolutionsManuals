def horner(A, x):
    n = len(A)
    h1 = A[n-1]
    for i in range(n-2, -1, -1):
        h1 = h1*x + A[i]

    p1 = A[n-1]*x
    p2 = A[n-2]
    for i in range(n-3, -1, -1):
        p1 *= x
    for i in range(n-3, -1, -1):
        p2 = p2*x + A[i]
    h2 = p1 + p2
    return (h1,h2)

print(horner([1, 2, 3], 10))
print(3*10**2 + 2*10 + 1)
