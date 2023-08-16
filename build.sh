#!/bin/bash

# This script compiles cards_proxy.cpp into a 32-bit DLL
# run: './build.sh' in the terminal (use the bash shell e.g. the MSYS2 bash on Windows) to run this script

# Flags:
# -Werror: Treat all warnings as errors.
# -static: Use static linking.
# -m32: Compile for a 32-bit target. Use '-m64' for a 64-bit target.
# -mdll: Intended to produce a DLL. However, consider using '-shared' for g++.
# -o cards.dll: Output the result as cards.dll.

g++ -Werror -static -m32 -mdll -o cards.dll cards_proxy.cpp cards.def

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful!"


#################################################################
#####  How to install MSYS2 and the C++ compiler on Windows  ####
#################################################################

# 1. Install MSYS2 from their official website: https://www.msys2.org/.
# 2. Launch MSYS2.
# 3. In the terminal window that appears, execute the command:
#        'pacman -S mingw-w64-x86_64-gcc'
# 4. Next, execute the following command:
#        'pacman -S --needed base-devel mingw-w64-i686-toolchain'
#        When prompted, press Enter to install all suggested packages.
# 5. Installation and setup are complete!

#################################################################