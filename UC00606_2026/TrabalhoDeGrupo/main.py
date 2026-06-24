# -*- coding: latin-1 -*-
from random import choice
import re
import sys
import typing

def display_menu() -> None:
    print("\n" + "=" * 50)
    print("ANALISADOR DE AMEAÇAS")
    print("=" * 50)
    print("1. Carregar ficheiro de logs")
    print("-" * 50)

def main() -> None:
    while True:
        display_menu()
        choice = input("Escolha uma opção: ")
        if choice == "1":
            log_path = input("Introduza o caminho do ficheiro de logs: ").strip()
            if not log_path:
                print("Caminho Inválido.")
                continue


















if __name__ == "__main__":
    main()

