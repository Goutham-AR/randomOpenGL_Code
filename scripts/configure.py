#! /usr/bin/env python

import subprocess

# cmake -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_INSTALL=OFF -S . -B build

glfw_flags = ["-DGLFW_BUILD_DOCS=OFF", "-DGLFW_BUILD_TESTS=OFF",
              "-DGLFW_BUILD_EXAMPLES=OFF", "-DGLFW_INSTALL=OFF"]

cmake_flags = ["-S.", "-Bbuild"]

subprocess.run(["cmake"] + glfw_flags + cmake_flags)
