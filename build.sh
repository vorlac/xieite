#! /bin/bash

HEADER_DIRECTORY="$PWD/include/"

SOURCE_DIRECTORY="$PWD/src/"

DESTINATION=${1:-"$PWD/.a"}

COMPILER_FLAGS="-c -std=c++20 -pthread"


SOURCE_FILES=()
mapfile -d '' SOURCE_FILES < <(find $SOURCE_DIRECTORY -type f -print0)
SOURCE_FILES_COUNT=${#SOURCE_FILES[@]}
TEMPORARY_DIRECTORY=$(mktemp -d)
for (( i=0 ; i<$SOURCE_FILES_COUNT ; i++ )); do
	g++ ${SOURCE_FILES[i]} -I $HEADER_DIRECTORY -o "$TEMPORARY_DIRECTORY/$(basename $(mktemp))" $COMPILER_FLAGS &
done
wait
ar crs $DESTINATION $(ls -d $TEMPORARY_DIRECTORY/*)
rm -rf $TEMPORARY_DIRECTORY
