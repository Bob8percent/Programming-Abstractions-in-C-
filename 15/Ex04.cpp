
//	I	->	1
//	V	->	5
//	X	->	10
//	L	->	50
//	C	->	100
//	D	->	500
//	M	->	1000
int calcPoint(char ch) {
	switch (ch) {
	case 'I':
		return 1;
		
	case 'V':
		return 5;

	case 'X':
		return 10;

	case 'L':
		return 50;

	case 'C':
		return 100;

	case 'D':
		return 500;

	case 'M':
		return 1000;

	default:
		return 0;
	}
}

int romanToDecimal(const std::string& str) {
	int result = 0;
	for (int i = 0; i < str.length(); ++i) {
		char ch = str.at(i);
		char nch = -1;
		if (i < str.length() - 1)nch = str.at(i + 1);


		int point = calcPoint(ch);
		int npoint = calcPoint(nch);
		if (nch != -1 && npoint > point) {
			result += (-1 * point);
		}
		else {
			result += point;
		}
	}

	return result;
}
