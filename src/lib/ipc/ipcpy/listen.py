import os
import time

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
                
            
                
            
            