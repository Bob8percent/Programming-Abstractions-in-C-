//  stackを使用して入力と逆順に表示する

int main()
{
	const int sentinel = 0;

	Stack<int> s;
	while (1)
	{
		int value = getInteger(std::cin);
		if (value == sentinel)break;

		s.push(value);
	}

	//	逆順に表示
	while (!s.isEmpty())std::cout << s.pop() << std::endl;
}
