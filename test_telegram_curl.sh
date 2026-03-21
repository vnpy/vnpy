#!/bin/bash

echo "============================================================"
echo "🧪 Telegram API 测试脚本"
echo "============================================================"
echo ""

# 配置
BOT_TOKEN="8562753482:AAHVTckHvuH60HQ2DYQN-6rTnLxagqpKZGI"
CHAT_ID="8420636030"

# 1. 测试获取Bot信息
echo "1️⃣ 测试获取Bot信息..."
echo "   命令: curl -s https://api.telegram.org/bot${BOT_TOKEN:0:15}.../getMe"
RESPONSE=$(curl -s "https://api.telegram.org/bot${BOT_TOKEN}/getMe")
echo "   响应: $RESPONSE"
echo ""

# 检查是否成功
if echo "$RESPONSE" | grep -q '"ok":true'; then
    BOT_NAME=$(echo "$RESPONSE" | grep -o '"first_name":"[^"]*"' | cut -d'"' -f4)
    echo "   ✅ Bot连接成功！名称: $BOT_NAME"
else
    echo "   ❌ Bot连接失败"
    echo "   可能原因: 网络无法访问Telegram，需要代理"
fi
echo ""

# 2. 测试发送消息
echo "2️⃣ 测试发送消息到Chat ID: $CHAT_ID..."
MESSAGE="🚀 自动交易系统测试%0A%0A✅ 配置加载成功%0A📊 交易对: DOGE-USDT-SWAP.OKX%0A⚙️ 策略: DoubleMA%0A   快线=18%0A   慢线=20%0A%0A⏳ 系统测试完成！"

echo "   命令: curl -s -X POST https://api.telegram.org/bot.../sendMessage"
RESPONSE=$(curl -s -X POST \
    "https://api.telegram.org/bot${BOT_TOKEN}/sendMessage" \
    -d "chat_id=${CHAT_ID}" \
    -d "text=🚀 自动交易系统测试

✅ 配置加载成功
📊 交易对: DOGE-USDT-SWAP.OKX
⚙️ 策略: DoubleMA
   快线=18
   慢线=20

⏳ 系统测试完成！" \
    -d "parse_mode=HTML")

echo "   响应: $RESPONSE"
echo ""

if echo "$RESPONSE" | grep -q '"ok":true'; then
    echo "   ✅ 消息发送成功！请检查你的Telegram"
else
    echo "   ❌ 消息发送失败"
    ERROR_CODE=$(echo "$RESPONSE" | grep -o '"error_code":[0-9]*' | cut -d':' -f2)
    if [ "$ERROR_CODE" = "400" ]; then
        echo "   错误: Chat ID不存在或Bot未加入该聊天"
        echo "   解决: 给你的Bot发送 /start"
    elif [ "$ERROR_CODE" = "401" ]; then
        echo "   错误: Bot Token无效"
    else
        echo "   错误码: $ERROR_CODE"
    fi
fi
echo ""

# 3. 获取更新（查看最近的消息）
echo "3️⃣ 获取最近的聊天记录..."
RESPONSE=$(curl -s "https://api.telegram.org/bot${BOT_TOKEN}/getUpdates?limit=5")
echo "   响应: $RESPONSE"
echo ""

if echo "$RESPONSE" | grep -q '"ok":true'; then
    UPDATE_COUNT=$(echo "$RESPONSE" | grep -o '"update_id":[0-9]*' | wc -l)
    echo "   ✅ 获取到 $UPDATE_COUNT 条更新记录"
    
    # 提取Chat ID
    FOUND_CHAT_ID=$(echo "$RESPONSE" | grep -o '"chat":{"id":[0-9]*' | head -1 | grep -o '[0-9]*')
    if [ -n "$FOUND_CHAT_ID" ]; then
        echo "   📌 从记录中找到Chat ID: $FOUND_CHAT_ID"
        if [ "$FOUND_CHAT_ID" != "$CHAT_ID" ]; then
            echo "   ⚠️  注意: 这个Chat ID与你配置的 $CHAT_ID 不一致"
            echo "   建议更新配置文件中的chat_id为: $FOUND_CHAT_ID"
        fi
    fi
else
    echo "   ❌ 无法获取更新"
fi
echo ""

echo "============================================================"
echo "📋 测试完成"
echo "============================================================"
echo ""
echo "如果以上测试都失败，可能是网络问题。"
echo "可以尝试使用代理:"
echo ""
echo "# 使用socks5代理"
echo "curl -x socks5://127.0.0.1:10808 https://api.telegram.org/bot.../getMe"
echo ""
echo "# 使用http代理"
echo "curl -x http://127.0.0.1:10809 https://api.telegram.org/bot.../getMe"
