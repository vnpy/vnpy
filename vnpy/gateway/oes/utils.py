import os

from vnpy.api.oes.vnoes import SGeneralClientRemoteCfgT, SGeneralClientAddrInfoT

mydir = os.path.dirname(__file__)
config_template_path = os.path.join(mydir, "config_template.ini")
with open(config_template_path, "rt", encoding='utf-8') as f:
    config_template = f.read()


def create_remote_config(server: str, username: str, password: str):
    cfg = SGeneralClientRemoteCfgT()
    cfg.username = username
    cfg.password = password
    cfg.addrCnt = 1
    cfg.addrList[0].uri = server
    cfg.clEnvId = 0
    cfg.clusterType = 0

    cfg.socketOpt.soRcvbuf = 8192
    cfg.socketOpt.soSndbuf = 8192
    cfg.socketOpt.connTimeoutMs = 5000
    cfg.socketOpt.tcpNodelay = 1
    cfg.socketOpt.quickAck = 1
    cfg.socketOpt.keepalive = 1
    cfg.socketOpt.keepIdle = 60
    cfg.socketOpt.keepIntvl = 5
    cfg.socketOpt.keepCnt = 9
    return cfg

