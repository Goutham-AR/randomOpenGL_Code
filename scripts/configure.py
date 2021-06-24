#! /usr/bin/env python

import subprocess
import argparse

arg_parser = argparse.ArgumentParser(
    description="preffered cmake generator")

arg_parser.add_argument("-G", default="Ninja",
                        nargs=1, metavar="Generator", dest="gen")

args = arg_parser.parse_args()
# cmake -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_INSTALL=OFF -S . -B build
glfw_flags = ["-DGLFW_BUILD_DOCS=OFF", "-DGLFW_BUILD_TESTS=OFF",
              "-DGLFW_BUILD_EXAMPLES=OFF", "-DGLFW_INSTALL=OFF"]

cmake_flags = ["-S.", "-Bbuild", "-G" + args.gen[0]]

subprocess.run(["cmake"] + glfw_flags + cmake_flags)
