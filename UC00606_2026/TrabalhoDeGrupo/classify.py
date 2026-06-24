def classify_event(timestamp: str, ip: str, message: str) -> Optional[LogEvent]:
    msg_lower = message.lower()
    if any(keyword in msg_lower for keyword in ['syntax error', 'union select', 'drop table']):
        return SqlInjectionEvent(timestamp, ip, message)
    elif any(keyword in msg_lower for keyword in ['failed password', 'authentication failure', 'root login refused']):
        return AuthFailureEvent(timestamp, ip, message)
    elif any(keyword in msg_lower for keyword in ['port closed', 'connection refused', 'tcp syn stealth']):
        return PortScanEvent(timestamp, ip, message)
    else:
        return None