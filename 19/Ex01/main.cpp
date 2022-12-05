#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Library/vector.h"
#include "Employee.h"

int main() {
	HourlyEmployee* h1 = new HourlyEmployee("H1");
	h1->setHourlyRate(900);
	h1->setHoursWorked(40);
	HourlyEmployee* h2 = new HourlyEmployee("H2");
	h2->setHourlyRate(1200);
	h2->setHoursWorked(50);
	HourlyEmployee* h3 = new HourlyEmployee("H3");
	h3->setHourlyRate(1100);
	h3->setHoursWorked(10);

	CommissionEmployee* c1 = new CommissionEmployee("C1");
	c1->setBasedSalary(1000);
	c1->setSalaryVolume(10000);
	c1->setCommissionRate(0.8);
	CommissionEmployee* c2 = new CommissionEmployee("C2");
	c2->setBasedSalary(500);
	c2->setSalaryVolume(20000);
	c2->setCommissionRate(0.5);
	CommissionEmployee* c3 = new CommissionEmployee("C3");
	c3->setBasedSalary(2000);
	c3->setSalaryVolume(30000);
	c3->setCommissionRate(0.9);

	SalariedEmployee* s1 = new SalariedEmployee("S1");
	s1->setSalary(10000);
	SalariedEmployee* s2 = new SalariedEmployee("S2");
	s2->setSalary(20000);
	SalariedEmployee* s3 = new SalariedEmployee("S3");
	s3->setSalary(25000);

	Vector<Employee*> payroll;
	payroll += h1, h2, h3, c1, c2, c3, s1, s2, s3;

	for (Employee* p : payroll) {
		std::cout << p->getName() << ": " << p->getPay() << std::endl;
	}
}

