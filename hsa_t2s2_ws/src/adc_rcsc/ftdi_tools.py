#!/usr/bin/python3

"""
FTDI - tools.

Tools to simplify the use of the 'ftd2xx' module.
"""

import json
import sys
# import json
import time

from typing import List, Dict


# pip3 install git+https://github.com/snmishra/ftd2xx.git#egg=ftd2xx

import ftd2xx


def flushRx(dev : ftd2xx.FTD2XX) :
    while(1):
        size = dev.getQueueStatus()
        if size == 0:
            break
        dev.read(size)


def getDeviceInfoListRaw() -> list:
    num = ftd2xx.createDeviceInfoList()
    dil = []
    for i in range(num):
        did = ftd2xx.getDeviceInfoDetail(i,update=False)
        dil.append(did)
    return dil


def getDeviceInfoList() -> list:
    l = getDeviceInfoListRaw()
    dil = []
    for d in l:
        e = {
            'status' :      ft_device_info_list_flags_to_str(d['flags']),
            'type' :        ft_device_info_list_type_to_str(d['type']),
            # 'id' :          d['id'],
            # 'location' :    d['location'],
            'serial' :      d['serial'].decode(),
            'description' : d['description'].decode(),
        }
        dil.append(e)
    return dil    


def ft_device_info_list_type_to_str(dev_type : int) -> str:
    dtl = [
        "232BM",
        "232AM",
        "100AX",
        "UNKNOWN",
        "2232C",
        "232R",
        "2232H",
        "4232H",
        "232H",
        "X_SERIES",
    ]
    if dev_type < 0 or dev_type > 9:
        return "INVALID"
    return dtl[dev_type] 


def ft_device_info_list_flags_to_str(dev_flags : int) -> str:
        if(dev_flags == 1):
            return "OPENED"
        if(dev_flags == 2):    
            return "CLOSED"
        return "INVALID"


def getLibraryVersionString() -> str :
    ftdiVer = ftd2xx.getLibraryVersion().to_bytes(4,sys.byteorder)
    return f"{ftdiVer[2]:x}.{ftdiVer[1]:x}.{ftdiVer[0]:x}"





# if __name__ == '__main__':

#     ftdiVer = getLibraryVersionString()
#     print(f"FTDI library version: {ftdiVer}")

#     print("Detected FTDI devices:")
#     dil = getDeviceInfoList()

#     print(json.dumps(dil,indent=4))