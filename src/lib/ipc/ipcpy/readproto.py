import ipc_pb2
def addDict(msg):
    dict={}
    for data in msg.Data:
        dict[data.id]=data.dat
    return dict

def get(dict, name):
    return dict[name]