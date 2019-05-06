import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress, t, sem


def get_data_from_file(filepath):
    """ Read mass meseaurment from data capture file """
    data = list()
    with open(filepath, "r") as fd:
        lines = fd.readlines()
        for line in lines:
            m = line.split()[2]
            data.append(float(m))
        return data

def mean_confidence_interval(data_raw, confidence=0.95):
    data = 1.0 * np.array(data_raw)
    n = len(data)
    mean, std_err_mean = np.mean(data), sem(data)
    h = std_err_mean * t.ppf((1 + confidence) / 2., n-1)
    return mean, mean-h, mean+h

# Import data from files
capt_2 = get_data_from_file("../capture2")
capt_3 = get_data_from_file("../capture3")
capt_4 = get_data_from_file("../capture4")

# Reducing capt_2 to one point per mass
meas = [
    capt_2[0:30],
    capt_2[32:73],
    capt_2[77:129],
    capt_2[132:169],
    capt_2[172:203],
    capt_2[210:240],
    capt_2[243:281],
    capt_2[286:323],
    capt_2[326:354],
    capt_2[360:387],
    capt_2[389:],
]
y2 = [np.mean(i) for i in meas]
x2 = [i for i in range(0, len(y2))]

pcc_2 = linregress(x2,y2)[2]
print("PPC capt_2: %s" % str(pcc_2))

# fit capt_2 to linear function
fit_2 = np.polyfit(x2, y2, 1)
fit_fn_2 = np.poly1d(fit_2)
print("capt_2 fn: %s" % fit_fn_2)

# plot capt_2
plt.plot(x2, y2, "yo", label="capt_2_points")
plt.plot(x2, fit_fn_2(x2), "--k", label="capt_2_fit: %s" % fit_fn_2)

# Reducing capt_3 to one point per mass
meas = [
        capt_3[27:80],
        capt_3[143:191],
        capt_3[254:313],
        capt_3[378:426],
        capt_3[486:525],
        capt_3[585:623],
        capt_3[679:718],
        capt_3[775:823],
        capt_3[895:951],
        capt_3[1031:1089],
]
y3 = [np.mean(i) for i in meas]
x3 = [i for i in range(0, len(y3))]

print("Data points capt_3: %s" % y3)
mean, s1, s2 = mean_confidence_interval(y3)
print("mean: %s, s1: %s, s2: %s" % mean_confidence_interval(y3))
print("Distance to  mean: %s" % (mean-s1)) 

pcc_3 = linregress(x3,y3)[2]
print("PPC capt_3: %s" % str(pcc_3))

# fit capt_3 to linear function
fit_3 = np.polyfit(x3, y3, 1)
fit_fn_3 = np.poly1d(fit_3)

# Reducing capt_4 to one point per mass
meas = [
    capt_4[0:167],
    capt_4[169:206],
    capt_4[210:259],
    capt_4[254:285],
    capt_4[287:333],
    capt_4[337:383],
    capt_4[388:438],
    capt_4[444:489],
    capt_4[495:537],
    capt_4[542:583],
    capt_4[587:]
]
y4 = [np.mean(i) for i in meas]
x4 = [i for i in range(0, len(y4))]

pcc_4 = linregress(x4,y4)[2]
print("PPC capt_4: %s" % str(pcc_4))

# fit capt_4 to linear function
fit_4 = np.polyfit(x4, y4, 1)
fit_fn_4 = np.poly1d(fit_4)
print("capt_4 fn: %s" % fit_fn_4)

# plot capt_4
plt.plot(x4, y4, "ro",  label="capt_4_points")
plt.plot(x4, fit_fn_4(x4), "-k", label="capt_4_fit: %s" % fit_fn_4)

plt.legend()
plt.title("Zero-drift and Sensitivity-drift")
plt.ylabel("Weight / kg")
plt.xlabel("Number of nuts")
plt.show()
