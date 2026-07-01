import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(__file__)))

from analyzer import ThreatAnalyzer
from models import AuthFailureEvent, LogEvent, SqlInjectionEvent


class ThreatAnalyzerUc10Tests(unittest.TestCase):
    def setUp(self) -> None:
        LogEvent.reset_total_threats()
        self.analyzer = ThreatAnalyzer()

    def test_get_incidents_by_ip_orders_by_risk_and_then_timestamp(self) -> None:
        self.analyzer.add_event(AuthFailureEvent("2024-01-01 10:00:00", "10.0.0.1", "abc"))
        self.analyzer.add_event(AuthFailureEvent("2024-01-02 10:00:00", "10.0.0.1", "def"))
        self.analyzer.add_event(SqlInjectionEvent("2024-01-03 10:00:00", "10.0.0.1", "x"))
        self.analyzer.add_event(AuthFailureEvent("2024-01-04 10:00:00", "10.0.0.2", "ghi"))

        result = self.analyzer.get_incidents_by_ip("10.0.0.1")

        self.assertEqual([event.__class__.__name__ for event in result], ["SqlInjectionEvent", "AuthFailureEvent", "AuthFailureEvent"])
        self.assertEqual([event.timestamp for event in result[:2]], ["2024-01-03 10:00:00", "2024-01-02 10:00:00"])
        self.assertEqual(result[1].timestamp, "2024-01-02 10:00:00")
        self.assertEqual(result[2].timestamp, "2024-01-01 10:00:00")


if __name__ == "__main__":
    unittest.main()
