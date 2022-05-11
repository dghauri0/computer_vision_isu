import math

def forward_algorithm_renorm(A, B, pi, O):
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