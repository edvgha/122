#!/bin/bash

for i in {1..3000}
do
    curl http://localhost:9099/ &
done
