import cmath


# Implementation of Fast O(nlog(n)) FFT. Uses divide-and-conquer approach.
# Figured cmath is a better library to use here, so I don't have to separate
# real and imaginary parts in calculation.
def iter_fft(input_vector):
    size = 


vect = [0, cmath.sqrt(2) / 2, 1, cmath.sqrt(2) / 2, 0, -cmath.sqrt(2) / 2, -1, -cmath.sqrt(2) / 2]

print("FFT check:", iter_fft(vect))
