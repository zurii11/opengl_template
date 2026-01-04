#!/bin/bash

INCLUDES="-I$PWD/include"
LIBS="-L"lib" -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl"
SOURCE_MAIN="$PWD/src/main.c"
SOURCE_GLAD="$PWD/src/glad.c"
OUTPUT="$PWD/build/program.out"

gcc "$SOURCE_MAIN" "$SOURCE_GLAD" -o "$OUTPUT" "$INCLUDES" $LIBS

if [ $? -eq 0 ]; then
	    echo "Build succeeded!"
	    echo "gcc " "$SOURCE_MAIN" "$SOURCE_GLAD" -o "$OUTPUT" "$INCLUDES" $LIBS
    else
	        echo "Build failed!"
fi

