# -*- coding: utf-8 -*-
"""
Created on Mon Feb 10 16:30:18 2014

@author: ayush488
"""

# -*- coding: utf-8 -*-
"""
Created on Mon Feb 10 08:25:21 2014

@author: ayush488
"""
import math
import urllib #needed for web calls
import operator  #needed for sorting dictionary
N=5000000000 #assuming the number of web pages to be this
def Distance(x,y,xy):# for computing relatedness score. This funciton is given to you 
    if x==0.0:
        x=0.01
    if y==0.0:
        y=0.01
    if xy==0.0:
        xy=0.01
            
    fx=math.log(x)
    fy=math.log(y)
    fxy=math.log(xy)
    M=math.log(N)
    NGD=(max(fx,fy)-fxy)/(M-min(fx,fy))
    return NGD

        

def web_count(word):
    #create a temporary file name, can be an html file (.html or .txt)
    #prepare a query using the search engine url and the input word
    #use the urllib function to call the web adn save the web page
    #read the file and search for the hits for the input word (you may have to use some string operations for this)
    #the function should return the count(hits) for the word
    
def web_data(key,cand_words):
    #get count(x) for the keyword
    # iterate over each word in candidate words and get hit count for each word (y)
    # while iterating you can also get the hits for the combination of the word with the keyword(xy)
    #call the Distance function(given) with (x,y,xy)to get the relatedness score, you can use a dictionary to store the scores against each word in candidate words so that it can be used to find the 2-most related words in next step
    #print the two most related words to the keyword from the list of candidate worrd
    
def extractor(l):
    #takes the line as input
    #split the line to get the keyword and the list of candidate words
    #candidate words have to be stored in list 
    # make a call to the web_data function with the keyword and the candidate words list
      
def read_file():
    #read the test_file.txt
    #read lines from the file
    #iterate over each line and call the extractor function with each line
      
            
#call the read_file() function  
     
        
    
        
        
  