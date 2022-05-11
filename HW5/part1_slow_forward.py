import itertools
import math

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

# Very... Naive implementation..
def slow_forward(A, B, pi, O):
    L = 0.0
    time_steps = len(O)

    if time_steps == 2:
        for time_step_0 in range(len(pi)):
            for time_step_1 in range(len(pi)):
                mult = pi[time_step_0] * B[time_step_0][O[0]] * A[time_step_0][time_step_1] * B[time_step_1][O[1]]
                L += mult

    elif time_steps == 3:
        for time_step_0 in range(len(pi)):
            for time_step_1 in range(len(pi)):
                for time_step_2 in range(len(pi)):
                    mult = pi[time_step_0] * B[time_step_0][O[0]] * A[time_step_0][time_step_1] * B[time_step_1][O[1]] * \
                           A[time_step_1][time_step_2] * B[time_step_2][O[2]]
                    L += mult

    elif time_steps == 4:
        for time_step_0 in range(len(pi)):
            for time_step_1 in range(len(pi)):
                for time_step_2 in range(len(pi)):
                    for time_step_3 in range(len(pi)):
                        mult = pi[time_step_0] * B[time_step_0][O[0]] * A[time_step_0][time_step_1] * B[time_step_1][
                            O[1]] * \
                               A[time_step_1][time_step_2] * B[time_step_2][O[2]] * A[time_step_2][time_step_3] * \
                               B[time_step_3][O[3]]
                        L += mult

    elif time_steps == 5:
        for time_step_0 in range(len(pi)):
            for time_step_1 in range(len(pi)):
                for time_step_2 in range(len(pi)):
                    for time_step_3 in range(len(pi)):
                        for time_step_4 in range(len(pi)):
                            mult = pi[time_step_0] * B[time_step_0][O[0]] * A[time_step_0][time_step_1] * \
                                   B[time_step_1][O[1]] * \
                                   A[time_step_1][time_step_2] * B[time_step_2][O[2]] * A[time_step_2][time_step_3] * \
                                   B[time_step_3][O[3]] * A[time_step_3][time_step_4] * B[time_step_4][O[4]]
                            L += mult

    return L


temp = slow_forward(A_ex, B_ex, pi_ex, O_ex)
print("L (EX): ", temp)
