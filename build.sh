#
# Copyright (c) 2019, Fellipe Augusto Ugliara
#
# Use of this source code is governed by an ISC license that can be found 
# in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
#
# --------------------
#
# Run this script to deploy staticgen cli and tests
# It require clang; to install use the command:
#
#   $ sudo apt install clang
#
rm -rf ./deploy
mkdir deploy
mkdir deploy/object

DATATYPE="../library.datatype/deploy"
MODULE_INC="-I $DATATYPE/include"
DATATYPE_INC="$MODULE_INC/abstract $MODULE_INC/composite $MODULE_INC/other $MODULE_INC/primitive $MODULE_INC/toolbelt"
DATATYPE_OBJS="$DATATYPE/object/*.o"

LANGUAGE="../library.language/deploy"
MODULE_INC_LANG="-I $LANGUAGE/include"
LANGUAGE_INC="$MODULE_INC_LANG/regex $MODULE_INC_LANG/recognizer"
LANGUAGE_OBJS="$LANGUAGE/object/*.o"

clang compiler/home.c -c $DATATYPE_INC $LANGUAGE_INC -o deploy/object/home.o
clang compiler/post.c -c $DATATYPE_INC $LANGUAGE_INC -o deploy/object/post.o

clang cli.c deploy/object/*.o -I compiler $DATATYPE_INC $DATATYPE_OBJS $LANGUAGE_INC $LANGUAGE_OBJS -o deploy/staticgen
