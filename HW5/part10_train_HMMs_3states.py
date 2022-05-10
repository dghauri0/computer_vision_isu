from __future__ import print_function

import random

import nanohmm

# A = [[0.5, 0.5], [0.0, 1.0], [0.5, 0.5]]
# B = [[0.5, 0.5, 0.0], [0.5, 0.0, 0.5], [0.0, 0.5, 0.5]]
# pi = [0.0, 0.5, 0.5]

A = [[0.4, 0.0, 0.6],
     [0.2, 0.6, 0.2],
     [0.2, 0.4, 0.4]]
B = [[0.16, 0.0, 0.32, 0.16, 0.16, 0.20],
     [0.16, 0.16, 0.16, 0.16, 0.16, 0.20],
     [0.16, 0.16, 0.16, 0.16, 0.16, 0.20]]
pi = [0.5, 0.5, 0.0]

lambda_ = nanohmm.hmm_t(A, B, pi)
bw = nanohmm.baumwelch_t(lambda_)
O1 = [4, 2, 5, 1, 5, 1, 5, 3, 2, 3, 2, 0, 1, 0, 0, 4, 4, 3, 0, 1]
O2 = [3, 2, 3, 3, 5, 5, 5, 5, 1, 0, 1, 4, 2, 4, 3, 0, 5, 3, 1, 0]
O3 = [4, 3, 0, 3, 4, 0, 1, 0, 2, 0, 5, 3, 2, 0, 0, 5, 5, 3, 5, 4]
O4 = [3, 4, 2, 0, 5, 4, 4, 3, 1, 5, 3, 3, 2, 3, 0, 4, 2, 5, 2, 4]
O5 = [2, 0, 5, 4, 4, 2, 0, 5, 5, 4, 4, 2, 0, 5, 4, 4, 5, 5, 5, 5]
LL, lambda_ = nanohmm.baumwelch(bw, O5, 100)

iterations = 100
target_LL = -30.0
states = 3
M = 6
for i in range(iterations):

    if round(target_LL, 3) == round(LL, 3):
        break
    else:
        for j in range(states):
            prob = random.uniform(0, 1)
            A[j][0] = prob
            A[j][1] = (1 - prob) / 2
            A[j][2] = (1 - prob) / 2
            # print(A[j])
        for j in range(states):
            prob = random.uniform(0, 1)
            for k in range(M):
                B[j][k] = prob
                prob = (1 - prob)  # This doesn't make sense, but it tends to give me the lowest LL score.
            # print(B[j])

    lambda_ = nanohmm.hmm_t(A, B, pi)
    bw = nanohmm.baumwelch_t(lambda_)
    LL, lambda_ = nanohmm.baumwelch(bw, O5, 200)

print("LL =", LL)
print("Trained HMM:")
print("A = ", lambda_.A)
print("B = ", lambda_.B)
print("pi = ", lambda_.pi)
