#!/usr/bin/env bash

# @author: Ankit Dimri

# Compile the client.cpp file and create the object file

echo "Compiling client.cpp..."

g++ client.cpp -o clnt

echo "compiled ..."
# run the client

count=0
ps_running=$(pidof client)
for pids in $ps_running
do
  count=`expr $count + 1`
done

echo "starting client..."
./clnt
