import numpy as np
import matplotlib.pyplot as plt

#first generate some datapoint for a randomly sampled noisy sinewave
x = np.random.random(1000)*10
noise = np.random.normal(scale=0.3,size=len(x))
y = np.sin(x) + noise

#plot the data
plt.plot(x,y,'ro',alpha=0.3,ms=4,label='data')
plt.xlabel('Time')
plt.ylabel('Intensity')

#define a moving average function
def moving_average(x,y,step_size=.1,bin_size=1):
    bin_centers  = np.arange(np.min(x),np.max(x)-0.5*step_size,step_size)+0.5*step_size
    bin_avg = np.zeros(len(bin_centers))

    for index in range(0,len(bin_centers)):
        bin_center = bin_centers[index]
        items_in_bin = y[(x>(bin_center-bin_size*0.5) ) & (x<(bin_center+bin_size*0.5))]
        bin_avg[index] = np.mean(items_in_bin)

    return bin_centers,bin_avg

#plot the moving average
bins, average = moving_average(x,y)
plt.plot(bins, average,label='moving average')

plt.show()