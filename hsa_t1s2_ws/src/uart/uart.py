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


def read_and_print_thread(dev : ftd2xx.FTD2XX, event : threading.Event):
    dev.setTimeouts(200,0)

    while not event.is_set():
        b = dev.read(1)
        if not b:
            # print("Read timeout.")
            continue
        size = dev.getQueueStatus()
        b += dev.read(size)
        # print(b)
        # print_hex_block(b)
        print(b.decode(),end="")
    print("Exit thread...")


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


    event = threading.Event()
    thread = threading.Thread(target=read_and_print_thread, args=(dev,event,))
    thread.start()

    while(True):
        try:
            cmd = input()
            if(cmd == "q"):
                break

            if(cmd == "w"):
                dev.write("Test\n".encode())

        except KeyboardInterrupt:
            break

    print("Stop.")
    event.set()
    thread.join()

    print("Thread stopped.")
    exit(0)