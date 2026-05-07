#!/usr/bin/python3

import sys
import json
import threading

import ftd2xx
import ftdi_tools

import numpy as np
import matplotlib.pyplot as plt


if __name__ == '__main__':

    values = np.genfromtxt("adc_log.csv", delimiter=",")
    print(values)

    fig, ax = plt.subplots(1,1,figsize=(12,6))

    x = np.arange(0,values.shape[0])
    y = values

    ax.plot(x,y,'b',label='ADC samples')
    ax.set_xlabel('samples')
    ax.set_ylabel('ticks')
    leg = ax.legend()
    leg.get_frame().set_alpha(0.5)

    plt.show()


    exit(0)