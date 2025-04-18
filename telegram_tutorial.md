# 📬 Telegram Bot Setup Guide for Automated Messaging (with Python Engine)

This tutorial walks you through how to create a Telegram bot, retrieve your chat ID, and configure the settings file to work with a Python-based `TelegramEngine` (like for alerts or log pushes).

---

## ✅ Step 1: Create a Telegram Bot via BotFather

1. Open Telegram and search for **`@BotFather`**
2. Start a chat and enter:
   ```
   /newbot
   ```
3. Follow the prompts:
   - **Bot name**: (e.g., `TradeNotifierBot`)
   - **Username**: must end in `bot` (e.g., `TradeNotifierCZ_bot`)
4. BotFather will reply with a token:
   ```
   123456789:ABCdefGhIjkLmNoPQRstuVWXyz
   ```

➡️ **Save this token** — it's your bot's API key.

---

## ✅ Step 2: Get Your Chat ID

### 🧍 For Personal Chat

1. Start a conversation with your bot (click it → press "Start").
2. Visit this URL in your browser (replace `<TOKEN>`):
   ```
   https://api.telegram.org/bot<TOKEN>/getUpdates
   ```
3. Send a message to your bot. The response will contain:
   ```json
   {
     "message": {
       "chat": {
         "id": 123456789
       }
     }
   }
   ```

🔢 Use this number as your `chat_id`.

---

### 👥 For Group or Channel

1. Add the bot to a group or channel.
2. Send a message in the group.
3. Visit:
   ```
   https://api.telegram.org/bot<TOKEN>/getUpdates
   ```
4. Look for:
   ```json
   "chat": {
     "id": -1001234567890
   }
   ```

🔢 Use this `-100...` value as your `chat_id`.

---

## ✅ Step 3: Create `setting.json`

```json
{
  "telegram": {
    "active": true,
    "token": "123456789:ABCdefGhIjkLmNoPQRstuVWXyz",
    "chat": "-1001234567890",
    "proxy": ""
  }
}
```

- `active`: set to `true` to enable Telegram
- `token`: from BotFather
- `chat`: from Step 2
- `proxy`: optional, only needed in restricted regions (e.g., `"http://127.0.0.1:1080"`)

---

## ✅ Step 4: Load the Settings in Python

```python
import json

with open("setting.json", "r") as f:
    SETTINGS = json.load(f)
```

Ensure your `TelegramEngine` class uses this `SETTINGS` dictionary.

---

## ✅ Step 5: Send a Test Message

If set up correctly:

```python
engine.send_msg("Hello from my bot!")
```

You should receive a message instantly in Telegram.

---

## 🛠 Troubleshooting

- ❗ If no message arrives, check:
  - The bot has been started or added to the group
  - Token and chat ID are correct
  - Proxy is required in your region
- 🔁 Use `/getUpdates` to verify messages are arriving

---

Happy coding! 🐍💬