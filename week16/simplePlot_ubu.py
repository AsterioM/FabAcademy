import serial
import matplotlib
import matplotlib.pyplot as plt
import time
import numpy as np
def plotea():

    xdata = range(101)

    # get serial port connection
    ser = serial.Serial("/dev/ttyUSB1", 4800)

    # create the list to store data
    dataList = []
    print(len(dataList))

    while len(dataList) < 101:
    	#clean characters and make numbers the data
        data = ser.readline()
    	print(ser.readline())
        dataList.insert(0, float(data))


    l25 = []
    l200 = []
    l25 = l25 + [25]*(101 - len(l25))
    l200 = l200 + [200]*(101 - len(l200))

    # plt.ion()	#turn interactive mode on
    dataFont =  matplotlib.font_manager.FontProperties(weight='normal', size=22)
    matplotlib.rcParams['toolbar'] = 'None'			#removes ugly toolbar
    fig = plt.figure(figsize=(18,8), facecolor='white')
    ax = fig.add_subplot(111)
    ax.spines['top'].set_color('grey')			#removes visible axis
    ax.spines['bottom'].set_color('grey')		#removes visible axis
    ax.spines['left'].set_color('grey')		#removes visible axis
    ax.spines['right'].set_color('grey')		#removes visible axis


    myline, = plt.plot(dataList, color="blue", antialiased=True, lw=1.5, alpha=0.7)
    line25 = plt.plot(l25, color="grey", antialiased=True, lw=1, alpha=0.7)
    line200 = plt.plot(l200, color="grey", antialiased=True, lw=1, alpha=0.7)

    mytext = plt.text(90, 230, '0', color="blue", verticalalignment='top', horizontalalignment='left', fontproperties=dataFont, alpha=0.5, bbox=dict(facecolor='white', edgecolor='None', pad=dataFont.get_size()*0.55, alpha=0.8))

    fig.canvas.draw()
    plt.show(block = False)

    plt.ylim([0, 260])
    # frame1 = plt.gca()
    # frame1.axes.get_xaxis().set_visible(False)
    # frame1.axes.get_yaxis().set_visible(False)

    while True:
        # get data

        while ser.inWaiting() > 0:
             data = ser.readline()
    	     print(ser.readline())
#            data = float(ser.readline().strip("\n").strip("\r"))

             mytext.set_text(data)
            # insert data into list
             dataList.insert(0, float(data))

        # keep list to max 100 values
        while len(dataList) > 101:
            dataList.pop()
            myline.set_ydata(dataList)

        ax.relim()
        fig.canvas.draw()
        fig.tight_layout()


if __name__ == '__main__':
    plotea()
