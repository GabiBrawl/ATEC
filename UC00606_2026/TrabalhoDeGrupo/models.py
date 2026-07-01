import re
from datetime import datetime
from typing import Optional


class LogEvent:
    total_threats: int = 0

    def __init__(self, timestamp: str, ip: str, message: str) -> None:
        self.__timestamp = self._validate_timestamp(timestamp)
        self.__ip = self._validate_ip(ip)
        self.__message = message.strip()

        if type(self) is not LogEvent:
            LogEvent.total_threats += 1
        
    @staticmethod
    def _validate_ip(ip: str) -> str:
        pattern = re.compile(
            r'^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.'
            r'(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.'
            r'(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.'
            r'(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$'
        )
        if not pattern.match(ip):
            raise ValueError(f"Endereço IP inválido: {ip}")
        return ip

    @staticmethod
    def _validate_timestamp(ts: str) -> str:
        """
        Valida o formato da data/hora.

        :param ts: String no formato 'YYYY-MM-DD HH:MM:SS'
        :return: A mesma string se for válida
        :raises ValueError: Se o formato estiver incorreto
        """
        try:
            datetime.strptime(ts, "%Y-%m-%d %H:%M:%S")
        except ValueError:
            raise ValueError(f"Timestamp inválido: {ts}")
        return ts

    @property
    def timestamp(self) -> str:
        """Retorna o timestamp do evento."""
        return self.__timestamp

    @property
    def ip(self) -> str:
        """Retorna o IP de origem."""
        return self.__ip

    @property
    def message(self) -> str:
        """Retorna a mensagem do evento."""
        return self.__message

    def get_risk(self) -> int:
        """
        Método base de cálculo de risco (deve ser sobrescrito nas subclasses).
        Retorna 0 para a classe base.
        """
        return 0

    def __str__(self) -> str:
        """Representação legível do evento."""
        return f"[{self.timestamp}] {self.ip} -> {self.message} (Risco: {self.get_risk()})"

    def __repr__(self) -> str:
        """Representação técnica do evento."""
        return f"{self.__class__.__name__}(timestamp='{self.timestamp}', ip='{self.ip}', message='{self.message}')"


class AuthFailureEvent(LogEvent):
    """Evento de falha de autenticação (Risco Base = 5)."""

    BASE_RISK = 5

    def __init__(self, timestamp: str, ip: str, message: str) -> None:
        super().__init__(timestamp, ip, message)

    def get_risk(self) -> int:
        """Risco total = BASE_RISK + comprimento da mensagem."""
        return self.BASE_RISK + len(self.message)

    def __str__(self) -> str:
        return f"[{self.timestamp}] {self.ip} -> AUTH FAILURE: {self.message} (Risco: {self.get_risk()})"

    def __repr__(self) -> str:
        return (
            "AuthFailureEvent("
            f"timestamp='{self.timestamp}', "
            f"ip='{self.ip}', "
            f"message='{self.message}', "
            f"risk={self.get_risk()}"
            ")"
        )


class SqlInjectionEvent(LogEvent):
    """Evento de tentativa de SQL Injection (Risco Base = 10)."""

    BASE_RISK = 10

    def __init__(self, timestamp: str, ip: str, message: str) -> None:
        super().__init__(timestamp, ip, message)

    def get_risk(self) -> int:
        return self.BASE_RISK + len(self.message)

    def __str__(self) -> str:
        return f"[{self.timestamp}] {self.ip} -> SQL INJECTION: {self.message} (Risco: {self.get_risk()})"

    def __repr__(self) -> str:
        return (
            "SqlInjectionEvent("
            f"timestamp='{self.timestamp}', "
            f"ip='{self.ip}', "
            f"message='{self.message}', "
            f"risk={self.get_risk()}"
            ")"
        )


class PortScanEvent(LogEvent):
    """Evento de escaneamento de portas (Risco Base = 3)."""

    BASE_RISK = 3

    def __init__(self, timestamp: str, ip: str, message: str) -> None:
        super().__init__(timestamp, ip, message)

    def get_risk(self) -> int:
        return self.BASE_RISK + len(self.message)

    def __str__(self) -> str:
        return f"[{self.timestamp}] {self.ip} -> PORT SCAN: {self.message} (Risco: {self.get_risk()})"

    def __repr__(self) -> str:
        return (
            "PortScanEvent("
            f"timestamp='{self.timestamp}', "
            f"ip='{self.ip}', "
            f"message='{self.message}', "
            f"risk={self.get_risk()}"
            ")"
        )