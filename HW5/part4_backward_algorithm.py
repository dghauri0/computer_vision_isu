import math, part2_forward_algorithm

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

# HMM model parameters given from 5A
A_5a = [[0.66, 0.34],
        [1, 0]]
B_5a = [[0.5, 0.25, 0.25],
        [0.1, 0.1, 0.8]]
pi_5a = [0.8, 0.2]

# HMM model parameters given from 5B
A_5b = [[0.8, 0.1, 0.1],
        [0.4, 0.2, 0.4],
        [0, 0.3, 0.7]]
B_5b = [[0.66, 0.34, 0],
        [0, 0, 1],
        [0.5, 0.4, 0.1]]
pi_5b = [0.6, 0, 0.4]

O_5 = [0, 1, 0, 2, 0, 1, 0]

def backward_algorithm(A, B, pi, O):
    backward_variable_array = [[0] * len(O) for i in range(len(pi))]
    forward_variable_array = part2_forward_algorithm.forward_algorithm(A, B, pi, O)
    for time in reversed(range(len(O))):
        for state in range(len(pi)):
            if time == (len(O) - 1):
                # initialization
                backward_variable_array[state][time] = 1
            else:
                for i in range(len(pi)):
                    backward_variable_array[state][time] += A[state][i] * B[i][O[time + 1]] * \
                                                            backward_variable_array[i][time + 1]

    return backward_variable_array


# print(backward_algorithm(A_ex, B_ex, pi_ex, O_ex))
# print(backward_algorithm(A_5a, B_5a, pi_5a, O_5))
# print(backward_algorithm(A_5b, B_5b, pi_5b, O_5))
