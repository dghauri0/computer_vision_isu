import cmath


# Using divide-and-conquer for this approach. Needs input vectors to be powers
# of 2.
def fft(x):
    size = len(x)

    if size == 1:
        return x
    else:
        X = []
        for i in range(size):
            X.append(0)

        # log(n) from recursion tree generation
        even = fft(x[0::2])
        odd = fft(x[1::2])

        # n from loop traversal
        for k in range(round(size / 2)):
            w = cmath.exp(-2j * cmath.pi * k / size)
            X[k] = even[k] + w * odd[k]
            X[k + round(size / 2)] = even[k] - w * odd[k]

        return X


vect = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071]
print(fft(vect))
