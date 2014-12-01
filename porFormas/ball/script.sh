#!/bin/bash
for i in `seq 1 1000`;
do
#	streamer -f jpeg -o image$i.jpeg    
#	raspistill -w 180 -h 120 -o ball_$i.jpg
	mv ball_$i.jpg ball$i.jpg
done    
        
