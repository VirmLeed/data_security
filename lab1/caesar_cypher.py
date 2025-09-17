def encrypt(text: str, alphabet: str, shift: int, debug: bool = False):
    text = text.replace(" ", "")
    alphabet = sorted(list(set(alphabet.replace(" ", "").lower())))

    alphabet_length = len(alphabet)

    if debug:
        print(f"alphabet length: {alphabet_length}")

    output = ""
    for letter in text:
        letter_index =alphabet.index(letter)
        output += alphabet[(letter_index+shift) % alphabet_length]

    return output


def decrypt(text: str, alphabet: str, shift: int, debug: bool = False):
    text = text.replace(" ", "")
    alphabet = sorted(list(set(alphabet.replace(" ", "").lower())))

    alphabet_length = len(alphabet)

    if debug:
        print(f"alphabet length: {alphabet_length}")

    output = ""
    for letter in text:
        letter_index = alphabet.index(letter)
        output += alphabet[(letter_index-shift) % alphabet_length]

    return output


def test():
    encrypted = encrypt("абв", "абвг", 2, True)
    print(encrypted)
    decrypted = decrypt(encrypted, "абвг", 2, True)
    print(decrypted)
