import cmath


# Implementation of Fast O(nlog(n)) FFT. Uses divide-and-conquer approach.
# Figured cmath is a better library to use here, so I don't have to separate
# real and imaginary parts in calculation.
def fft(input_vector):
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
        even = fft(input_vector[0::2])
        odd = fft(input_vector[1::2])

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


# Implementation of Fast O(nlog(n)) IFFT. Uses divide-and-conquer approach.
# Figured cmath is a better library to use here, so I don't have to separate
# real and imaginary parts in calculation.
def ifft(input_vector):
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

        # O(log(n)) from recursion tree generation. Split input vector into
        # even and odd element sub-parts.
        even = ifft(input_vector[0::2])
        odd = ifft(input_vector[1::2])

        # O(n) from loop traversal
        for k in range(round(size / 2)):
            q = cmath.exp(2j * cmath.pi * k / size) * odd[k]
            temp_0 = (even[k] + q)
            temp_0_real = round(temp_0.real, 4)
            temp_0_imag = round(temp_0.imag, 4)
            output_vector[k] = temp_0_real + (temp_0_imag * 1j)

            temp_1 = (even[k] - q)
            temp_1_real = round(temp_1.real, 4)
            temp_1_imag = round(temp_1.imag, 4)
            output_vector[k + round(size / 2)] = temp_1_real + (temp_1_imag * 1j)

        return output_vector


# Final scaling helper function for IFFT. This was needed as
# dividing by size as required by the IDFT base algorithm at every level
# in the recursion tree resulted in improper scaling. Therefore, we do it instead
# at the very end stage, which means we need to call this function seperately once
# we exit the main ifft function. Still, big-o is not violated (iirc) as we still have
# O(nlog(n)) + O(n) = O(nlog(n))
def scaling_ifft(vector, size):
    output_vector = []
    for i in range(size):
        output_vector.append(vector[i] / size)
    return output_vector


vect = [0, cmath.sqrt(2)/2, 1, cmath.sqrt(2)/2, 0, -cmath.sqrt(2)/2, -1, -cmath.sqrt(2)/2]
vect_inv = [0, -4j, 0, 0, 0, 0, 0, 4j]

print("FFT check:", fft(vect))
print("IFFT check:", scaling_ifft(ifft(vect_inv), len(vect_inv)))
