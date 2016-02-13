This program is uses multiple processes running in parallel to convert files of the format .bmp, .gif, and .png to thumnails of maximum dimensions 200x200 pixels.  HTML files are created for each converted file and link to one another in a slideshow progression.

To build the program, make sure all files are in the same directory and type 
	make parallel_convert

To run the program, type
	./parallel_convert convert_count output_dir input_dir

where convert_count is a number, 1 through 10, of processes used to convert images, output_dir is the directory the converted images will be created in, and input_dir is the directory of the images to be converted.