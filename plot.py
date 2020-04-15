#!/usr/bin/env python

import matplotlib.pyplot as plt

def plot(title, x, y, xlabel, ylabel, output):
    plt.plot(x, y)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.savefig(output)
