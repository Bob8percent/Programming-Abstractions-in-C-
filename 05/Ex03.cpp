
/*
* 標準偏差を求める
*/
double stddev(Vector<double>& data)
{
	double ave = mean(data);
	double subSqSum = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		double val = data[i] - ave;
		subSqSum += val * val;
	}
	return std::sqrt(subSqSum / data.size());
}

double mean(Vector<double>& data)
{
	double sum = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		sum += data[i];
	}
	return sum / data.size();
}
