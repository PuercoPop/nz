#!/usr/bin/env python

"""Iterate over the list of executables in the test directory, execute them and
report success on exit codes >= 0, failure otherwise.

"""

from os import access, devnull, listdir, X_OK
from os.path import isfile, join
from subprocess import call

TEST_DIR = "./bin/" # /bin/t
DEVNULL = open(devnull, 'wb')

def executablep(fpath):
    return isfile(fpath) and access(fpath, X_OK)

def run_test(exec_fpath):
    ret_code = call(exec_fpath, stdout=DEVNULL)
    return ret_code >= 0

if __name__ == "__main__":
    executables = [join(TEST_DIR, f) for f in listdir(TEST_DIR)]
    executables = filter(executablep, executables)

    for executable in executables:
        if not run_test(executable):
            print "Test failed: {0} :'(".format(executable)
