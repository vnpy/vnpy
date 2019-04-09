from pathlib import Path

from ctypes import (cdll, CFUNCTYPE,
                    c_bool, c_char_p, c_long, c_int,
                    c_void_p, create_string_buffer, byref)


DLL_PATH = Path(__file__).parent.joinpath("FixApi.dll")
APEX = cdll.LoadLibrary(str(DLL_PATH))

REPLY_FUNC = CFUNCTYPE(c_bool, c_long, c_long, c_int)
PUSH_FUNC = CFUNCTYPE(c_bool, c_long, c_long, c_long, c_char_p)
CONN_FUNC = CFUNCTYPE(c_bool, c_long, c_long, c_void_p)


class ApexApi:
    """
    Wrapper for APEX C API.
    """

    def __init__(self):
        """Constructor"""
        self.reply_call_func = REPLY_FUNC(self.on_reply)
        self.push_call_func = PUSH_FUNC(self.on_push)
        self.conn_call_func = CONN_FUNC(self.on_conn)

    def initialize(self):
        """初始化"""
        n = APEX.Fix_Initialize()
        return bool(n)

    def set_app_info(self, name: str, version: str):
        """设置应用信息"""
        n = APEX.Fix_SetAppInfo(to_bytes(name), to_bytes(version))
        return bool(n)

    def uninitialize(self):
        """卸载库"""
        n = APEX.Fix_Uninitialize()
        return bool(n)

    def set_default_info(self, user: str, wtfs: str, fbdm: str, dest: str):
        """设置默认信息"""
        n = APEX.Fix_SetDefaultInfo(
            to_bytes(user),
            to_bytes(wtfs),
            to_bytes(fbdm),
            to_bytes(dest)
        )
        return bool(n)

    def connect(self, address: str, khh: str, pwd: str, timeout: int):
        """连接交易"""
        conn = APEX.Fix_Connect(
            to_bytes(address),
            to_bytes(khh),
            to_bytes(pwd),
            timeout
        )
        return conn

    def connect_ex(
        self, address: str, khh: str, pwd: str, file_cert: str,
        cert_pwd: str, file_ca: str, procotol: str, verify: bool,
        timeout: int
    ):
        """连接交易"""
        conn = APEX.Fix_ConnectEx(
            to_bytes(address),
            to_bytes(khh),
            to_bytes(pwd),
            to_bytes(file_cert),
            to_bytes(cert_pwd),
            to_bytes(file_ca),
            to_bytes(procotol),
            verify,
            timeout
        )
        return conn

    def close(self, conn: int):
        """断开"""
        n = APEX.Fix_Close(conn)
        return bool(n)

    def allocate_session(self, conn: int):
        """分配会话"""
        sess = APEX.Fix_AllocateSession(conn)
        return sess

    def release_session(self, sess: int):
        """释放会话"""
        n = APEX.Fix_ReleaseSession(sess)
        return bool(n)

    def set_timeout(self, sess: int, timeout: int):
        """设置会话超时时间"""
        n = APEX.Fix_SetTimeOut(sess, c_long(timeout))
        return bool(n)

    def set_wtfs(self, sess: int, wtfs: str):
        """设置委托方式"""
        n = APEX.Fix_SetWTFS(sess, to_bytes(wtfs))
        return bool(n)

    def set_fbdm(self, sess: int, fbdm: str):
        """设置来源营业部"""
        n = APEX.Fix_SetFBDM(sess, to_bytes(fbdm))
        return bool(n)

    def set_dest_fbdm(self, sess: int, fbdm: str):
        """设置目标营业部"""
        n = APEX.Fix_SetDestFBDM(sess, to_bytes(fbdm))
        return bool(n)

    def set_node(self, sess: int, node: str):
        """设置业务站点"""
        n = APEX.Fix_SetNode(sess, to_bytes(node))
        return bool(n)

    def set_gydm(self, sess: int, gydm: str):
        """设置柜员号"""
        n = APEX.Fix_SetGYDM(sess, to_bytes(gydm))
        return bool(n)

    def create_head(self, sess: int, func: int):
        """设置会话功能号"""
        n = APEX.Fix_CreateHead(sess, func)
        return bool(n)

    def set_string(self, sess: int, val: str):
        """设置字符串请求数据"""
        n = APEX.Fix_SetString(sess, val)
        return bool(n)

    def set_long(self, sess: int, val: int):
        """设置整形请求数据"""
        n = APEX.Fix_SetLong(sess, val)
        return bool(n)

    def set_double(self, sess: int, val: float):
        """设置浮点数请求数据"""
        n = APEX.Fix_SetDouble(sess, val)
        return bool(n)

    def run(self, sess: int):
        """运行"""
        n = APEX.Fix_Run(sess)
        return bool(n)

    def async_run(self, sess: int):
        """异步运行"""
        n = APEX.Fix_AsyncRun(sess)
        return bool(n)

    def is_replyed(self, sess: int, msec: int):
        """是否收到应答"""
        n = APEX.Fix_IsReplyed(sess, msec)
        return bool(n)

    def cancel(self, sess: int):
        """取消应答等待"""
        n = APEX.Fix_Cancel(sess, sess)
        return bool(n)

    def get_code(self, sess: int):
        """获取错误代码"""
        return APEX.Fix_GetCode(sess)

    def get_err_msg(self, sess: int):
        """获取错误信息"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetErrMsg(sess, out, size)
        return out.value

    def get_count(self, sess: int):
        """获取行数"""
        return APEX.Fix_GetCount(sess)

    def get_item(self, sess: int, fid: int, row: int):
        """获取字符串内容"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetItem(sess, fid, out, size, row)
        return out.value

    def get_long(self, sess: int, fid: int, row: int):
        """获取整形内容"""
        val = APEX.Fix_GetLong(sess, fid, row)
        return val

    def get_double(self, sess: int, fid: int, row: int):
        """获取浮点型内容"""
        val = APEX.Fix_GetDouble(sess, fid, row)
        return val

    def get_have_item(self, sess: int, fid: int, row: int):
        """查看指定应答数据"""
        n = APEX.Fix_HaveItem(sess, fid, row)
        return bool(n)

    def set_token(self, sess: int, token: str):
        """设置业务令牌"""
        n = APEX.Fix_SetToken(sess, token)
        return bool(n)

    def get_token(self, sess: int):
        """获取业务令牌"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetToken(sess, out, size)
        return out.value

    def encode(self, data: str):
        """加密"""
        data = to_bytes(data)
        buf = create_string_buffer(data, 512)
        APEX.Fix_Encode(buf)
        return to_unicode(buf.value)

    def add_backup_svc_addr(self, address: str):
        """设置业务令牌"""
        address = to_bytes(address)
        n = APEX.Fix_AddBackupSvrAddr(address)
        return bool(n)

    def set_conn_event(self, conn: int):
        """设置连接状态回调函数"""
        n = APEX.Fix_SetConnEvent(conn, self.conn_call_func)
        return bool(n)

    def is_connect(self, conn: int):
        """检查连接状态"""
        n = APEX.Fix_IsConnect(conn)
        return bool(n)

    def subscribe_by_customer(self, conn: int, svc: int, khh: str, pwd: str):
        """订阅数据"""
        func = APEX[108]
        n = func(conn, svc, self.push_call_func,
                 to_bytes(""), to_bytes(khh), to_bytes(pwd))

        return n

    def unsubscribe_by_handle(self, handle: int):
        """退订推送"""
        n = APEX.Fix_UnSubscibeByHandle(handle)
        return bool(n)

    def get_column_count(self, sess: int, row: int):
        """获取列数"""
        return APEX.Fix_GetColumnCount(sess, row)

    def get_val_with_id_by_index(self, sess: int, row: int, col: int):
        """根据行列获取数据"""
        s = 256
        buf = create_string_buffer(b"", s)
        fid = c_long(0)
        size = c_int(s)

        APEX.Fix_GetValWithIdByIndex(
            sess, row, col, byref(fid), buf, byref(size))
        return fid.value, to_unicode(buf.value)

    def set_system_no(self, sess: int, val: str):
        """设置系统编号"""
        n = APEX.Fix_SetSystemNo(sess, to_bytes(val))
        return bool(n)

    def set_default_system_no(self, val: str):
        """设置默认系统编号"""
        n = APEX.Fix_SetDefaultSystemNo(to_bytes(val))
        return bool(n)

    def set_auto_reconnect(self, conn: int, reconnect: int):
        """设置自动连接"""
        n = APEX.Fix_SetAutoReconnect(conn, reconnect)
        return bool(n)

    def get_auto_reconnect(self, conn: int):
        """获取自动连接状态"""
        n = APEX.Fix_GetAutoReconnect(conn)
        return bool(n)

    def create_req(self, sess: int, func: int):
        """创建任务"""
        n = APEX.Fix_CreateReq(sess, func)
        return bool(n)

    def get_item_buf(self, sess, row):
        """获取缓存数据"""
        size = 1024
        outlen = c_int(size)
        buf = create_string_buffer(b"", size)

        APEX.Fix_GetItemBuf(sess, buf, byref(outlen), row)
        return buf

    def set_item(self, sess: int, fid: int, val: str):
        """设置请求内容"""
        n = APEX.Fix_SetString(sess, fid, to_bytes(val))
        return bool(n)

    def get_last_err_msg(self):
        """获取错误信息"""
        size = 256
        out = create_string_buffer(b"", size)

        APEX.Fix_GetLastErrMsg(out, size)
        return to_unicode(out.value)

    def reg_reply_call_func(self, sess: int = 0):
        """注册回调函数"""
        if not sess:
            n = APEX.Fix_RegReplyCallFunc(c_void_p(None), self.reply_call_func)
        else:
            n = APEX.Fix_RegReplyCallFunc(sess, self.reply_call_func)
        return bool(n)

    def on_reply(self, conn: int, sess: int, recv: int):
        """异步回调函数（需要继承）"""
        return True

    def on_push(self, conn: int, sess: int, sub: int, data: str):
        """推送回调（需要继承）"""
        return True

    def on_conn(self, conn: int, event, recv):
        """连接回调（需要继承）"""
        return True


def to_bytes(data: str):
    """
    将unicode字符串转换为bytes
    """
    try:
        bytes_data = data.encode("GBK")
        return bytes_data
    except AttributeError:
        return data


def to_unicode(data: bytes):
    """
    将bytes字符串转换为unicode
    """
    return data.decode("GBK")
