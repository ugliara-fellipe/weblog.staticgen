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

PROTOTYPE="../library.prototype/deploy"
MODULE_INC_1="-I $PROTOTYPE/include"
PROTOTYPE_INC="$MODULE_INC_1/container $MODULE_INC_1/primitive $MODULE_INC_1/prototype"
PROTOTYPE_LIB="-L $PROTOTYPE/lib/ -l prototype"

EXTEND="../library.extend/deploy"
MODULE_INC_2="-I $EXTEND/include"
EXTEND_INC="$MODULE_INC_2/extend $MODULE_INC_2/regex $MODULE_INC_2/recognizer"
EXTEND_LIB="-L $EXTEND/lib/ -l extend"

clang compiler/home.c -c $EXTEND_INC $PROTOTYPE_INC -o deploy/object/home.o
clang compiler/post.c -c $EXTEND_INC $PROTOTYPE_INC -o deploy/object/post.o

clang cli.c deploy/object/*.o -I compiler $EXTEND_INC $EXTEND_LIB $PROTOTYPE_INC $PROTOTYPE_LIB -o deploy/staticgen
