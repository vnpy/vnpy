from __future__ import annotations

from pathlib import Path

import yaml
from pydantic import BaseModel, Field
from pydantic_settings import BaseSettings, SettingsConfigDict

from aqr.domain.order import TradingEnvironment


class AccountRiskConfig(BaseModel):
    max_total_exposure: float = Field(0.60, ge=0, le=1)
    max_drawdown_halt: float = Field(0.08, ge=0, le=1)


class PositionRiskConfig(BaseModel):
    max_single_weight: float = Field(0.05, ge=0, le=1)
    max_industry_weight: float = Field(0.25, ge=0, le=1)


class ExecutionRiskConfig(BaseModel):
    max_order_size: int = Field(100_000, gt=0)
    max_orders_per_second: int = Field(2, gt=0)
    max_active_orders: int = Field(20, gt=0)
    max_daily_cancels: int = Field(50, ge=0)
    max_price_deviation: float = Field(0.02, ge=0, le=1)


class RiskConfig(BaseModel):
    account: AccountRiskConfig = AccountRiskConfig()
    position: PositionRiskConfig = PositionRiskConfig()
    execution: ExecutionRiskConfig = ExecutionRiskConfig()

    @classmethod
    def from_yaml(cls, path: Path) -> RiskConfig:
        raw = yaml.safe_load(path.read_text(encoding="utf-8")) or {}
        return cls.model_validate(raw.get("risk", raw))


class Settings(BaseSettings):
    model_config = SettingsConfigDict(
        env_file=".env",
        env_prefix="AQR_",
        extra="ignore",
        case_sensitive=False,
    )

    environment: TradingEnvironment = TradingEnvironment.PAPER
    account_id: str = "A01"
    gateway_name: str = "PAPER"
    database_url: str = (
        "postgresql+psycopg://aqr:change-me@localhost:5432/aqr_core"
    )
    outbox_poll_seconds: float = Field(0.5, gt=0)
    outbox_claim_timeout_seconds: float = Field(30, gt=0)
    heartbeat_timeout_seconds: float = Field(15, gt=0)
    order_ack_timeout_seconds: float = Field(10, gt=0)
    reconciliation_interval_seconds: float = Field(60, gt=0)
    reconciliation_snapshot_max_age_seconds: float = Field(5, gt=0)
    worker_id: str = "aqr-execution-local"
