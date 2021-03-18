import os
import time
import ipc_pb2

def listen(pipename):
    try:
        rd = os.open(pipename, os.O_RDONLY)
    except IOError:
        print("不存在指定管道")
    else:
       
        fl = 0
        a=''
        while True:
            s = os.read(rd, 128)
            if (len(s) == 0):
                fl+=1
                time.sleep(1)
            else:
                fl == 0
                a += s
            if (fl == 3):
                os.close(rd)
                return a

def makedict(pbstr):
    dict = {}
    msg = ipc_pb2.msg()
    msg.ParseFromString(pbstr)
    for data in msg.Data:
        dict[data.id]=data.dat
    return dict

def get(dict, name):
    return dict[name]
