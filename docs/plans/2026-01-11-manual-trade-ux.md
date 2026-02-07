# Manual Trade UX Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Improve the manual trading panel by locking exchange to the selected gateway, adding local contract fuzzy search, adding quantity quick-fill buttons, and refreshing positions on trade events.

**Architecture:** Changes live in the manual trading panel UI (`vnpy/trader/ui/widget.py`) and rely on existing `MainEngine` contract/account/position caches. We add a local contract index for fuzzy matching, gateway→exchange locking, quick-fill helpers using available balance + latest price, and a trade-event-driven position refresh hook.

**Tech Stack:** Python 3.10+, Qt (PyQt), vn.py main engine/event engine, pytest.

### Task 1: Add trade-event refresh hook for position grid

**Files:**
- Modify: `vnpy/trader/ui/widget.py`
- Test: `tests/test_manual_trading_panel.py`

**Step 1: Write the failing test**

```python
from vnpy.trader.ui.widget import TradingWidget


def test_trading_widget_refreshes_positions_on_trade_event(qtbot, main_engine, event_engine):
    widget = TradingWidget(main_engine, event_engine)
    qtbot.addWidget(widget)
    calls = {"count": 0}

    def _refresh_positions():
        calls["count"] += 1

    widget.refresh_position = _refresh_positions  # type: ignore[attr-defined]

    event_engine.put(
        Event("eTrade", object())
    )

    assert calls["count"] == 1
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_manual_trading_panel.py::test_trading_widget_refreshes_positions_on_trade_event -v`
Expected: FAIL (event not wired)

**Step 3: Write minimal implementation**

```python
self.signal_trade.connect(self.process_trade_event)
self.event_engine.register(EVENT_TRADE, self.signal_trade.emit)


def process_trade_event(self, event: Event) -> None:
    self.refresh_position()
```

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_manual_trading_panel.py::test_trading_widget_refreshes_positions_on_trade_event -v`
Expected: PASS

**Step 5: Commit**

```bash
git add vnpy/trader/ui/widget.py tests/test_manual_trading_panel.py
git commit -m "[Mod] Refresh positions on trade"
```

### Task 2: Gateway-driven exchange lock

**Files:**
- Modify: `vnpy/trader/ui/widget.py`
- Test: `tests/test_manual_trading_panel.py`

**Step 1: Write the failing test**

```python
def test_gateway_change_locks_exchange(qtbot, main_engine, event_engine):
    widget = TradingWidget(main_engine, event_engine)
    qtbot.addWidget(widget)

    widget.gateway_combo.addItem("OKX")
    widget.exchange_combo.addItem("OKX")

    widget.gateway_combo.setCurrentText("OKX")
    widget.handle_gateway_change()

    assert widget.exchange_combo.currentText() == "OKX"
    assert not widget.exchange_combo.isEnabled()
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_manual_trading_panel.py::test_gateway_change_locks_exchange -v`
Expected: FAIL

**Step 3: Write minimal implementation**

```python
self.gateway_combo.currentTextChanged.connect(self.handle_gateway_change)


def handle_gateway_change(self) -> None:
    gateway_name = self.gateway_combo.currentText()
    exchange = self._get_gateway_default_exchange(gateway_name)
    if exchange:
        self.exchange_combo.setCurrentText(exchange.value)
        self.exchange_combo.setEnabled(False)
```

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_manual_trading_panel.py::test_gateway_change_locks_exchange -v`
Expected: PASS

**Step 5: Commit**

```bash
git add vnpy/trader/ui/widget.py tests/test_manual_trading_panel.py
git commit -m "[Mod] Lock exchange to gateway"
```

### Task 3: Local contract fuzzy search (code + name)

**Files:**
- Modify: `vnpy/trader/ui/widget.py`
- Test: `tests/test_manual_trading_panel.py`

**Step 1: Write the failing test**

```python
def test_contract_fuzzy_search_matches_name(qtbot, main_engine, event_engine, contract_factory):
    contract = contract_factory(symbol="BTC-USDT", exchange="OKX", name="比特币")
    main_engine.contracts[contract.vt_symbol] = contract

    widget = TradingWidget(main_engine, event_engine)
    qtbot.addWidget(widget)

    matches = widget.find_contract_matches("比特")
    assert any(item["vt_symbol"] == contract.vt_symbol for item in matches)
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_manual_trading_panel.py::test_contract_fuzzy_search_matches_name -v`
Expected: FAIL

**Step 3: Write minimal implementation**

```python
self.contract_index = self._build_contract_index()


def _build_contract_index(self) -> list[dict]:
    # Build list of {vt_symbol, symbol, name, exchange, gateway}


def find_contract_matches(self, text: str) -> list[dict]:
    # substring match in symbol/name (case-insensitive)
```

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_manual_trading_panel.py::test_contract_fuzzy_search_matches_name -v`
Expected: PASS

**Step 5: Commit**

```bash
git add vnpy/trader/ui/widget.py tests/test_manual_trading_panel.py
git commit -m "[Add] Local contract fuzzy search"
```

### Task 4: Quantity quick-fill (USDT amounts + position ratios)

**Files:**
- Modify: `vnpy/trader/ui/widget.py`
- Test: `tests/test_manual_trading_panel.py`

**Step 1: Write the failing test**

```python
def test_quick_fill_amount_uses_available_balance(qtbot, main_engine, event_engine):
    widget = TradingWidget(main_engine, event_engine)
    qtbot.addWidget(widget)

    widget._latest_price = 100.0
    widget._available_balance = 1000.0

    widget.apply_quick_amount(200.0)
    assert widget.volume_line.text() == "2"
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_manual_trading_panel.py::test_quick_fill_amount_uses_available_balance -v`
Expected: FAIL

**Step 3: Write minimal implementation**

```python
def apply_quick_amount(self, usdt_amount: float) -> None:
    # volume = usdt_amount / latest_price
    # validate > 0 and >= min_volume
```

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_manual_trading_panel.py::test_quick_fill_amount_uses_available_balance -v`
Expected: PASS

**Step 5: Commit**

```bash
git add vnpy/trader/ui/widget.py tests/test_manual_trading_panel.py
git commit -m "[Add] Quick fill buttons for quantity"
```

### Task 5: Wiring UI controls and refresh/fill behavior

**Files:**
- Modify: `vnpy/trader/ui/widget.py`
- Test: `tests/test_manual_trading_panel.py`

**Step 1: Write the failing test**

```python
def test_select_contract_updates_fields(qtbot, main_engine, event_engine, contract_factory):
    contract = contract_factory(symbol="ETH-USDT", exchange="OKX", name="以太坊")
    main_engine.contracts[contract.vt_symbol] = contract

    widget = TradingWidget(main_engine, event_engine)
    qtbot.addWidget(widget)

    widget.apply_contract(contract)

    assert widget.symbol_line.text() == "ETH-USDT"
    assert widget.name_line.text() == "以太坊"
    assert widget.exchange_combo.currentText() == "OKX"
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_manual_trading_panel.py::test_select_contract_updates_fields -v`
Expected: FAIL

**Step 3: Write minimal implementation**

```python
def apply_contract(self, contract: ContractData) -> None:
    # fill symbol/name/exchange/gateway + subscribe
```

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_manual_trading_panel.py::test_select_contract_updates_fields -v`
Expected: PASS

**Step 5: Commit**

```bash
git add vnpy/trader/ui/widget.py tests/test_manual_trading_panel.py
git commit -m "[Mod] Wire contract selection into panel"
```
