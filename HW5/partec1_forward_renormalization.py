import math, part2_forward_algorithm

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]


def forward_algorithm_renorm(A, B, pi, O):
    forward_variable_array = [[0] * len(O) for i in range(len(pi))]
    renorm_coeff = [0.0] * len(O)
    print(renorm_coeff)
    for time in range(len(O)):
        renorm_coeff[time] = 0
        for state in range(len(pi)):
            if time == 0:
                forward_variable_array[state][time] = pi[state] * B[state][O[time]]
            else:
                for i in range(len(pi)):
                    forward_variable_array[state][time] += forward_variable_array[i][time - 1] * A[i][state] * B[state][
                        O[time]]
            renorm_coeff[time] += forward_variable_array[state][time]
        if renorm_coeff[time] == 0.0 or math.fabs(renorm_coeff[time]) < 1e-10:
            renorm_coeff[time] = 1.0
        else:
            renorm_coeff[time] = 1.0 / renorm_coeff[time]
            for k in range(len(pi)):
                forward_variable_array[k][time] *= renorm_coeff[time]

    return forward_variable_array


print(forward_algorithm_renorm(A_ex, B_ex, pi_ex, O_ex))
print(part2_forward_algorithm.forward_algorithm(A_ex, B_ex, pi_ex, O_ex))
