#!/bin/bash
SCRIPT_PATH="$(readlink -f "$0")"
SCRIPT_DIR="$(dirname "$SCRIPT_PATH")"

echo DIR: $SCRIPT_DIR
echo PATH: $SCRIPT_PATH

export PATH="$PATH:$HOME/tools/xtensa-lx106-elf/bin"

export IDF_PATH=$SCRIPT_DIR/

source $SCRIPT_DIR/../.venv/bin/activate

alias bfm="python $IDF_PATH/tools/idf.py -p /dev/ttyUSB0 flash monitor"