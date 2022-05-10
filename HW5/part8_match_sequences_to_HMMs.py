import part2_forward_algorithm

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

# HMM 1:
A_1 = [[1.0, 0.0], [0.5, 0.5]]
B_1 = [[0.4, 0.6, 0.0], [0.0, 0.0, 1.0]]
pi_1 = [0.0, 1.0]

# HMM 2:
A_2 = [[0.25, 0.75], [1.0, 0.0]]
B_2 = [[0, 1.0, 0], [0.66, 0.0, 0.34]]
pi_2 = [1.0, 0.0]

# HMM 3:
A_3 = [[0.0, 1.0], [1.0, 0.0]]
B_3 = [[1.0, 0.0, 0.0], [0.0, 0.66, 0.34]]
pi_3 = [1.0, 0.0]

# HMM 4:
A_4 = [[1, 0], [0.44, 0.56]]
B_4 = [[0.36, 0.42, 0.22], [1.0, 0, 0]]
pi_4 = [0, 1.0]

# HMM 5:
A_5 = [[0.0, 1.0], [1.0, 0.0]]
B_5 = [[0.25, 0.75, 0.0], [1.0, 0.0, 0.0]]
pi_5 = [1.0, 0.0]

O = [[1, 0, 0, 0, 1, 0, 1],
     [0, 0, 0, 1, 1, 2, 0],
     [1, 1, 0, 1, 0, 1, 2],
     [0, 1, 0, 2, 0, 1, 0],
     [2, 2, 0, 1, 1, 0, 1]]

alpha = [[None] for i in range(6)]

for i in range(len(O)):
    alpha[0] = part2_forward_algorithm.forward_algorithm(A_ex, B_ex, pi_ex, O_ex)
    alpha[1] = part2_forward_algorithm.forward_algorithm(A_1, B_1, pi_1, O[i])
    alpha[2] = part2_forward_algorithm.forward_algorithm(A_2, B_2, pi_2, O[i])
    alpha[3] = part2_forward_algorithm.forward_algorithm(A_3, B_3, pi_3, O[i])
    alpha[4] = part2_forward_algorithm.forward_algorithm(A_4, B_4, pi_4, O[i])
    alpha[5] = part2_forward_algorithm.forward_algorithm(A_5, B_5, pi_5, O[i])
    for j in range()

print(alpha)
