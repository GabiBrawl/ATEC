# -*- coding: utf-8 -*-
from typing import List, Type

import processor
import whitelist
from models import AuthFailureEvent, LogEvent, PortScanEvent, SqlInjectionEvent


whitelist_path = "/home/gabi/GitHub/ATEC/UC00606_2026/TrabalhoDeGrupo/txts/whilelist_1.txt"
log_path = "/home/gabi/GitHub/ATEC/UC00606_2026/TrabalhoDeGrupo/txts/input_1.txt"


def display_menu() -> None:
    print("\n" + "=" * 50)
    print("ANALISADOR DE AMEACAS")
    print("=" * 50)
    print("1. Carregar ficheiros")
    print("2. Listagem global de ameacas")
    print("3. Listagem filtrada por categoria")
    print("0. Sair")
    print("-" * 50)


def list_events(events: List[LogEvent]) -> None:
    if not events:
        print("Nao existem ameacas carregadas.")
        return

    print("\n--- LISTAGEM GLOBAL ---")
    for idx, event in enumerate(events, start=1):
        print(f"{idx}. {event}")


def list_events_by_category(events: List[LogEvent]) -> None:
    if not events:
        print("Nao existem ameacas carregadas.")
        return

    print("\nEscolha a categoria:")
    print("1. SqlInjectionEvent")
    print("2. AuthFailureEvent")
    print("3. PortScanEvent")

    option = input("Categoria: ").strip()
    category_map: dict[str, Type[LogEvent]] = {
        "1": SqlInjectionEvent,
        "2": AuthFailureEvent,
        "3": PortScanEvent,
    }

    selected_type = category_map.get(option)
    if selected_type is None:
        print("Categoria invalida.")
        return

    filtered = [event for event in events if isinstance(event, selected_type)]
    if not filtered:
        print(f"Nao existem ocorrencias da categoria {selected_type.__name__}.")
        return

    print(f"\n--- LISTAGEM: {selected_type.__name__} ---")
    for idx, event in enumerate(filtered, start=1):
        print(f"{idx}. {event}")


def main() -> None:
    loaded_events: List[LogEvent] = []

    while True:
        display_menu()
        option = input("Input: ").strip()

        if option == "1":
            if not whitelist_path:
                print("Caminho da whitelist invalido.")
                continue

            if not log_path:
                print("Caminho do ficheiro de logs invalido.")
                continue

            ips_permitidos = whitelist.load(whitelist_path)
            loaded_events = processor.process_log_file(log_path, ips_permitidos, echo=False)
            print(f"Ficheiros carregados com sucesso. Ameacas detetadas: {len(loaded_events)}")

        elif option == "2":
            list_events(loaded_events)

        elif option == "3":
            list_events_by_category(loaded_events)

        elif option == "0":
            print("A terminar...")
            break

        else:
            print("Opcao invalida.")


if __name__ == "__main__":
    main()

