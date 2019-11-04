#!/usr/bin/env bash

# @author: Ankit Dimri

# Compile the client.cpp file and create the object file

echo "Compiling client.cpp..."

g++ client.cpp -o clnt

echo "compiled ..."
# run the client

echo "starting client..."
./clnt
