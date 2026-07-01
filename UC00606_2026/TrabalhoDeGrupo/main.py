# -*- coding: utf-8 -*-
from typing import List, Type

from analyzer import ThreatAnalyzer
import processor
import whitelist
from models import AuthFailureEvent, LogEvent, PortScanEvent, SqlInjectionEvent


#whitelist_path = "/home/gabi/GitHub/ATEC/UC00606_2026/TrabalhoDeGrupo/txts/whilelist_1.txt"
#log_path = "/home/gabi/GitHub/ATEC/UC00606_2026/TrabalhoDeGrupo/txts/input_1.txt"
whitelist_path = "C:\\Users\\ruijo\\ATEC\\UC00606_2026\\TrabalhoDeGrupo\\txts\\whilelist_1.txt"
log_path = "C:\\Users\\ruijo\\ATEC\\UC00606_2026\\TrabalhoDeGrupo\\txts\\input_1.txt"

def display_menu() -> None:
    print("\n" + "=" * 50)
    print("ANALISADOR DE AMEACAS")
    print("=" * 50)
    print("1. Carregar ficheiros")
    print("2. Listagem global de ameacas")
    print("3. Listagem filtrada por categoria")
    print("4. Monitorizacao global de estado")
    print("5. Origens de forca bruta")
    print("6. Pesquisa isolada por IP")
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
    analyzer = ThreatAnalyzer()

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
            analyzer.load_from_file(log_path, ips_permitidos, reset=True)
            print(f"Ficheiros carregados com sucesso. Ameacas detetadas: {analyzer.get_total_events()}")
            print(f"Total global de ameacas na sessao: {LogEvent.get_total_threats()}")
            if analyzer.has_brute_force_alerts():
                print("Alertas de forca bruta detetados nas seguintes origens:")
                for ip in analyzer.get_brute_force_ips():
                    print(f"- {ip}")

        elif option == "2":
            list_events(analyzer.list_events())

        elif option == "3":
            list_events_by_category(analyzer.list_events())

        elif option == "4":
            print(f"Total global de ameacas na sessao: {LogEvent.get_total_threats()}")

            traffic_by_ip = analyzer.get_traffic_by_ip()
            if traffic_by_ip:
                print("Volume de trafego por IP:")
                for ip, volume in sorted(traffic_by_ip.items()):
                    print(f"- {ip}: {volume}")
            else:
                print("Nao existem eventos carregados.")

            auth_failures_by_ip = analyzer.get_auth_failures_by_ip()
            if auth_failures_by_ip:
                print("Falhas de autenticacao por IP:")
                for ip, failures in sorted(auth_failures_by_ip.items()):
                    print(f"- {ip}: {failures}")

        elif option == "5":
            brute_force_ips = analyzer.get_brute_force_ips()
            if not brute_force_ips:
                print("Nao existem origens classificadas como forca bruta.")
            else:
                print("Origens classificadas como forca bruta:")
                for ip in brute_force_ips:
                    print(f"- {ip}")

        elif option == "6":
            ip = input("IP para pesquisa: ").strip()
            incidents = analyzer.get_incidents_by_ip(ip)
            if not incidents:
                print(f"Nao existem incidentes associados ao IP {ip}.")
            else:
                print(f"\n--- INCIDENTES PARA {ip} ---")
                for idx, event in enumerate(incidents, start=1):
                    print(f"{idx}. {event}")

        elif option == "0":
            print("A terminar...")
            break

        else:
            print("Opcao invalida.")


if __name__ == "__main__":
    main()

