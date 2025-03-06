def xor(dividend, divisor):
    """Perform XOR operation for CRC calculation."""
    result = []
    for i in range(1, len(divisor)):
        if divisor[i] == dividend[i]:
            result.append('0')
        else :
            result.append('1')
    return ''.join(result)


def crc_encode(dividend, divisor):
    """Perform CRC encoding."""
    divisor_bits = len(divisor)
    extra_bits = divisor_bits - 1
    dividend_padded = dividend + '0' * extra_bits

    temp = dividend_padded[0:divisor_bits]

    for i in range(len(dividend)):
        if temp[0] == '1':
            temp = (xor(temp, divisor) +
                    (
                dividend_padded[i + divisor_bits]
                if i + divisor_bits < len(dividend_padded) else ''
                    ))
        else:
            temp = xor(temp, '0' * divisor_bits) + (
                dividend_padded[i + divisor_bits] if i + divisor_bits < len(dividend_padded) else '')

    remainder = temp[0:extra_bits]
    encoded_word = dividend + remainder

    print("\nEncoding Results:")
    print(f"Encoded Word: {encoded_word}")
    print(f"CRC Remainder: {remainder}")
    print(f"Number of Extra Bits Added: {extra_bits}\n")

    return encoded_word, remainder


def crc_decode(encoded_word, divisor):
    """Perform CRC decoding."""
    divisor_bits = len(divisor)
    temp = encoded_word[0:divisor_bits]

    for i in range(len(encoded_word) - divisor_bits + 1):
        if temp[0] == '1':
            temp = xor(temp, divisor) + (encoded_word[i + divisor_bits] if i + divisor_bits < len(encoded_word) else '')
        else:
            temp = xor(temp, '0' * divisor_bits) + (
                encoded_word[i + divisor_bits] if i + divisor_bits < len(encoded_word) else '')

    remainder = temp[0:len(divisor) - 1]
    print("Decoding Results:")
    print(f"CRC Remainder: {remainder}\n")
    return remainder


# Main Program
if __name__ == "__main__":
    print("CRC Encoder and Decoder")

    dividend = input("Enter the dividend (binary): ").strip()
    divisor = input("Enter the divisor (binary): ").strip()

    encoded_word, _ = crc_encode(dividend, divisor)
    crc_decode(encoded_word, divisor)
