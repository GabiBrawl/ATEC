from __future__ import annotations

from collections import defaultdict
from typing import Dict, List, Set, Type

import processor
from classify import classify_event
from models import AuthFailureEvent, LogEvent


class ThreatAnalyzer:
	def __init__(self) -> None:
		self._events: List[LogEvent] = []
		self._traffic_by_ip: Dict[str, int] = defaultdict(int)
		self._auth_failures_by_ip: Dict[str, int] = defaultdict(int)
		self._brute_force_ips: Set[str] = set()

	@property
	def events(self) -> List[LogEvent]:
		return list(self._events)

	def clear(self) -> None:
		self._events.clear()
		self._traffic_by_ip.clear()
		self._auth_failures_by_ip.clear()
		self._brute_force_ips.clear()

	def add_event(self, event: LogEvent) -> None:
		self._events.append(event)
		self._traffic_by_ip[event.ip] += 1

		if isinstance(event, AuthFailureEvent):
			self._auth_failures_by_ip[event.ip] += 1
			if self._auth_failures_by_ip[event.ip] >= 5:
				self._brute_force_ips.add(event.ip)

	def load_from_file(self, log_path: str, whitelist_set: Set[str], reset: bool = True) -> List[LogEvent]:
		if reset:
			self.clear()

		events = processor.process_log_file(log_path, whitelist_set, echo=False)
		for event in events:
			self.add_event(event)
		return list(self._events)

	def list_events(self) -> List[LogEvent]:
		return list(self._events)

	def list_events_by_type(self, event_type: Type[LogEvent]) -> List[LogEvent]:
		return [event for event in self._events if isinstance(event, event_type)]

	def get_incidents_by_ip(self, ip: str) -> List[LogEvent]:
		"""Devolve o histórico de incidentes de um IP ordenado por risco desc e timestamp desc."""
		filtered_events = [event for event in self._events if event.ip == ip]
		return sorted(filtered_events, key=lambda event: (event.get_risk(), event.timestamp), reverse=True)

	def get_traffic_by_ip(self) -> Dict[str, int]:
		return dict(self._traffic_by_ip)

	def get_auth_failures_by_ip(self) -> Dict[str, int]:
		return dict(self._auth_failures_by_ip)

	def get_brute_force_ips(self) -> List[str]:
		return sorted(self._brute_force_ips)

	def get_total_events(self) -> int:
		return len(self._events)

	def has_brute_force_alerts(self) -> bool:
		return bool(self._brute_force_ips)
