import part2_forward_algorithm
import part4_backward_algorithm

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

# Given HMM
A = [[0.6, 0.4],
     [1, 0]]
B = [[0.7, 0.3, 0],
     [0.1, 0.1, 0.8]]
pi = [0.7, 0.3]

# Observation Sequences
O = [[1, 0, 0, 0, 1, 0, 1],
     [0, 0, 0, 1, 1, 2, 0],
     [1, 1, 0, 1, 0, 1, 2],
     [0, 1, 0, 2, 0, 1, 0],
     [2, 2, 0, 1, 1, 0, 1]]

alpha_ex = part2_forward_algorithm.forward_algorithm(A_ex, B_ex, pi_ex, O_ex)
beta_ex = part4_backward_algorithm.backward_algorithm(A_ex, B_ex, pi_ex, O_ex)

print(alpha_ex)
print(beta_ex)

print("states: ", len(alpha_ex))
print("times: ", len(O_ex))

for o_s in range(5):
    alpha = part2_forward_algorithm.forward_algorithm(A, B, pi, O[o_s])
    beta = part4_backward_algorithm.backward_algorithm(A, B, pi, O[o_s])

    print("Observation Sequence ", o_s, ":")
    print("Alpha N-by-T array: ", alpha)
    print("Beta N-by-T array: ", beta)
    for time in range(len(O[o_s])):
        L = 0
        for state in range(len(alpha_ex)):
            L += alpha[state][time] * beta[state][time]
        print("Dot product time-step ", time, ":", L)
    print()
