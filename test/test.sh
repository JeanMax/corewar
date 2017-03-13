#!/bin/bash

VERBOSE=

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
LOG_FOLDER="$ROOT/test/log"
DATA_FOLDER="$ROOT/data"

GREEN="\033[32;01m"
RED="\033[31;01m"
NORMAL="\033[0m"

asm_files="$(find "$DATA_FOLDER" -name \*.s)"
INVALID_FILES="$(echo "$asm_files" | grep invalid)"
VALID_FILES="$(echo "$asm_files" | grep -v invalid)"
unset asm_files

function error() {
	echo -e "\n$RED$1$NORMAL"
    test $2 && tail -n 42 "$2"
	exit 1
}

function success() {
	echo -e "$GREEN$1$NORMAL"
}

# TODO: make ?

mkdir -p "$LOG_FOLDER"

for f in $INVALID_FILES; do
	base_f="$(basename "$f")"
	"$ROOT/asm" "$f" &> "$LOG_FOLDER/$base_f.log" && error "$base_f (invalid file) succeed :/" "$f" #TODO: catch asm crash :o
	test $VERBOSE && echo && cat "$f" && cat "$LOG_FOLDER/$base_f.log"
	success "$base_f (invalid file) ok!"
done

for f in $VALID_FILES; do
	base_f="$(basename "$f")"
	"$ROOT/asm" "$f" &> "$LOG_FOLDER/$base_f.log" || error "$base_f (valid file) failed :/" "$f"
	test $VERBOSE && echo && cat "$f" && cat "$LOG_FOLDER/$base_f.log"
	success "$base_f (valid file) ok!"
done

success "yay"
