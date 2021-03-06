#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
class Customer{

public:
	Customer();
	Customer(int id, double x, double y, double demand, bool depot = 0);

	void setId(const int);
	void setX(const double);
	void setY(const double);
	void setDemand(const double);
	void setDepot(const bool);

	int getId() const;
	double getX() const;
	double getY() const;
	double getDemand() const; 
	bool getDepot() const;

	bool operator==(const Customer&) const;

private:
	int id;
	double x;
	double y;
	double demand;
	bool depot;
	
	friend std::ostream& operator<<(std::ostream&, const Customer&);
};

#endif
