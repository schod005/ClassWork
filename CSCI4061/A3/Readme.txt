# CSci 4061 Spring 2015 Assignment 3
# Henry Grittner, 4560922
# David Schoder, 4552990
# CSELabs machine: KH4250-20

This program will test our in-memory filesystem by writing .jpg files to it and reading them back onto the hard disk.

To compile type:
	make test
Usage: 
	./test input_directory output_directory log_filename


Our experiment used 622 average reads per file and yielded results of:
Best case read time:	7.244 ms
Worst case read time:	3733.244 ms



Experiment Calculations:

7459 accesses
7459 / 2 = 3730 reads
3730 reads / 6 files = average of 622 reads per file
Rotation Rate = 15000 RPM
Average Seek time = 4 ms
Average number of sectors per track = 1000
Sector size = 512 bytes

Best case (contiguous file):
Average Seek time = 4 ms
Average Rotation time = (60000 ms / 1 minute) / 15000 RPM / 2 = 2 ms
Average Read time = (622 sectors / 1000 sectors per track) * Average Rotation time = 1.244 ms
Total Read time = 4 ms + 2 ms + 1.244 ms = 7.244 ms

Worst case (random fragmentation):
Average Seek time = 4 ms
Average Rotation time = (60000 ms / 1 minute) / 15000 RPM / 2 = 2 ms
Average Read time = (1 sector / 1000 sectors per track) * Average Rotation time = 0.002 ms
Total read time = 622 * ( 4 + 2 + 0.002 ) ms = 3733.244 ms


