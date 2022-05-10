import part2_forward_algorithm

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

A = [[0.6, 0.4],
     [1, 0]]
B = [[0.7, 0.3, 0],
     [0.1, 0.1, 0.8]]
pi = [0.7, 0.3]

O1 = [1, 0, 0, 0, 1, 0, 1]
O2 = [0, 0, 0, 1, 1, 2, 0]
O3 = [1, 1, 0, 1, 0, 1, 2]
O4 = [0, 1, 0, 2, 0, 1, 0]
O5 = [2, 2, 0, 1, 1, 0, 1]

alpha_ex = part2_forward_algorithm.forward_algorithm(A_ex, B_ex, pi_ex, O_ex)
alpha_1 = part2_forward_algorithm.forward_algorithm(A, B, pi, O1)
alpha_2 = part2_forward_algorithm.forward_algorithm(A, B, pi, O2)
alpha_3 = part2_forward_algorithm.forward_algorithm(A, B, pi, O3)
alpha_4 = part2_forward_algorithm.forward_algorithm(A, B, pi, O4)
alpha_5 = part2_forward_algorithm.forward_algorithm(A, B, pi, O5)

L = [0, 0, 0, 0, 0, 0]
for i in range(len(alpha_ex)):
    L[0] += alpha_ex[i][len(alpha_ex[0]) - 1]

for i in range(len(alpha_1)):
    L[1] += alpha_1[i][len(alpha_1[0]) - 1]

for i in range(len(alpha_2)):
    L[2] += alpha_2[i][len(alpha_2[0]) - 1]

for i in range(len(alpha_3)):
    L[3] += alpha_3[i][len(alpha_3[0]) - 1]

for i in range(len(alpha_4)):
    L[4] += alpha_4[i][len(alpha_4[0]) - 1]

for i in range(len(alpha_5)):
    L[5] += alpha_5[i][len(alpha_5[0]) - 1]

print(L)