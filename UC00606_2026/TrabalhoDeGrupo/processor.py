import re
import sys
from typing import Optional
import whitelist

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

                if ip in whitelist:
                    continue
    except FileNotFoundError:
        print(f"Erro: Ficheiro '{log_path}' nao encontrado.")
        sys.exit(1)
    except Exception as e:
        print(f"Erro inesperado ao processar ficheiro: {e}")
        sys.exit(1)



def parse_log_line(line: str) -> Optional[tuple]:
    pattern = re.compile(
        r'^\s*(\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}:\d{2})\s*[;|]\s*'
        r'(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})\s*[;|]\s*(.+)$'
    )
    match = pattern.match(line)
    if not match:
        return None
    timestamp, ip, message = match.groups()
    return timestamp.strip(), ip.strip(), message.strip()