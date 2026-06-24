from typing import Optional, Set

def load(whitelist_path: str) -> Set[str]:
    whitelist = set()
    with open(whitelist_path, "r", encoding="utf8") as f:
        for line in f:
            ip = line.strip()
            if ip:
                whitelist.add(ip)
    return(whitelist)