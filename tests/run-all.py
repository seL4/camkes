#!/usr/bin/env python
#
# Copyright 2016, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

import argparse, multiprocessing, os, stat, subprocess, sys

MY_DIR = os.path.abspath(os.path.dirname(__file__))

def main(argv):
    parser = argparse.ArgumentParser(
        description='run CAmkES integration tests')
    parser.add_argument('--jobs', '-j', type=int,
        default=multiprocessing.cpu_count(), help='number of parallel jobs')
    parser.add_argument('--verbose', '-v', action='store_true',
        help='be verbose with output')
    opts = parser.parse_args(argv[1:])

    result = 0

    pipes = {}
    if not opts.verbose:
        pipes['stdout'] = pipes['stderr'] = subprocess.PIPE

    for t in sorted(os.listdir(MY_DIR)):
        path = os.path.join(MY_DIR, t)
        mode = os.stat(path).st_mode
        if t != os.path.basename(__file__) and not stat.S_ISDIR(mode) and \
                os.access(path, os.X_OK):
            sys.stdout.write(' Running %s ... ' % t)
            sys.stdout.flush()
            p = subprocess.Popen([path, str(opts.jobs)],
                cwd=os.path.join(MY_DIR, '../../..'), **pipes)
            stdout, stderr = p.communicate()
            if p.returncode == 0:
                sys.stdout.write('\033[32mPassed\033[0m\n')
            else:
                result = p.returncode
                sys.stdout.write('\033[31mFailed\033[0m\n')
                if not opts.verbose:
                    sys.stdout.write(' -- stdout %s --\n%s' % (t, stdout))
                    sys.stderr.write(' -- stderr %s --\n%s' % (t, stderr))
                sys.stdout.flush()
                sys.stderr.flush()

    return result

if __name__ == '__main__':
    try:
        sys.exit(main(sys.argv))
    except KeyboardInterrupt:
        sys.exit(130)
