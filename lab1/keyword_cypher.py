def encrypt(text: str, keyword: str, debug: bool = False):
    text = text.replace(" ", "").lower()
    keyword = "".join(keyword.replace(" ", "").lower())

    keyword_length = len(keyword)
    text_length = len(text)

    order = sorted(range(keyword_length), key=lambda i: keyword[i])
    
    if debug:
        print(f"Text length {text_length} Kw length {keyword_length}")
        indexes = sorted(list(set(keyword)))
        print("".join([str(indexes.index(letter)) for letter in keyword]))
        for i in range(0, text_length, keyword_length):
            print(text[i:i+keyword_length])
        print()

    output = ""
    for column in order:
        for index in range(column, text_length, keyword_length):
            output += text[index]
    
    return output


def decrypt(text: str, keyword: str, debug: bool = False) -> str:
    text = text.replace(" ", "").lower()
    keyword = "".join(keyword.replace(" ", "").lower())

    keyword_length = len(keyword)
    text_length = len(text)

    order = sorted(range(keyword_length), key=lambda i: keyword[i])

    rows = (text_length + keyword_length - 1) // keyword_length
    # full_columns = text_length % keyword_length
    full_columns = text_length % keyword_length
    if not full_columns:
        full_columns = keyword_length

    if debug:
        print(f"Text length {text_length} Kw length {keyword_length}")
        print(f"Rows: {rows}, Full columns: {full_columns}")

    column_lengths = []
    for index in range(keyword_length):
        column_index = order[index]
        length = rows if column_index < full_columns else rows - 1
        column_lengths.append(max(0, length))

    if debug:
        print(f"Column lengths: {column_lengths}")

    columns = []
    index = 0
    for length in column_lengths:
        columns.append(text[index:index+length])
        index += length

    if debug:
        print("Columns:")
        for row in range(rows):
            for column in columns:
                if len(column) > row:
                    print(column[row], end="")
                else:
                    print(end=" ")
            print()

    sorted_columns = [""] * keyword_length
    for index, column_index in enumerate(order):
        sorted_columns[column_index] = columns[index]

    if debug:
        print("Sorted columns:")
        for row in range(rows):
            for column in sorted_columns:
                if len(column) > row:
                    print(column[row], end="")
                else:
                    print(end=" ")
            print()
        print()

    output = []
    for row in range(rows):
        for column in range(keyword_length):
            if row < len(sorted_columns[column]):
                output.append(sorted_columns[column][row])

    return "".join(output)

def test():
    encrypted = encrypt("Прикладная математикабв", "шифр", True)
    print(encrypted)
    print()
    decrypted = decrypt(encrypted, "Шифр", True)
    print(decrypted)
