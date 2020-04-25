error_codes = {
    0: "没有错误",
    -1: "TCP连接没建立",
    -2: "交互通道无效",
    -3: "用户未登录",
    -4: "非本前置会话不能订阅私有流",
    -5: "重复的私有流订阅请求",
    -6: "打开私有流文件失败",
    -7: "内部通信错误",
    -8: "创建会话通道失败",
    -9: "超出流控限制",
}


def get_error_msg(error_code: int):
    try:
        return error_codes[error_code]
    except KeyError:
        return "未知错误"
