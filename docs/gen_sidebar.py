#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import os.path

import queue

ignore = ["_sidebar.md"]

#translate = {"language": "语言","preprocessor":"预处理器", "conditional": "条件编译"}


def dfs_showdir(path, depth):
    for item in os.listdir(path):
        if item in ignore:
            continue
        q=queue.Queue()

        newitem = path + '/' + item
        if os.path.isdir(newitem):
            q.put(newitem)
        else:
            if item != "index.md":
                continue
            show_item="未定义"
            with open(path + '/' + item, encoding='utf-8') as file:
                for line in file.readlines():
                    line = line.strip('\n')
                    #print(line[0:2])
                    if line[0:2]=='# ':
                        show_item=line[2:]
                        break
            print("  " * depth + "* [" + show_item +
                  "](" + path[2:] + "/index)")
        while not q.empty():
            dfs_showdir(q.get(), depth + 1)

if __name__ == '__main__':
    dfs_showdir('.', 0)
