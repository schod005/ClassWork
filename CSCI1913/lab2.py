#################################################
#Introduction to Python Programming Constructs  #
#Csci 1913                                      #
#Author(s):                                     #
#Date:                                          #
#                                               #
#################################################
import math

#Step 3
def largest(a, b, c, d):
	big=a
	list=[a,b,c,d]
	for x in list:
		if x>big:
			big=x
	return big

#Test cases for step 3
print(largest(1, 2, 3, 4))#expected output: 4

#Step 4
def largest2(a, b, c, d):
	big=0
	list=[a,b,c,d]
	for x in list:
		if type(x) is int or type(x) is float:
			if x>big:
				big=x
	return big

#Step 4 test cases
print(largest2("a", "b", 4.5, 3))#expected output:5

#Step 5
def largest3(*values):
	big=0
	list=values
	for x in list:
		if type(x) is int:
			if x>big:
				big=x
	return big

#Step 5 test cases
print(largest3(1, 80, 3, 4))#expected output:5


#Step 6
def largest4(*values):
	big=0
	list=values
	for x in list:
		if type(x) is int:
			while x>big:
				big=x
	return big

#Step 6 test cases
print(largest4(1, 2, 3, 4))#expected output:5


#Step 7
def insert(item, t):
	listtemp=[]
	temp=item
	inserted=0
	for x in range(0,len(t)):
		if temp>t[x]:
			listtemp.append(t[x])
		elif temp<t[x] and inserted == 0:
			listtemp.append(temp)
			listtemp.append(t[x])
			inserted = 1
		else:
			listtemp.append(t[x])
	bob=tuple(listtemp)
	return bob

#Step 7 test cases
print(insert(5, (1, 2, 3, 10, 12))) # produces (1, 2, 3, 5, 10, 12)
print(insert(5, (1,))) # produces (1, 5)
print(insert(5, (1, 2, 3, 10, 12))) # produces (1, 2, 3, 5, 10, 12)

#Step 8

def  make_largest(f, g):
	def applylargest(x):
		if f(x)>g(x):
			return f(x)
		else:
			return g(x)
	return lambda x: applylargest(x)

#Step 8 test cases
maxsincos = make_largest(math.sin, math.cos)
print(maxsincos(1)) # expected output: FILL
print(maxsincos(0)) # expected output: FILL
def square(x):
	return x**2
maxrootsquare = make_largest(math.sqrt, square)
print(maxrootsquare(5))