
//	Queueを逆順にする
void reverseQueue(Queue<std::string>& queue);
void printQueue(Queue<std::string> queue);

int main()
{
	Queue<std::string> q;
	q.enqueue("AAA");
	q.enqueue("BBB");
	q.enqueue("CCC");

	printQueue(q);
	reverseQueue(q);
	printQueue(q);
}

void reverseQueue(Queue<std::string>& queue)
{
	Stack<std::string> s;
	while (!queue.isEmpty())s.push(queue.dequeue());
	while (!s.isEmpty())queue.enqueue(s.pop());
}

void printQueue(Queue<std::string> queue)
{
	while (!queue.isEmpty())std::cout << queue.dequeue() << std::endl;
}
