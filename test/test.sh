#!/bin/bash

VERBOSE=

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
LOG_FOLDER="$ROOT/test/log"
DATA_FOLDER="$ROOT/test/data"

GREEN="\033[32;01m"
RED="\033[31;01m"
NORMAL="\033[0m"

INVALID_FILES="$(find "$DATA_FOLDER/invalid_asm" -name \*.s)"
VALID_FILES="$(find "$DATA_FOLDER/test_asm" -name \*.s)"

error() {
	echo -e "\n$RED$1$NORMAL"
    test $2 && tail -n 42 "$2"
	exit 1
}

success() {
	echo -e "$GREEN$1$NORMAL"
}

# unit tests
./flextest3000
UNIT_RET=$?


# functional tests
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
    diff "$f" "$(echo "$f" | sed -E 's|(.*)s$|\1cor|' | sed -E 's|test_asm|ctrl_cor|')" || error "$base_f (valid file) cor files diff :/" "$f"
	test $VERBOSE && echo && cat "$f" && cat "$LOG_FOLDER/$base_f.log"
	success "$base_f (valid file) ok!"
done

test $UNIT_RET == 0 && success "yay" || exit $UNIT_RET