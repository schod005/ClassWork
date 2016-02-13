typedef struct ELE {
	int val;
	struct ELE *next;
} *list_ptr;

int sum_list(list_ptr ls)
{
	int val = 0;
	while (ls)
	{
		val += ls->val;
		ls = ls->next;
	}
	return val;
}

int rsum_list(list_ptr ls)
{
	if (!ls)
		return 0;
	else {
		int val = ls->val;
		int rest = rsum_list(ls->next);
		return val + rest;
	}
}

int main()
{
	list_ptr x;
	sum_list(x);
	rsum_list(x);
}
