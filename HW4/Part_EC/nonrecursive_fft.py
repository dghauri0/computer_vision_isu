import math, cmath


def iter_fft(input_vector):
    reved_input = bit_rev_copy(input_vector)
    size = len(reved_input)
    output = []
    for i in range(size):
        output.append(-1)

    for s in range(1, math.ceil(math.log2(size)), 1):
        m = round(math.pow(2, s))
        angle_m = cmath.exp(2 * cmath.pi * 1j / m)
        for k in range(0, size, m):
            angle = 1
            for i in range(round(m / 2)):
                a = angle * reved_input[k + i + round(m / 2)]
                b = reved_input[k + i]
                reved_input[k + i] = b + a
                reved_input[k + i + round(m / 2)] = b - a
                angle = angle * angle_m
    return reved_input


# Helper function to reverse a given integer's bits and then
# output the reversed integer form.
def rev_bits(integer, width):
    b = '{:0{width}b}'.format(integer, width=width)
    return int(b[::-1], 2)


# Helper function to re-order the input vector into different index
# positions based on the newly computed indexes from the rev_bits function.
def bit_rev_copy(input_vector):
    size = len(input_vector)
    output = []
    for i in range(size):
        output.append(0)
    for i in range(size):
        rev_width = math.ceil(math.log2(size))
        rev = rev_bits(i, rev_width)
        output[rev] = input_vector[i]
    return output


print(rev_bits(6, 3))
test = [1, 2, 3, 4, 5, 6, 7, 8]
print(bit_rev_copy(test))

vect = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071]
print("FFT check:", iter_fft(vect))
