# -*- coding: latin-1 -*-
from random import choice
import processor
import whitelist

whitelist_path = "/home/gabi/GitHub/ATEC/UC00606_2026/TrabalhoDeGrupo/txts/whilelist_1.txt"
log_path = "/home/gabi/GitHub/ATEC/UC00606_2026/TrabalhoDeGrupo/txts/input_1.txt"

def display_menu() -> None:
    print("\n" + "=" * 50)
    print("ANALISADOR DE AMEACAS")
    print("=" * 50)
    print("1. Carregar ficheiros")
    print("-" * 50)

def main() -> None:
    while True:
        display_menu()
        choice = input("Input: ")
        if choice == "1":
            # whitelist_path = input("Caminho da Whitelist: ").strip() !!!!!!!!!!!!!!!DESCOMENTAR!!!!!!!!!!!!!!!
            if not whitelist_path:
                print("Caminho invalido")
                break

            whitelist.load(whitelist_path)

            # log_path = input("Introduza o caminho do ficheiro de logs: ").strip() !!!!!!!!!!!!!!!DESCOMENTAR!!!!!!!!!!!!!!!
            if not log_path:
                print("Caminho Invalido.")
                continue

            ips_permitidos = whitelist.load(whitelist_path)
            processor.process_log_file(log_path, ips_permitidos)
    main()















if __name__ == "__main__":
    main()

