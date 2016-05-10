#include <iostream>
using namespace std;
#include <assert.h>

class date
{
public:
	date(int year,int month,int day):_year(year),_month(month),_day(day)		
	{
		assert(year >= 1900);
		assert(month > 0 && month < 13);
		assert(day > 0 && day <= GetMonDay(year, month));
	}

	date(date& da)
	{
		_year = da._year;
		_month =da. _month;
		_day = da._day;
	}

	date operator+(int day)
	{
		date d = *this;
		d._day = _day +day;
		while(d._day > GetMonDay(d._year, d._month))
		{
			d._day = d._day - GetMonDay(d._year, d._month);
			d._month++;
			if(d._month > 12)
			{
				d._month = 1;
				d._year++;
			}
		}
		return d;
	}

	date& operator+=(int day)
	{
		_day +=day;
		while(_day > GetMonDay(_year, _month))
		{
			_day = _day - GetMonDay(_year, _month);
			_month++;
			if(_month > 12)
			{
				_month = 1;
				_year++;
			}
		}
		return *this;
	}

	date operator-(int day)
	{
		date d = *this;
		d._day = _day - day;
		while(d._day <= 0)
		{
			d._month--;
			if(d._month < 1)
			{
				d._month = 12;
				d._year--;
			}
			d._day = d._day + GetMonDay(d._year, d._month);
		}
		return d;
	}

	date& operator-=(int day)
	{
		_day = _day - day;
		while(_day <= 0)
		{
			_month--;
			if(_month < 1)
			{
				_month = 12;
				_year--;
			}
			_day = _day + GetMonDay(_year, _month);
		}
		return *this;
	}
	
	int operator-(const date& d)
	{
		int count = 0;
		date d1(*this);
	    if((d._year > d1._year) ||
			((d._year == d1._year)&&(d._month > d1._month)) ||
			((d._year == d1._year)&&(d._month==d1._month)&&(d._day > d1._day)))
		{
			while(1)
			{
				d1.operator++();
				count++;
				if(d._year == d1._year && d._month == d1._month && d._day == d1._day)
				{
					return count;
				}
			}
		}
		else if((d._year < d1._year) ||
			((d._year == d1._year)&&(d._month < d1._month)) ||
			((d._year == d1._year)&&(d._month==d1._month)&&(d._day < d1._day)))
		{
			while(1)
			{
				d1.operator--();
				count++;
				if(d._year == d1._year && d._month == d1._month && d._day == d1._day)
				{
					return count;
				}
			}
		}
		return 0;
	}
	

	date operator++(int)
	{
		date tmp(*this);
		_day++;
		while(_day > GetMonDay(_year, _month))
		{
			_day = _day - GetMonDay(_year, _month);
			_month++;
			if(_month > 12)
			{
				_month = 1;
				_year++;
			}
		}
		return tmp;
	}

	date& operator++()
	{
		_day++;
		while(_day > GetMonDay(_year, _month))
		{
			_month++;
			if(_month > 12)
			{
				_month = 1;
				_year++;
			}
			_day = _day - GetMonDay(_year, _month);
		}
		return *this;
	}

	date operator--()
	{
		_day--;
		while(_day <= 0)
		{
			_day =  _day + GetMonDay(_year, _month);
			_month--;
			if(_month < 1)
			{
				_month = 12;
				_year--;
			}
		}
		return *this;
	}

	date operator--(int)
	{
		date tmp(*this);
		_day--;
		while(_day <= 0)
		{
			_day =  _day + GetMonDay(_year, _month);
			_month--;
			if(_month < 1)
			{
				_month = 12;
				_year--;
			}
		}
		return tmp;
	}

	bool operator==(date da)
	{
		return (_year == da._year)&&(_month == da._month)&&(_day == da._day);
	}


	void display()
	{
		cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
	}

	~date()
	{
	}
private:
	int GetMonDay(int year, int month)
	{
		assert(year >= 1900);
		assert(month > 0 && month < 13);

		static int monthArray[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
		int day = monthArray[month - 1];

		if((month == 2) && ((year%400) || ((year%4) && (year%100 != 0))))
		{
			day += 1;
		}
		return day;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	date d1(2016,1,9);
//	d1.operator+(50);
//	d1.operator+=(90);
//	d1.operator-(6);
//	d1.operator-=(2);
//	d1.operator++();
//	d1.operator++(0);
//	d1.operator--();
//	d1.operator--(0);
	date d2(2015,3,8);
	cout<<d1.operator-(d2)<<endl;
	d1.display();
	return 0;
}