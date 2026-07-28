from aqr.reconciliation.position_matcher import DiffSeverity, ReconciliationDiff


def match_active_orders(
    internal_client_ids: set[str], gateway_client_ids: set[str]
) -> list[ReconciliationDiff]:
    diffs: list[ReconciliationDiff] = []
    for client_order_id in sorted(internal_client_ids - gateway_client_ids):
        diffs.append(
            ReconciliationDiff(
                entity_type="ORDER",
                symbol=None,
                field_name="active_order",
                internal_value=client_order_id,
                gateway_value=None,
                severity=DiffSeverity.CRITICAL,
            )
        )
    for client_order_id in sorted(gateway_client_ids - internal_client_ids):
        diffs.append(
            ReconciliationDiff(
                entity_type="EXTERNAL_UNKNOWN_ORDER",
                symbol=None,
                field_name="active_order",
                internal_value=None,
                gateway_value=client_order_id,
                severity=DiffSeverity.CRITICAL,
            )
        )
    return diffs
