
template <typename ValueType>
void swap(ValueType& x, ValueType& y) {
	ValueType tmp = x;
	x = y;
	y = tmp;
}
