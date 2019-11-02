#!/bin/bash

# @author: Ankit Dimri

# Compile server.cpp and create a server object

echo
echo "Compiling server.cpp ..."
echo
g++ server.cpp -o server
echo "compiled!"
echo "starting server..."
echo

# Start server
./server
