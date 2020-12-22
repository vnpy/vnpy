import wmi
import requests


def get_iip():
    """"""
    f = requests.get("http://myip.dnsomatic.com")
    iip = f.text
    return iip


def get_lip():
    """"""
    c = wmi.WMI()

    lip = ""
    for interface in c.Win32_NetworkAdapterConfiguration(IPEnabled=1):
        lip = interface.IPAddress[0]

    return lip


def get_mac():
    """"""
    c = wmi.WMI()

    mac = ""
    for interface in c.Win32_NetworkAdapterConfiguration(IPEnabled=1):
        mac = interface.MACAddress

    return mac


def get_hd():
    """"""
    c = wmi.WMI()

    hd = ""
    for disk in c.Win32_DiskDrive():
        hd = disk.SerialNumber.strip()

    return hd


def get_terminal_info():
    """"""
    iip = ""
    iport = ""
    lip = get_lip()
    mac = get_mac()
    hd = get_hd()

    terminal_info = ";".join([
        "PC",
        f"IIP={iip}",
        f"IPORT={iport}",
        f"LIP={lip}",
        f"MAC={mac}",
        f"HD={hd}",
        "PCN=NA;CPU=NA;PI=NA;VOL=NA@NA"
    ])

    return terminal_info
