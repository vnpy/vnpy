from aqr.config import RiskConfig


def map_to_vnpy_risk_settings(config: RiskConfig) -> dict:
    """Translate the single AQR risk source into vnpy_riskmanager rules."""
    execution = config.execution
    return {
        "委托规模检查": {
            "active": True,
            "order_volume_limit": execution.max_order_size,
            "order_value_limit": 100_000_000,
        },
        "活动委托检查": {
            "active": True,
            "active_order_limit": execution.max_active_orders,
        },
        "每日上限检查": {
            "active": True,
            "total_order_limit": 20_000,
            "total_cancel_limit": execution.max_daily_cancels,
            "total_trade_limit": 20_000,
            "contract_order_limit": 2_000,
            "contract_cancel_limit": execution.max_daily_cancels,
            "contract_trade_limit": 2_000,
        },
        "重复报单检查": {
            "active": True,
            "duplicate_order_limit": 2,
        },
        "委托指令检查": {
            "active": True,
        },
    }
