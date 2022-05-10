import math, part2_forward_algorithm

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]


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
                    backward_variable_array[state][time] += A[i][state] * B[i][O[time + 1]] * \
                                                            backward_variable_array[i][time + 1]

    return backward_variable_array


print(backward_algorithm(A_ex, B_ex, pi_ex, O_ex))
