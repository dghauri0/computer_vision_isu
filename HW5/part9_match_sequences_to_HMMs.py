from __future__ import print_function

import nanohmm

# HMM 1.
A_1 = [[0.33, 0, 0, 0.67, 0],
       [0.67, 0, 0.33, 0, 0],
       [0, 1.0, 0.0, 0, 0],
       [0, 0, 0, 0.25, 0.75],
       [0.0, 0.0, 0.6, 0, 0.4]]
B_1 = [[0.67, 0, 0, 0, 0, 0.33],
       [0.0, 1.0, 0, 0, 0, 0],
       [0.5, 0, 0, 0, 0, 0.5],
       [0, 0, 0, 0.25, 0.75, 0],
       [0, 0.0, 0.6, 0.4, 0, 0.0]]
pi_1 = [0.0, 0.0, 0.0, 1.0, 0.0]

# HMM 2.
A_2 = [[0.0, 0.0, 1.0, 0, 0.0],
       [0.0, 0, 0.0, 0.0, 1.0],
       [0.38, 0.0, 0.23, 0.38, 0.0],
       [0.0, 0.31, 0.0, 0.69, 0],
       [0.0, 0.75, 0.0, 0.25, 0.0]]
B_2 = [[0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
       [0.0, 0.6, 0.2, 0.2, 0.0, 0.0],
       [0.0, 0.0, 0, 1.0, 0.0, 0],
       [0, 0.0, 0, 0.22, 0.0, 0.78],
       [0.6, 0.0, 0.0, 0.0, 0.4, 0.0]]
pi_2 = [0.0, 0.0, 1.0, 0.0, 0.0]

# HMM 3.
A_3 = [[0, 0.0, 0.32, 0.18, 0.5],
       [0.0, 0.0, 0.0, 1.0, 0.0],
       [0, 0.0, 0, 0.0, 1.0],
       [0, 0.64, 0, 0.0, 0.36],
       [1.0, 0.0, 0, 0, 0]]
B_3 = [[0.0, 0.17, 0.33, 0.0, 0.0, 0.5],
       [0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
       [0.47, 0.0, 0.0, 0.0, 0.0, 0.53],
       [0.27, 0.0, 0.0, 0.0, 0.73, 0.0],
       [0.66, 0.0, 0.0, 0.33, 0.0, 0.0]]
pi_3 = [0.0, 0.0, 0.0, 1.0, 0.0]

# HMM 4.
A_4 = [[0.0, 0.0, 1.0, 0, 0.0],
       [0.0, 0, 0.62, 0, 0.38],
       [0.0, 0.5, 0.0, 0.5, 0.0],
       [0.0, 0.23, 0.0, 0.0, 0.77],
       [0.0, 0, 0, 1.0, 0]]
B_4 = [[0.0, 0.0, 0.0, 1.0, 0.0, 0.0],
       [0.0, 0.0, 0.62, 0, 0.38, 0.0],
       [0, 0.0, 0.0, 0.0, 1, 0],
       [0, 0.0, 0, 0.41, 0.18, 0.41],
       [0.31, 0.16, 0.37, 0.16, 0, 0.0]]
pi_4 = [1.0, 0.0, 0.0, 0.0, 0]

# HMM 5.
A_5 = [[0.5, 0.33, 0, 0.17, 0.0],
       [0.0, 0.0, 0.0, 0.0, 1.0],
       [0.75, 0.0, 0.25, 0.0, 0.0],
       [0.0, 0.0, 0, 1.0, 0.0],
       [0.0, 0.0, 1.0, 0.0, 0.0]]
B_5 = [[0.0, 0.0, 0.0, 0.0, 1.0, 0],
       [0.0, 0.0, 1.0, 0.0, 0.0, 0.0],
       [0.0, 0.0, 0.0, 0.0, 0, 1.0],
       [0.0, 0.0, 0.0, 0.0, 0, 1.0],
       [1.0, 0.0, 0.0, 0.0, 0.0, 0.0]]
pi_5 = [0.0, 1.0, 0.0, 0.0, 0.0]

# Given observation sequences.
O_1 = [4, 2, 5, 1, 5, 1, 5, 3, 2, 3, 2, 0, 1, 0, 0, 4, 4, 3, 0, 1]
O_2 = [3, 2, 3, 3, 5, 5, 5, 5, 1, 0, 1, 4, 2, 4, 3, 0, 5, 3, 1, 0]
O_3 = [4, 3, 0, 3, 4, 0, 1, 0, 2, 0, 5, 3, 2, 0, 0, 5, 5, 3, 5, 4]
O_4 = [3, 4, 2, 0, 5, 4, 4, 3, 1, 5, 3, 3, 2, 3, 0, 4, 2, 5, 2, 4]
O_5 = [2, 0, 5, 4, 4, 2, 0, 5, 5, 4, 4, 2, 0, 5, 4, 4, 5, 5, 5, 5]

for i in range(5):
    f = 0.0
    if i == 0:
        lambda_ = nanohmm.hmm_t(A_1, B_1, pi_1)
        f = nanohmm.forward_t(lambda_)

    if i == 1:
        lambda_ = nanohmm.hmm_t(A_2, B_2, pi_2)
        f = nanohmm.forward_t(lambda_)

    if i == 2:
        lambda_ = nanohmm.hmm_t(A_3, B_3, pi_3)
        f = nanohmm.forward_t(lambda_)

    if i == 3:
        lambda_ = nanohmm.hmm_t(A_4, B_4, pi_4)
        f = nanohmm.forward_t(lambda_)

    if i == 4:
        lambda_ = nanohmm.hmm_t(A_5, B_5, pi_5)
        f = nanohmm.forward_t(lambda_)

    print("Computed LL's for HMM ", i + 1, ":")
    print("O1: ", nanohmm.forward(f, O_1))
    print("O2: ", nanohmm.forward(f, O_2))
    print("O3: ", nanohmm.forward(f, O_3))
    print("O4: ", nanohmm.forward(f, O_4))
    print("O5: ", nanohmm.forward(f, O_5))
    print()

# lambda_ = nanohmm.hmm_t(A_1, B_1, pi_1)
# f = nanohmm.forward_t(lambda_)
# print("O2: ", nanohmm.forward(f, O_2))