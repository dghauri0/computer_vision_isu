# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

# HMM model parameters given from 3A
A_3a = [[0.66, 0.34],
        [1, 0]]
B_3a = [[0.5, 0.25, 0.25],
        [0.1, 0.1, 0.8]]
pi_3a = [0.8, 0.2]

# HMM model parameters given from 3B
A_3b = [[0.8, 0.1, 0.1],
        [0.4, 0.2, 0.4],
        [0, 0.3, 0.7]]
B_3b = [[0.66, 0.34, 0],
        [0, 0, 1],
        [0.5, 0.4, 0.1]]
pi_3b = [0.6, 0, 0.4]

O_3 = [0, 1, 0, 2, 0, 1, 0]


def forward_algorithm(A, B, pi, O):
    forward_variable_array = [[0] * len(O) for i in range(len(pi))]
    for time in range(len(O)):
        for state in range(len(pi)):
            if time == 0:
                forward_variable_array[state][time] = pi[state] * B[state][O[time]]
            else:
                for i in range(len(pi)):
                    forward_variable_array[state][time] += forward_variable_array[i][time - 1] * A[i][state] * B[state][
                        O[time]]

    return forward_variable_array


print(forward_algorithm(A_3a, B_3a, pi_3a, O_3))
print(forward_algorithm(A_3b, B_3b, pi_3b, O_3))
