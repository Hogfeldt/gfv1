#coding=utf-8
import matplotlib.pyplot as plt
import numpy as np
import os



def get_data_from_file(filepath):
    """ Read temperatures from data capture and convert to a list """
    data = []
    with open(filepath, "r") as f:
        lines = f.readlines()
        for line in lines:
            temp = line.split(",")[2].strip()
            data.append(temp)
    return data

def get_data_from_file2(filepath):
    """ Read temperatures from data capture and convert to a list """
    data = []
    with open(filepath, "r") as f:
        lines = f.readlines()
        for line in lines:
            temp = line.split(" ")[2].strip()
            data.append(temp)
    return data


# Read data files into list
exercise1 = get_data_from_file('exercise1.txt')
exercise1.pop(0)
# Sampling times for every capture
t1 = np.arange(len(exercise1))

capture2 = get_data_from_file2('capture2')
t2 = np.arange(len(capture2))


plt.plot(t1,exercise1,'ro')
plt.xlabel('Antal mellem moetrikker')
plt.ylabel('ADC output')
plt.title('Load cell linearity')
plt.show()

plt.plot(t2,capture2)
plt.xlabel('Antal maalinger med mellem moetrikker hver 100 millisekund')
plt.ylabel('ADC output')
plt.title('Load cell linearity')
plt.show()
