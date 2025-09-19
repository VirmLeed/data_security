import argparse
import caesar_cypher
import keyword_cypher
from pathlib import Path


def resolve_file(text: str):
    p = Path(text)
    if p.exists():
        if p.is_file():
            return p.read_text()
    return text


def main(text: str, alphabet: str, shift: int, keyword: str, out: str | None = None, debug: bool = False) -> None:
    text = resolve_file(text)
    alphabet = resolve_file(alphabet)
    keyword = resolve_file(keyword)

    print(text, alphabet, keyword)

    result = caesar_cypher.encrypt(keyword_cypher.encrypt(text, keyword, debug), alphabet, shift, debug)

    if out:
        with open(out, "w", encoding="utf-8") as f:
            f.write(result)
    else:
        print(result)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Зашифровать шифром Цезаря с ключевым словом")
    parser.add_argument("text", help="Шифруемый текст (или файл с текстом)")
    parser.add_argument("alphabet", help="Алфавит (или файл с алфавитом)")
    parser.add_argument("shift", type=int, help="Смещение шифра Цезаря")
    parser.add_argument("keyword", help="Ключевое слово (или файл с ключевым словом)")
    parser.add_argument("--out", "-o", help="Выходной файл")
    parser.add_argument("--debug", "-d", help="Дебаг вывод", action="store_true")
    args = parser.parse_args()
    main(args.text, args.alphabet, args.shift, args.keyword, args.out, args.debug)
