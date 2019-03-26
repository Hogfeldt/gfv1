import matplotlib.pyplot as plt
import numpy as np
import os


def get_data_from_file(filepath):
    """ Read temperatures from data capture and convert to a list """
    data = []
    with open(filepath, "r") as f:
        lines = f.readlines()
        for line in lines:
            temp = line.split(",")[1].strip()
            data.append(temp)
    return data


# Read data files into list
first_cap = get_data_from_file('first_capture.txt')
second_cap = get_data_from_file('second_capture.txt')
third_cap = get_data_from_file('third_capture.txt')
fifth_cap = get_data_from_file('fifth_capture.txt')
sixth_cap = get_data_from_file('sixth_capture.txt')
seventh_cap = get_data_from_file('seventh_capture.txt')
eighth_cap = get_data_from_file('eighth_capture.txt')
nineth_cap = get_data_from_file('nineth_capture.txt')


# Sampling times for every capture
t1 = np.arange(0.0, len(first_cap)/3, 1/3)
t2 = np.arange(0.0, len(second_cap)/3, 1/3)[:-1]
t3 = np.arange(0.0, len(third_cap)/3, 1/3)
t5 = np.arange(0.0, len(fifth_cap)/3, 1/3)
t6 = np.arange(0.0, len(sixth_cap)/3, 1/3)
t7 = np.arange(0.0, len(seventh_cap)/3, 1/3)
t8 = np.arange(0.0, len(eighth_cap)/3, 1/3)
t9 = np.arange(0.0, len(nineth_cap)/3, 1/3)[:-1]


# Plot captures experimenting with Kp
fig, ax = plt.subplots()
ax.plot(t1, first_cap, label='Kp = 2', color='blue')
ax.plot(t2, second_cap, label='Kp = 4', color='red')
ax.plot(t3, third_cap, label='Kp = 8', color='green')
legend = ax.legend(loc='center right', fontsize='x-large')
plt.xlabel('Time in seconds')
plt.ylabel('Temperature in degrees celsius')
plt.title('Experimenting with Kp')
plt.show()


# Plot captures experimenting with Ki
fig, ax = plt.subplots()
ax.plot(t1, first_cap, label='Ki = 1/30', color='blue')
ax.plot(t5, fifth_cap, label='Ki = 2/30', color='red')
ax.plot(t6, sixth_cap, label='Ki = 1/10', color='green')
legend = ax.legend(loc='center right', fontsize='x-large')
plt.xlabel('Time in seconds')
plt.ylabel('Temperature in degrees celsius')
plt.title('Experimenting with Ki')
plt.show()


# Plot captures experimenting to find optimal combination
fig, ax = plt.subplots()
ax.plot(t1, first_cap, label='Kp = 2, Ki = 1/30, Kd = 0', color='blue')
ax.plot(t5, fifth_cap, label='Kp = 2, Ki = 2/30, Kd = 0', color='red')
ax.plot(t7, seventh_cap, label='Kp = 4, Ki = 2/30, Kd = 0', color='green')
ax.plot(t8, eighth_cap, label='Kp = 8, Ki = 2/30, Kd = 0', color='purple')
ax.plot(t9, nineth_cap, label='Kp = 7, Ki = 5/60, Kd = 0', color='yellow')
legend = ax.legend(loc='center right', fontsize='x-large')
plt.xlabel('Time in seconds')
plt.ylabel('Temperature in degrees celsius')
plt.title('Experimenting omptimal parameter combination')
plt.show()
