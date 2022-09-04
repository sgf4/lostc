#!/bin/bash

while :; do
    make
    ./lostc &
    p=$!
    inotifywait -r src -e close_write
    kill $p
done
