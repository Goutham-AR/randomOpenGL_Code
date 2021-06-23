#! /usr/bin/env python

import subprocess

# add feature for running configure.py if some change has occurred

subprocess.run(["cmake", "--build", "./build"])
