/*
* 平均値を求める
*/
double mean(Vector<double>& data)
{
	double sum = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		sum += data[i];
	}
	return sum / data.size();
}
