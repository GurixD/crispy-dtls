#!/usr/bin/env python3

from fileinput import filename
import os 
import glob


dir_path = os.path.dirname(os.path.realpath(__file__))
dtls_dir = dir_path + '/../dtls'

filenames = []
for root, dirs, files in os.walk(dtls_dir):
    for file in files:
        if file.endswith(".h") or file.endswith(".hpp") or file.endswith(".cpp"):
            rel_dir = os.path.relpath(root, dtls_dir)
            if(rel_dir != '.'):
                file = rel_dir + '/' + file
            filenames.append(file)

print(' '.join(filenames))