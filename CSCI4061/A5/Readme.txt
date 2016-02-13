# CSci 4061 Spring 2015 Assignment 4
# Henry Grittner, 4560922
# David Schoder, 4552990
# CSELabs machine: KH4250-20

This code implements a simple client-server TCP socket program
that is capable of transmitting images between two computers.
The server program looks for all png, gif, and tiff files in a
given input directory, and then creates a catalog of these files.
The client program connects to the server over a tcp socket,
downloads the catalog file, and then downloads either specific
images or all images of a certain type. The client saves links to
the images in an html file, and error checking is performed using
the md5 hash function.

Compile the code by entering:
	
	make all

To transmit images from one computer to another, start the server 
program on the sending computer by entering:
	
	./server [Port] [Image Directory]
	
Start the client on the receiving computer by entering:

	./client [IP address] [Port] [Optional Extension]
	
A list of images will display on the client with corresponding indecies.
If no extension is entered, to download images, enter the index of the
picture the client wishes to download and the download will begin 
immediately.
If an extension is entered, all images with the given extension will be
downloaded.
