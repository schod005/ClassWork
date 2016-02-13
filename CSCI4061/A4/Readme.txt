# CSci 4061 Spring 2015 Assignment 4
# Henry Grittner, 4560922
# David Schoder, 4552990
# CSELabs machine: KH4250-20

This code uses multiple threads to search through a directory tree
and find all of the valid jpg, png, gif, and bmp files. The program
also finds information about the images (type, size, etc.) and then
creates an html file with the information that links back to
the image files. This program can run in two different modes. The
first mode creates a single thread for each directory in the tree
that finds the image files. The second mode creates five threads
for each directory, one that spawns more threads in subdirectories
and four that search for each of the different image types.
Information about the program execution is logged to two different 
files as the program runs called "catalog.log" and "output.log".
These files, along with the html file, appear in the output
directory.

In order to calculate the total runtime for the different program
variations (which is stored in the logfile), we took the time
between the creation of the first search thread and the completion
of the final search thread. This gave the total time that threads
were running, which gives a good estimation about how long the
two variations took to run.

Our program can handle only absolute paths to files beginning 
with ~/

To compile type:
	make
Usage: 
	./image_manager [version] ~/[input_dir] ./[output_dir]

Comparison:
Overall, variant one takes around 20 ms to complete the search and
variant two takes about 40 ms to complete the search. This means 
that the first variation is usually about twice as fast as the 
second. This makes sense, since variation 1 only has to look at 
each file in a directory once, whereas variation 2 must look at 
each file 5 times (one for each thread). Variation 2 is also going 
to have many more collisions when threads try to lock mutexes, which 
could contribute to the slowdown.

Variation 2 is also going to use more space than variation 1. 
Variation 2 must keep 5 times as many open directories in memory 
than variation 1 does, along with more strings to hold filenames 
and other data. All of this together means that we do not get any 
added benefit from creating 5 threads per directory rather than just 
1. This shows that using too many threads can cause the overall 
program to execute at a slower rate.
