int add(int a, int b) { return a + b; }

int main()
{
	int(*fp)(int, int) = add;
	int three = (*************************************************************************************fp)(1, 2);
	return 0;
}