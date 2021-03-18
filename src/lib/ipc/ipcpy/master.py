import os
import time
import ipc_pb2

def listen(pipename):
    try:
        rd = os.open(pipename, os.O_RDONLY)
    except IOError:
        print("不存在指定管道")
    else:
        while True:
            totallen = os.read(rd, 4)
            totallenRecv = struct.unpack('>I', totallen)[0]
            messagelen = totallenRecv - 4 
            message = os.read(rd, messagelen)
            makedict(message)

def makedict(pbstr):
    dict = {}
    msg = ipc_pb2.msg()
    msg.ParseFromString(pbstr)
    for data in msg.Data:
        dict[data.id]=data.dat
    return dict

def get(dict, name):
    return dict[name]
