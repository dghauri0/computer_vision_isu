import cmath


# Implementation of Fast O(nlog(n)) FFT. Uses divide-and-conquer approach.
# Figured cmath is a better library to use here, so I don't have to separate
# real and imaginary parts in calculation.
def iter_fft(input_vector):
    size = len(input_vector)

    # Base case
    if size == 1:
        return input_vector

    # Perform D&C and loop through on each subsequent return
    # applying exponential calculation.
    else:

        # Initialize output vector
        output_vector = []
        for i in range(size):
            output_vector.append(-1)

        # log(n) from recursion tree generation. Split input vector into
        # even and odd element sub-parts.
        even = iter_fft(input_vector[0::2])
        odd = iter_fft(input_vector[1::2])

        # n from loop traversal
        for k in range(round(size / 2)):
            q = cmath.exp(-2j * cmath.pi * k / size) * odd[k]
            temp_0 = even[k] + q
            temp_0_real = round(temp_0.real, 4)
            temp_0_imag = round(temp_0.imag, 4)
            output_vector[k] = temp_0_real + (temp_0_imag * 1j)

            temp_1 = even[k] - q
            temp_1_real = round(temp_1.real, 4)
            temp_1_imag = round(temp_1.imag, 4)
            output_vector[k + round(size / 2)] = temp_1_real + (temp_1_imag * 1j)

        return output_vector


vect = [0, cmath.sqrt(2) / 2, 1, cmath.sqrt(2) / 2, 0, -cmath.sqrt(2) / 2, -1, -cmath.sqrt(2) / 2]

print("FFT check:", iter_fft(vect))
