#!/usr/bin/env bash

# @author: Ankit Dimri

# Compile the client.cpp file and create the object file

echo "Compiling client.cpp..."

g++ client.cpp -o clnt

echo "compiled ..."
# run the client

count=0
ps_running=$(pidof clnt)
for pids in $ps_running
do
  count=`expr $count + 1`
done

count=`expr $count + 1`

echo "Starting client $count ..."

echo "starting client..."
./clnt
