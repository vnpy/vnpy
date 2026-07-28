from __future__ import annotations

from dataclasses import dataclass, field

from aqr.domain.order import SubmitOrderCommand


@dataclass(slots=True)
class GatewayRouter:
    default_gateway: str
    account_gateways: dict[str, str] = field(default_factory=dict)

    def route(self, command: SubmitOrderCommand) -> str:
        gateway = self.account_gateways.get(command.account_id, self.default_gateway)
        if not gateway:
            raise RuntimeError(f"no gateway configured for account {command.account_id}")
        return gateway
