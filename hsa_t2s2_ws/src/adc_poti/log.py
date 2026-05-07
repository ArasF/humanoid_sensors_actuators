#!/usr/bin/python3

import sys
import json
import threading

import ftd2xx
import ftdi_tools

import numpy as np


def print_hex_block(d : bytes):
    for i in range(len(d)):
        print(f"{d[i]:02x} ",end="")
        if ((i+1) % 16) == 0 and i+1 < len(d):
            print("")
    print("")


def read_and_print_thread(
        dev : ftd2xx.FTD2XX, 
        exit_event : threading.Event,
        start_log_event : threading.Event,
        stop_log_event : threading.Event):
    
    dev.setTimeouts(200,0)

    log_started : bool = False

    data_list = []

    while not exit_event.is_set():
        b = dev.read(1)
        if not b:
            # print("Read timeout.")
            continue
        size = dev.getQueueStatus()
        b += dev.read(size)
        # print(b)
        # print_hex_block(b)
        # print(b.decode(),end="")

        if start_log_event.is_set():
            start_log_event.clear()
            if not log_started:       
                log_started = True
                start_log_event.clear()
                data_list = []
                print(f"Log started.")

        if stop_log_event.is_set():
            stop_log_event.clear()
            if log_started:
                log_started = False
                print(f"Log stopped.")
                mat = np.array(data_list)
                np.savetxt("adc_log.csv", mat, delimiter=",", fmt='%d')
        
        if log_started:
            for d in b:
                data_list.append(d)
                print(d)

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


    exit_event = threading.Event()
    start_log_event = threading.Event()
    stop_log_event = threading.Event()
    thread = threading.Thread(target=read_and_print_thread, args=(dev,exit_event,start_log_event,stop_log_event))
    thread.start()

    while(True):
        try:
            cmd = input()
            if(cmd == "q"):
                break

            if(cmd == "s"):
                start_log_event.set()

            if(cmd == "e"):
                stop_log_event.set()

            # if(cmd == "w"):
            #     dev.write("Test\n".encode())

        except KeyboardInterrupt:
            break

    print("Stop.")
    exit_event.set()
    thread.join()

    print("Thread stopped.")
    exit(0)