import math

A = [[0.66, 0.34],
     [1, 0]]
B = [[0.5, 0.25, 0.25],
     [0.1, 0.1, 0.8]]
pi = [0.8, 0.2]

def slow_forward(A, B, pi, O):
    L = 0
    for state in range(len(O)):
        ''

