import vnpy
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

    return mac.replace(":", "")


def get_hd():
    """"""
    c = wmi.WMI()

    hd = ""
    for disk in c.Win32_DiskDrive():
        hd = disk.SerialNumber.strip()

    return hd.upper()


def get_cpu():
    """"""
    c = wmi.WMI()

    cpu = ""
    for processor in c.Win32_Processor():
        print(processor)
        cpu = processor.ProcessorId.strip()

    return cpu.lower()


def get_terminal_info():
    """"""
    iip = "NA"
    iport = "NA"
    lip = get_lip()
    mac = get_mac()
    hd = get_hd()
    cpu = get_cpu()

    terminal_info = ";".join([
        "PC",
        f"IIP={iip}",
        f"IPORT={iport}",
        f"LIP={lip}",
        f"MAC={mac}",
        f"HD={hd}",
        f"CPU={cpu}@vn.py;V{vnpy.__version__}",
    ])

    return terminal_info
