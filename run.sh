#!/bin/bash

# VARIABLES
OUT=bin/main.exe
INP='src/main.c src/ball.c src/paddle.c'

INCLUDE=include/
LIB=lib/


# CLEAN THE PROMPT
clear


# DELETE PREVIOUS BUILD
if [ -f "$OUT" ]; then
    echo "[RUN] Deleting the previous $OUT ..."
    rm "$OUT"
    echo ""
fi


# COMPILE
echo "[RUN] Compiling $INP ..."
gcc $INP -o $OUT -I $INCLUDE -L $LIB -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
echo ""


# RUN
if [ -f "$OUT" ]; then
    echo "[RUN] Running $OUT ..."
    $OUT
    echo ""
else
    echo "[RUN] Compilation of $INP failed !"
    echo ""
    read -p "[RUN] Press enter to exit ... "
fi
