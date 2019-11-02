#!/bin/bash

# @author: Ankit Dimri

echo
echo "Compiling server.cpp ..."
echo
g++ server.cpp -o server
echo "compiled!"
echo "starting server..."
echo

./server
