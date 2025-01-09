#!/bin/bash

INCLUDES="-IC:/Users/Legion Slim 5/dev/OpenGL/include"
LIBS="-L"lib" -lglfw3 -lgdi32 -lopengl32 -luser32"
SOURCE_MAIN="C:/Users/Legion Slim 5/dev/OpenGL/src/main.c"
SOURCE_GLAD="C:/Users/Legion Slim 5/dev/OpenGL/src/glad.c"
OUTPUT="C:/Users/Legion Slim 5/dev/OpenGL/build/program.exe"

gcc "$SOURCE_MAIN" "$SOURCE_GLAD" -o "$OUTPUT" "$INCLUDES" $LIBS

if [ $? -eq 0 ]; then
	    echo "Build succeeded!"
	    echo "gcc " "$SOURCE_MAIN" "$SOURCE_GLAD" -o "$OUTPUT" "$INCLUDES" $LIBS
    else
	        echo "Build failed!"
fi

