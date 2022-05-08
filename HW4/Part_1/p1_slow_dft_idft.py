import math
import random


# Implementation of Slow O(size^2) DFT. Takes two input vectors. First takes in the
# real part of the vector element and the second takes the imaginary part. Similarly,
# after computation, the real and imaginary parts are returned in a 2D array (element 0 of
# 2D array is real and element 1 of 2D array is imaginary).
def slow_dft(input_vector_real, input_vector_imaginary):
    size = 0
    if len(input_vector_real) == len(input_vector_imaginary):
        size = len(input_vector_real)
    else:
        return "Real and Imaginary parts are not the same size."

    output_real = []
    output_imaginary = []
    for n in range(size):
        sum_real = 0
        sum_imaginary = 0
        for k in range(size):
            angle = (2 * math.pi * k * n) / size
            sum_real = sum_real + (input_vector_real[k] * math.cos(angle)) + (
                    input_vector_imaginary[k] * math.sin(angle))
            sum_imaginary = sum_imaginary + (input_vector_imaginary[k] * math.cos(angle)) - (
                    input_vector_real[k] * math.sin(angle))
        output_real.append(round(sum_real, 5))
        output_imaginary.append(round(sum_imaginary, 5))
    return output_real, output_imaginary


# Implementation of Slow O(size^2) IDFT. Takes two input vectors. First takes in the
# real part of the vector element and the second takes the imaginary part. Similarly,
# after computation, the real and imaginary parts are returned in a 2D array (element 0 of
# 2D array is real and element 1 of 2D array is imaginary).
def slow_idft(input_vector_real, input_vector_imaginary):
    size = 0
    if len(input_vector_real) == len(input_vector_imaginary):
        size = len(input_vector_real)
    else:
        return "Real and Imaginary parts are not the same size."

    output_real = []
    output_imaginary = []
    for n in range(size):
        sum_real = 0
        sum_imaginary = 0
        for k in range(size):
            angle = (2 * math.pi * k * n) / size
            sum_real = sum_real + (input_vector_real[k] * math.cos(angle)) - (
                    input_vector_imaginary[k] * math.sin(angle))
            sum_imaginary = sum_imaginary + (input_vector_real[k] * math.sin(angle)) + (
                    input_vector_imaginary[k] * math.cos(angle))
        output_real.append(round(sum_real / size, 5))
        output_imaginary.append(round(sum_imaginary / size, 5))
    return output_real, output_imaginary


input_vector_real = [0, math.sqrt(2) / 2, 1, math.sqrt(2) / 2, 0, -math.sqrt(2) / 2, -1, -math.sqrt(2) / 2]
input_vector_complex = [0, 0, 0, 0, 0, 0, 0, 0]

temp = slow_dft(input_vector_real, input_vector_complex)

print(temp)

size = 1024
input_vec_real = []
input_vec_imag = []

for i in range(size):
    input_vec_real.append(random.uniform(10, 100))
    input_vec_imag.append(random.uniform(10, 100))

temp = slow_dft(input_vec_real, input_vec_imag)

print(temp[0])
print(temp[1])

idft_check_real = [0, 0, 0, 0, 0, 0, 0, 0]
idft_check_imag = [0, -4, 0, 0, 0, 0, 0, 4]

print(slow_idft(idft_check_real, idft_check_imag))
