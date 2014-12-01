#!/bin/bash
for i in `seq 1 1000`;
do
#	streamer -f jpeg -o image$i.jpeg    
	mv img_$i.jpg img$i.jpg
	#raspistill -w 180 -h 120 -o img_$i.jpg
done    
        
