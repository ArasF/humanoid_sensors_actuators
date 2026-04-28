#!/usr/bin/python3

import sys
import json
import threading

import ftd2xx
import ftdi_tools


def print_hex_block(d : bytes):
    for i in range(len(d)):
        print(f"{d[i]:02x} ",end="")
        if ((i+1) % 16) == 0 and i+1 < len(d):
            print("")
    print("")



if __name__ == '__main__':

    ftdiVer = ftdi_tools.getLibraryVersionString()
    print(f"FTDI library version: {ftdiVer}")

    print("Detected FTDI devices:")

    dl = ftdi_tools.getDeviceInfoList()
    print(json.dumps(dl,indent=4))

    dev_num = None
    for ind,d in enumerate(dl):
        if d['description'] == "SkinCellAdapter":
            dev_num = ind
            break

    if dev_num is None:
        exit(1)


    dev = ftd2xx.open(dev_num)
    dev.setBaudRate(62500)
    dev.setLatencyTimer(2)
    ftdi_tools.flushRx(dev)
    dev.setTimeouts(200,0)

    a = 1
    b = 2

    a_bytes = a.to_bytes(64,'little')
    b_bytes = b.to_bytes(64,'little')

    dev.write(a_bytes)
    dev.write(b_bytes)

    c_bytes = dev.read(64)

    print("a = ")
    print_hex_block(a_bytes)

    print("b = ")
    print_hex_block(b_bytes)

    print("c = ")
    print_hex_block(c_bytes)



    a_bytes = a_bytes[0:63] + bytes([0x01])
    b_bytes = b_bytes[0:63] + bytes([0x01])

    dev.write(a_bytes)
    dev.write(b_bytes)

    c_bytes = dev.read(64)

    print("a = ")
    print_hex_block(a_bytes)

    print("b = ")
    print_hex_block(b_bytes)

    print("c = ")
    print_hex_block(c_bytes)



    a = 0xFF
    b = 2

    a_bytes = a.to_bytes(64,'little')
    b_bytes = b.to_bytes(64,'little')

    dev.write(a_bytes)
    dev.write(b_bytes)

    c_bytes = dev.read(64)

    print("a = ")
    print_hex_block(a_bytes)

    print("b = ")
    print_hex_block(b_bytes)

    print("c = ")
    print_hex_block(c_bytes)


    exit(0)