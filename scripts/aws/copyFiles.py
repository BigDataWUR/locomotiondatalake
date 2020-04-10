# This function duplicates _n_ times all files placed in a root folder 

import argparse
import os
from distutils.dir_util import copy_tree
import errno


def main(rootdir, number):
    dest = 'generated/input'+str(number)
    target = 'generated/output'+str(number)
    
    if not os.path.exists('generated'):
        os.mkdir('generated')
    if not os.path.exists(dest):
        os.mkdir(dest)
    if not os.path.exists(target):
        os.mkdir(target)
    
    for dirName, subdirList, fileList in os.walk(rootdir):
        base = os.path.commonprefix([dirName,rootdir])
        tail = os.path.relpath(dirName,base)
        dstn = os.path.join(dest,tail)
        for i in range(int(number)):
            if(len(subdirList) < 1):
                dst = dstn + "_" + "{0:0>6}".format(i)
                print("dest",dst)
                try:
                    copy_tree(dirName, dst)
                except OSError as e:
                    # If the error was caused because the source wasn't a directory
                    if e.errno == errno.ENOTDIR:
                        shutil.copy(dirName, dst)
                    else:
                        print('Directory not copied. Error: %s' % e)


if __name__ == "__main__":
    # Configure options
    parser = argparse.ArgumentParser(description='This function duplicates _n_ times all files placed in a root folder.\nSee options below')
    parser.add_argument('--i', help='Input data folder location', default='forceplate')
    parser.add_argument('--n', help='Number of copies to generate', default=5)

    args = parser.parse_args()
    
    main(args.i, args.n)
