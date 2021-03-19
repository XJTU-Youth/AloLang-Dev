import os
import time
import ipc_pb2
import struct

def listen(pipename):
    try:
        rd = open(pipename+"_out","rb")
        wd = open(pipename+"_in","wb")
    except IOError:
        raise IOError
    else:
        while True:
            totallen = rd.read(4)
            if len(totallen)==0:
                break
            messagelen=int.from_bytes(totallen,byteorder='little')
            message = rd.read(messagelen)
            dict=makedict(message)
            dict=client.alolang_run(dict)
            retData = ipc_pb2.msg()
            retData.version=1
            retData.command=2
            for k in dict:
                varData = retData.data.add()
                varData.id = k
                varData.dat = dict[k]
            feedback=retData.SerializeToString()
            wd.write(len(feedback).to_bytes(4, byteorder="little"))
            wd.write(feedback)
            wd.flush()

def makedict(pbstr):
    dict = {}
    msg = ipc_pb2.msg()
    msg.ParseFromString(pbstr)
    for data in msg.data:
        dict[data.id]=data.dat
    return dict

def get(dict, name):
    return dict[name]
