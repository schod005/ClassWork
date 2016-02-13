int ncopy(int *src, int *dst, int len)
{
	int count = 0;
	int val;
	
	while (len>0)
	{
		val = *src++;
		*dst++ = val;
		if (val > 0)
			count++;
		len--;
	}
	return count;
}

int main()
{
	int bob[10] = {3,5,1,7,43,7,3,4,2,8};
	int jack[10];
	ncopy(bob,jack,10);
	
}
