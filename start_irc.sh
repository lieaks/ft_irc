#!/bin/bash

# Check if necessary parameters are provided
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <port> <password>"
	  exit 1
fi

port=$1
password=$2

# Launch the IRC server
gnome-terminal -- bash -c "valgrind ./ircserv $port $password; exec bash" 

# Wait for the server to start
sleep 1

# Launch "i" instances of irssi, each in a separate terminal window, connecting to the server
for i in {1..3}
do
  sleep 1
  gnome-terminal -- bash -c "irssi -c localhost -p $port -w $password -n user$i; exec bash" 
done

# while the program ircserv is running 
while [ $(ps aux | grep ircserv | wc -l) -gt 1 ]
do
  sleep 1
done

 # Kill all instances of irssi
pkill -f irssi
