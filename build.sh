#
# Copyright (c) 2019, Fellipe Augusto Ugliara
#
# Use of this source code is governed by an ISC license that can be found 
# in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
#
# --------------------
#
# Run this script to deploy extend library and tests
# It require clang, and ar; to install use the command:
#
#   $ sudo apt install clang
#
rm -rf ./deploy
mkdir deploy
mkdir deploy/object

EXTEND="../library.extend/deploy"
MODULE_INC="-I $EXTEND/include"
EXTEND_INC="$MODULE_INC/extend $MODULE_INC/regex $MODULE_INC/recognizer"
EXTEND_LIB="-L $EXTEND/lib/ -l extend"

clang compiler/home.c -c $EXTEND_INC -o deploy/object/home.o -O2
clang compiler/post.c -c $EXTEND_INC -o deploy/object/post.o -O2

clang cli.c deploy/object/*.o -I compiler $EXTEND_INC $EXTEND_LIB -o deploy/staticgen -O2