import serial
import time
import pandas as pd

esp32=serial.Serial("COM5",115200,timeout=0.5)

dataset=[]
batch=0
while True:
    if(esp32.inWaiting()>0):
        data=esp32.readline()
        data=data.decode('utf-8')
        if(data.startswith("#")):
            data=data.split(",")
            h=float(data[1])
            t=float(data[2])
            result=data[3]
            dummy=[h,t,result]
            print(dummy)
            batch+=1
            dataset.append(dummy)
            if(batch==50):
                df=pd.DataFrame(dataset)
                df.to_csv('iotdata.csv')
                batch=0
            print(dataset)