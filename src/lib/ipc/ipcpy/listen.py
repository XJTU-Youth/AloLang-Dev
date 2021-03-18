import os
import time
import ipc_pb2

def listen(pipename):
    try:
        rd = os.open(pipename, os.O_RDONLY)
    except IOError:
        print("不存在指定管道")
    else:
        a = ''
        r=''
        while True:
            s = os.read(rd, 256)
            a += s
            tmp=r+s
            if 'end_package_from_alolang2py' in tmp:
                os.close(rd)
                return a
            r=s

def makedict(pbstr):
    dict = {}
    msg = ipc_pb2.msg()
    msg.ParseFromString(pbstr)
    for data in msg.Data:
        dict[data.id]=data.dat
    return dict

def get(dict, name):
    return dict[name]
