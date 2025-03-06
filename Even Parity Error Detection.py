def add_even_parity(dataword):
    """Add even parity bit to the dataword."""
    parity = dataword.count('1') % 2
    # If odd number of 1s, add a parity bit of 1 to make it even
    parity_bit = '1' if parity != 0 else '0'
    return dataword + parity_bit

def check_even_parity(codeword):
    """Check if the codeword has even parity."""
    return codeword.count('1') % 2 == 0

def main():
    print("=== Even Parity Error Detection ===")
    # User input
    dataword = input("Enter the binary dataword (e.g., 1010): ").strip()
    if not all(bit in '01' for bit in dataword):
        print("Invalid dataword. Please enter a binary string.")
        return

    # Encoding
    encoded = add_even_parity(dataword)
    print(f"Encoded Dataword (with parity bit): {encoded}")

    # Decoding
    n = int(input("Enter the number of times want to check = \n"))
    while n!=0 :
        received = input("Enter the received codeword (e.g., 10101): ")
        if not all(bit in '01' for bit in received):
            print("Invalid codeword. Please enter a binary string.")
            return

    # Check syndrome
        if check_even_parity(received):
            print(f"Syndrome: 0 (No Error Detected)\nFinal Dataword: {received[0:len(received)-1]}")
        else:
            print(f"Syndrome: 1 (Error Detected)\nFinal Dataword: No valid dataword")
        n = n-1

if __name__ == "__main__":
    main()
