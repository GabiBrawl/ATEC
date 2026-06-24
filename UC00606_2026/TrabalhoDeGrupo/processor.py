import sys
def process_log_file(log_path: str) -> None:
    try:
        with open(log_path, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.rstrip('\n')
                if not line:
                    continue
                parsed = parse_log_line(line)
                if not parsed:
                    continue
                timestamp, ip, message = parsed
    except FileNotFoundError:
        print(f"Erro: Ficheiro '{log_path}' não encontrado.")
        sys.exit(1)
    except Exception as e:
        print(f"Erro inesperado ao processar ficheiro: {e}")
        sys.exit(1)



