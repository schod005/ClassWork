file=open("test_file.txt",'r')
line=file.readlines()
for l in line:
    tmp=str(l).strip().split('***')
    print tmp
import urllib
word='tree'
Query ='http://www.bing.com/search?q='+word+'&go=&qs=n&form=QBLH&pq='+word+'&sc=8-4&sp=-1&sk=&cvid=6a7d298283ba46c0ba04272487cd60e2'
tmp1="web_bing.html"
urllib.urlretrieve(Query,tmp1)
file2=open(tmp1,'r')
s1=str(file2.read())
start='<a class="ftrH" id="h5443" href="javascript:">'
end='<span class="sw_ddbk"></span> </a></span>'
ind1=s1.find(start)
ind2=s1.find(end)
leng=len(start)
sub_str=s1[ind1+leng:ind2]
print sub_str
