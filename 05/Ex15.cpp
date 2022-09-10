//	Stackの最上位n個の要素をk回だけ回転させる
void roll(Stack<char>& stack, int n, int k);
void printStack(Stack<char> stack);

int main()
{
	Stack<char> stack;
	for (char ch = 'A'; ch <= 'Z'; ++ch)stack.push(ch);
	while (1)
	{
		std::cout << "現在：";
		printStack(stack);

		std::cout << " n : ";
		int n = getInteger(std::cin);
		std::cout << "k : ";
		int k = getInteger(std::cin);

		std::cout << "roll(stack, " << n << ", " << k << ")を実行します" << std::endl;
		roll(stack, n, k);
	}
}

void printStack(Stack<char> stack)
{
	std::cout << "上位 " ;
	while (!stack.isEmpty())std::cout << stack.pop();
	std::cout << " 底" << std::endl;
}

void roll(Stack<char>& stack, int n, int k)
{
	if (stack.size() < n)
	{
		std::cout << "ERROR: void roll(Stack<char>& stack, int n, int k) : "
			<< "nがstackのサイズを超えています" << std::endl;
		return;
	}
	if (!(n > 0 && k > 0))
	{
		std::cout << "ERROR: void roll(Stack<char>& stack, int n, int k) : "
			<< "nまたはkが負となっています" << std::endl;
		return;
	}

	std::string rotatedData(n, '0');	//　回転後の文字の並び。文字列の末がスタックの底となる
	int shift = n - k % n;
	for (int i = shift; i < n + shift; ++i)
	{
		int k = i % n;
		rotatedData[k] = stack.pop();
	}

	for (int i = n - 1; i >= 0; --i)
	{
		stack.push(rotatedData[i]);
	}
}
