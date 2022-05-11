import itertools
import math

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]


def slow_forward(A, B, pi, O):
    L = 0.0

    for time_step_0 in range(len(pi)):
        #mult = pi[time_step_0] * B[time_step_0][O[0]]
        for time_step_1 in range(len(pi)):
            #mult *= A[time_step_0][time_step_1] * B[time_step_1][O[1]]
            for time_step_2 in range(len(pi)):
                for time_step_3 in range(len(pi)):
                mult = pi[time_step_0] * B[time_step_0][O[0]] * A[time_step_0][time_step_1] * B[time_step_1][O[1]] * A[time_step_1][time_step_2] * B[time_step_2][O[2]]
                L += mult

    return L


temp = slow_forward(A_ex, B_ex, pi_ex, O_ex)
print(temp)
