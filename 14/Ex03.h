
template <typename T1, typename T2>
class Pair {
public:
	Pair();
	Pair(T1 v1, T2 v2);
	
	T1 first();
	T2 second();

private:
	T1 v1;
	T2 v2;
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair() {
	v1 = T1();
	v2 = T2();
}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(T1 v1, T2 v2) {
	this->v1 = v1;
	this->v2 = v2;
}

template <typename T1, typename T2>
T1 Pair<T1, T2>::first() {
	return v1;
}

template <typename T1, typename T2>
T2 Pair<T1, T2>::second() {
	return v2;
}
