import math

# From lecture as check
A_ex = [[0.5, 0.5],
        [0, 1]]
B_ex = [[0.5, 0.0, 0.5],
        [0, 1, 0]]
pi_ex = [1, 0]
O_ex = [0, 2, 1]

def slow_forward(A, B, pi, O):
    L = 0
    for state in range(len(pi)):
        for time in range(len(O)):
            
