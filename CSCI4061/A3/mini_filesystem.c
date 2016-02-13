/*
CSci 4061 Spring 2015 Assignment 3
Henry Grittner, 4560922
David Schoder, 4552990
This file implements the mini_filesystem as defined in mini_filesystem.h
*/

/////////////////// File system interface ///////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include "mini_filesystem.h"
#include "miscfuncs.h"

//initialize system call functions
int Search_Directory(char* filename);
int Add_to_Directory(char* Filename, int inodeNumber);
Inode Inode_Read(int inodeNumber);
int Inode_Write(int inodeNumber, Inode inode);
int Block_Read(int blockNumber, int numBytes, char* charString);
int Block_Write(int blockNumber, int number_of_bytes, char* charString);
Super_block Superblock_Read(void);
int Superblock_Write(Super_block supBlock);


//initializes filesystem
int Initialize_Filesystem(char* log_filename)
{
	//Creating log file
    Log_Filename = log_filename;
    FILE *File = fopen(Log_Filename,"w");
    log_timestamp(File);
    fprintf(File, "Filesystem Initialized\n");
    fclose(File);
    
    Count = 0;
    
	Inode newNode;
    int i;
    for (i=0; i<128; i++)
    {
		newNode.Inode_Number = -1;
		Inode_Write(i,newNode);
    }
    
    Super_block supBlock;
    supBlock.next_free_block = 0;
    supBlock.next_free_inode = 0;
    Superblock_Write(supBlock);
    
    return 0;
}


//creates a new file inode and adds it to directory
int Create_File(char* filename)
{
    //check if file exists already
    if (Search_Directory(filename) != -1)
    {
		printf("Error, file already exists\n");
		return -1;
	}     //file already exists
    
    //get next free inode
    Super_block curSuper = Superblock_Read();
    int nextInode = curSuper.next_free_inode;
    if (nextInode > 127)
    {
		printf("Error, out of Inodes\n");
		return -1;
	}     //out of inodes
    curSuper.next_free_inode++;
    Superblock_Write(curSuper);
    
    //initialize new inode
    Inode newNode;
    newNode.Inode_Number = nextInode;
    newNode.User_Id = getuid();
    newNode.Group_Id = getgid();
    newNode.File_Size = 0;
    newNode.Start_Block = -1;
    newNode.End_Block = -1;
    newNode.Flag = 0;
    
    //create directory entry
    if (!Add_to_Directory(filename, nextInode))
    {
		printf("Error, could not add entry to directory\n");
		curSuper.next_free_inode--;
        Superblock_Write(curSuper);
		return -1;
	}     //could not add entry to directory
	
    //update inode in list
    if (!Inode_Write(nextInode, newNode))
    {
		printf("Error, could not update Inode\n");
		curSuper.next_free_inode--;
        Superblock_Write(curSuper);
		return -1;
	}     //could not update inode
	
    return nextInode;
}


//sets the flag in the inode corresponding to the filename
    //return the inode number for the file
int Open_File(char* filename)
{
    int curNodeNum = Search_Directory(filename);
    if (curNodeNum == -1)
    {
		printf("Error, file does not exist\n");
		return -1;
	}    //file does not exist
    
    Inode curNode = Inode_Read(curNodeNum);
    if (curNode.Inode_Number == -1)
    {
		printf("Error, Inode is invalid\n");
		return -1;
	}    //inode is not valid file
    
    //set flag and update inode
    curNode.Flag = 1;
    Inode_Write(curNodeNum, curNode);
    
    return curNodeNum;
}


//reads the specified bytes into a character array
    //returns the number of bytes read
int Read_File(int inode_number, int offset, int count, char* to_read)
{
    //check input values
    if ((offset < 0) || (count < 1))
    {
		printf("Error, invalid offset/count\n");
		return -1;
	}     //invalid offset/count
    
    //make sure inode is valid file to read from
    Inode curNode = Inode_Read(inode_number);
    if ((curNode.Inode_Number == -1) || (curNode.Flag != 1))
    {
		printf("Error, Inode invalid\n");
		return -1;
	}     //inode is not a valid file/is not open
    
    //check file size and number of bytes requested
    if(curNode.File_Size < (offset + count))
    {
		printf("Error, end of file reached\n");
		return -1;
	}     //file smaller than number of bytes requested
    
    //get correct block to start reading from and offset within block
    int curBlock = curNode.Start_Block; //current block we're reading
    while (offset > 512)
    {
        curBlock++;
        offset -= 512;
    }
    
    //set up variables for reading
    int bytesLeft = count;
    int firstBytes = (512-offset);      //bytes read from first block
    if (firstBytes > count)
        {firstBytes = count;}
    bytesLeft -= firstBytes;
    int fullBlocks = bytesLeft / 512;   //number of full blocks read
    int finalBytes = bytesLeft % 512;   //bytes read from final block
    
    char firstString[firstBytes];   //string read from first block
    char* blockList[fullBlocks];    //list of full blocks read
    char finalString[finalBytes];   //string read from final block
    char curBlockString[512];       //current block we're reading
    
    //read portion of first block with offset
    if (Block_Read(curBlock, 512, curBlockString) != 512)
    {
		printf("Error, could not read block\n");
		return -1;
	}     //error reading block
    int i;
    for (i=0; i<firstBytes; i++)
    {
        firstString[i] = curBlockString[i+offset];
    }
    curBlock++;
    
    //read all required full blocks
    for (i=0; i<fullBlocks; i++)
    {
        blockList[i] = (char*)malloc(512);  //allocate new string
        if (Block_Read(curBlock, 512, blockList[i]) != 512)
        {
			printf("Error, could not read block\n");
			return -1;
		}     //error reading block
        curBlock++;
    }
    
    //read portion of last block
    if (Block_Read(curBlock, finalBytes, finalString) != finalBytes)
    {
		printf("Error, could not read block\n");
		return -1;
	}     //error reading block
    
    
    //copy string from first block into to_read
    int numRead = 0;
    if (copyString(to_read, firstString, firstBytes) != firstBytes)
    {
		printf("Error, could not copy string\n");
		return -1;
	}    //error copying string
    numRead += firstBytes;
    to_read += firstBytes;
    
    //copy all required full blocks into to_read
    for (i=0; i<fullBlocks; i++)
    {
        if (copyString(to_read, blockList[i], 512) != 512)
        {
			printf("Error, could not copy string\n");
			return numRead;
		} //error copying string
        free(blockList[i]); //free allocated memory
        numRead += 512;
        to_read += 512;
    }
    
    //copy portion of final block into to_read if necessary
    if (finalBytes > 0)
    {
        if (copyString(to_read, finalString, finalBytes) != finalBytes)
        {
			printf("Error, could not copy string\n");
			return numRead;
		}    //error copying string
    }
    
    return count;   //everything was read correctly
}


//write character string into newly created file
    //returns number of bytes written
int Write_File(int inode_number, int offset, char* to_write, int bytes)
{
    //make sure inode is valid file to read from
    Inode curNode = Inode_Read(inode_number);
    if ((curNode.Inode_Number == -1) || (curNode.Flag != 1))
    {
		printf("Error, Inode is invalid\n");
		return -1;
	}     //inode is not a valid file/is not open
    
    //make sure we're adding onto the end of the file
    if (offset != curNode.File_Size)
    {
		printf("Error, writing to an invalid offset\n");
		return -1;
	}     //trying to write to an invalid offset
    
    //make sure we have enough space to write the string
    int endBlock = curNode.End_Block;
    if (endBlock == -1)
    {
        Super_block curSuper = Superblock_Read();
        endBlock = curSuper.next_free_block;
    }
    int totalBytes = bytes;  //total number of bytes
    if ((curNode.File_Size % 512) != 0) //look at existing block space
    {
        totalBytes += curNode.File_Size % 512;
        totalBytes -= 512;
    }
    endBlock += totalBytes / 512;       //additional full blocks needed
    if ((totalBytes % 512) != 0)
        {endBlock++;}   //overflow into next block
    if (endBlock > 8191)
    {
		printf("Error, not enough memory for file\n");
		return -1;
	}     //we don't have enough blocks
    
    //if this is a new file, set up inode with next free block
    int curBlock = curNode.End_Block;
    int bytesWritten = 0;
    totalBytes = bytes;
    Super_block curSuper = Superblock_Read();
    if (curBlock == -1)
    {
        curBlock = curSuper.next_free_block++;
        Superblock_Write(curSuper);
        curNode.Start_Block = curBlock;
        Inode_Write(inode_number, curNode);
    }
    
    //fill up last file block if it is not full yet
    if ((curNode.File_Size % 512) != 0)
    {
        int curLength = curNode.File_Size % 512;
        int fillLength = 512 - curLength;
        if (bytes < fillLength)
            {fillLength = bytes;}
        
        int totalLength = curLength + fillLength;
        char curString[totalLength];
        if (Block_Read(curBlock, curLength, curString) != curLength)
            {
                printf("Error, could not read block\n");
                return -1;
            }     //error filling up block
        
        if (concatString(curString, to_write, curLength, fillLength) != fillLength)
            {
                printf("Error, could not copy string portion\n");
                return -1;
            }     //error filling up block
        
        if (Block_Write(curBlock, totalLength, curString) != totalLength)
        {
			printf("Error, could not write to block\n");
			return -1;
		}  //error writing to block
		
		to_write += fillLength;
		bytesWritten += fillLength;
		curNode.File_Size += bytesWritten;
		if (bytesWritten != bytes)
		{
		    curBlock = curSuper.next_free_block++;
            Superblock_Write(curSuper);
		}
    }
    
    int bytesLeft = bytes - bytesWritten;
    int totalBytesWritten = bytesWritten;
    
    while(bytesLeft)
    {
		bytesWritten = Block_Write(curBlock, (bytesLeft > 512 ? 512:bytesLeft), to_write);
		if(bytesWritten == 0)
		{
			printf("Error, could not write to block\n");
			return -1;
		}
		bytesLeft -= bytesWritten;
		to_write += bytesWritten;
		totalBytesWritten += bytesWritten;
		curNode.File_Size += bytesWritten;
		if (bytesLeft)
		{
		    curBlock = curSuper.next_free_block++;
            Superblock_Write(curSuper);
		}
	}
	curNode.End_Block = curBlock;
	Inode_Write(inode_number, curNode);

    return totalBytesWritten;
}


//clears the flag for the inode number if it is set
int Close_file(int inode_number)
{
    Inode curNode = Inode_Read(inode_number);
    if (curNode.Inode_Number == -1)
    {
		printf("Error, Inode is invalid\n");
		return 1;
	}     //inode is not valid file
    
    //if flag is set, clear it and return success
    if (curNode.Flag == 1)
    {
        curNode.Flag = 0;
        Inode_Write(inode_number, curNode);
        return 0;
    }
    
    return 1;   //file was not open
}

//returns the size of the file in bytes
int Get_File_Size(int inode_number)
{
    Inode curFile = Inode_Read(inode_number);
    if (curFile.Inode_Number == -1)
    {
        return 0;
    }
    return curFile.File_Size;
}




/////////////////// File system calls ///////////////////

//search through the directory for the given filename
    //returns the inode number of the file
int Search_Directory(char* filename)
{
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
	fprintf(File,"Directory\t\t\t Read\n");
	fclose(File);
	
    int i;
    for (i=0; i<128; i++)
    {
        if (strcmp(filename, Directory_Structure[i].Filename) == 0)
            {return Directory_Structure[i].Inode_Number;}
    }
    return -1;  //file does not exist
}


//adds an entry to the directory structure
int Add_to_Directory(char* Filename, int inodeNumber)
{
    int fileExist = Search_Directory(Filename);
    Inode curNode = Inode_Read(inodeNumber);
    
    //if file does not exist and inode is not in use
    if ((fileExist == -1) && (curNode.Inode_Number == -1))
    {
        //create directory entry and claim inode
        strcpy(Directory_Structure[inodeNumber].Filename, Filename);
        Directory_Structure[inodeNumber].Inode_Number = inodeNumber;
        Inode_List[inodeNumber].Inode_Number = inodeNumber;
        FILE *File = fopen(Log_Filename,"a");
        log_timestamp(File);
        fprintf(File,"Directory\t\t\t Write\n");
        fclose(File);
        return 1;
    }
    
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
    fprintf(File,"Directory\t\t\t Read\n");
    fclose(File);
    return 0;   //file already exists or inode is already initialized
}


//returns the inode structure for the corresponding inode number
Inode Inode_Read(int inodeNumber)
{
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
    if (inodeNumber < 10)
	    fprintf(File,"Inode %d\t\t\t\t Read\n", inodeNumber);
	else
	    fprintf(File,"Inode %d\t\t\t Read\n", inodeNumber);
	fclose(File);

    int i;
    for (i=0; i<128; i++)
    {
        if (Directory_Structure[i].Inode_Number == inodeNumber)
            {return Inode_List[inodeNumber];}
    }
    
    //inode is not a valid file. Return inode with number = -1
    Inode emptyNode;
    emptyNode.Inode_Number = -1;
    return emptyNode;
}


//copies the corresponding inode to the inode list
int Inode_Write(int inodeNumber, Inode inode)
{
    if ((inodeNumber < 0) || (inodeNumber > 127))
        {return 0;}
    
    if (inode.Inode_Number != -1)
    {
        FILE *File = fopen(Log_Filename,"a");
        log_timestamp(File);
	    if (inodeNumber < 10)
	        fprintf(File,"Inode %d\t\t\t\t Write\n", inodeNumber);
	    else
	        fprintf(File,"Inode %d\t\t\t Write\n", inodeNumber);
	    fclose(File);
	}

    Inode_List[inodeNumber].Inode_Number = inode.Inode_Number;
    Inode_List[inodeNumber].User_Id = inode.User_Id;
    Inode_List[inodeNumber].Group_Id = inode.Group_Id;
    Inode_List[inodeNumber].File_Size = inode.File_Size;
    Inode_List[inodeNumber].Start_Block = inode.Start_Block;
    Inode_List[inodeNumber].End_Block = inode.End_Block;
    Inode_List[inodeNumber].Flag = inode.Flag;
    
    return 1;
}


//reads from specified block into character string
    //returns number of bytes read
int Block_Read(int blockNumber, int numBytes, char* charString)
{
    if ((blockNumber < 0) || (blockNumber > 8191))
        {return 0;}   //invalid block number
    if ((numBytes < 1) || (numBytes > 512))
        {return 0;}   //invalid number of bytes
    
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
	fprintf(File,"Disk Block %d\t\t Read\n", blockNumber);
	fclose(File);
    
    char* curBlock = Disk_Blocks[blockNumber];
    
    if (copyString(charString, curBlock, numBytes) != numBytes)
        {return 0;}   //string copy was not successful
    return numBytes;
}


//writes the given string to the desired block (max of 512 bytes)
    //returns number of bytes written
int Block_Write(int blockNumber, int number_of_bytes, char* charString)
{
    if ((blockNumber < 0) || (blockNumber > 8191))
        {return 0;}     //invalid block number
    if (number_of_bytes > 512)
        {return 0;}     //trying to write too many bytes
    
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
	fprintf(File,"Disk Block %d\t\t Write\n", blockNumber);
	fclose(File);
    
    //allocate memory for block
    Disk_Blocks[blockNumber] = (char*) malloc(512);
    if (Disk_Blocks[blockNumber] == NULL)
    {return 0;}
    
    char* curBlock = Disk_Blocks[blockNumber];
    
    if (copyString(curBlock, charString, number_of_bytes) != number_of_bytes)
        {return 0;}
    return number_of_bytes;
}


//returns the superblock structure
Super_block Superblock_Read(void)
{
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
	fprintf(File,"Superblock\t\t\t Read\n");
	fclose(File);
    return Superblock;
}


//copies the given superblock info into the superblock
int Superblock_Write(Super_block supBlock)
{
    FILE *File = fopen(Log_Filename,"a");
    log_timestamp(File);
	fprintf(File,"Superblock\t\t\t Write\n");
	fclose(File);
    
    Superblock.next_free_inode = supBlock.next_free_inode;
    Superblock.next_free_block = supBlock.next_free_block;
    return 0;
}

