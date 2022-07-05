#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
using namespace std;
random_device ran;

//---------------------------------------------------------------- Class Person
class person
{
	string name = " ";
	string post = " ";
	short old = 0;
	int salary = 0;
public:
	person() {};
	string getname() { return name; }
	string getpost() { return post; }
	short getold() { return old; }
	int getsalary() { return salary; }
	void craete();
	void setsalary() { salary *= 1.075; }
	bool operator<(person& t);
	bool operator>(person& t);
	bool operator==(person& t);
	int operator+ (person& t);
	bool operator=(int x);
	friend ostream& operator<<(ostream& os, person t);
	friend istream& operator>>(istream& is, person& t);
};
void person::craete()
{
	cout << "Name: "; cin >> name;
	cout << "Post: "; cin >> post;
	cout << "Old: "; cin >> old;
	cout << "Salary: "; cin >> salary;
}
bool person::operator<(person& t)
{
	return name < t.name;
}
bool person::operator>(person& t)
{
	return name > t.name;
}
bool person::operator==( person& t)
{
	return name == t.name;
}
int person::operator+(person& t)
{
	return salary + t.getsalary();
}
bool person::operator=(int x)
{
	return salary = x;
}
ostream& operator<<(ostream& os, person t)
{
	os << "Name: " << t.name << " Post: " << t.post << " Old: " << t.old << " Salary: " << t.salary;
	return os;
}
istream& operator>>(istream& is, person& t)
{
	string buff;
	getline(is, buff);
	t.salary = stod(buff.substr(buff.rfind(":") + 1));
	buff.erase(buff.rfind("Salary:") + 1);
	t.old = stod(buff.substr(buff.rfind(":") + 1));
	buff.erase(buff.rfind("Old:"));
	t.post = buff.substr(buff.rfind(":") + 1);
	buff.erase(buff.rfind("Post:"));
	t.name = buff.substr(buff.rfind(":") + 1);
	return is;
}

//--------------------------------------------------------------- Class Personal
class personal
{
	vector<person> arr_pers;
public:
	int get_size() { return arr_pers.size(); }
	void addperson(person t);
	void show();
	void sort_name();
	void sort_salary();
	void serch_name(string Name);
	int budget();
	void pension(string tmp);
	void pension();
	void index();
	void min_max_el();
	person operator[](int index);
};
void personal::addperson(person t)
{
	arr_pers.emplace_back(t);
}
void personal::show()
{
	for (int i = 0; i < arr_pers.size(); i++)
	{
		cout << arr_pers[i] << endl;
	}
}
void personal::sort_name()
{
	sort(arr_pers.begin(), arr_pers.end());
}
void personal::sort_salary()
{
	sort(arr_pers.begin(), arr_pers.end(), []( person& t, person& t2) { return t.getsalary() < t2.getsalary(); });
}
void personal::serch_name(string Name)
{
	auto result=find_if(arr_pers.begin(), arr_pers.end(),[Name](person& t) {return t.getname() == Name;  });
	if (result != end(arr_pers))
		cout << "Result: " << *result << endl;
	else
		cout << "Not find " << Name << endl;
}
int personal::budget()
{
	person ptr;
	ptr = accumulate(arr_pers.begin(), arr_pers.end(), ptr, [](person t1, person t2) { return t1.getsalary() + t2.getsalary(); });
	cout << ptr.getsalary();
	return 0;
}
void personal::pension(string tmp)
{
	for (int i = 0; i < arr_pers.size(); i++)
	{
		if (arr_pers[i].getname() == tmp)
		{
			cout << "Сотрудник " << arr_pers[i].getname() << " отправлен на пенсию";
			arr_pers.erase(arr_pers.begin() + i);
		}
	}
}
void personal::pension()
{
	for (int i = 0; i < arr_pers.size(); i++)
	{
		if (arr_pers[i].getold() >= 65)
		{
			cout << "Сотрудник " << arr_pers[i].getname() << " отправлен на пенсию";
			arr_pers.erase(arr_pers.begin() + i);
		}
	}
}
void personal::index()
{
	for (int i = 0; i < arr_pers.size(); i++)
	{
		arr_pers[i].setsalary();
	}
}
void personal::min_max_el()
{
	auto ptr = minmax_element(arr_pers.begin(), arr_pers.end(), [](person& t1, person& t2) {return t1.getsalary() < t2.getsalary(); });
	cout << *ptr.first << *ptr.second << endl;
}
person personal::operator[](int index)
{
	return arr_pers[index];
}

//--------------------------------------------------------- Class ifof для записи 
class ifofstream
{
	string filename = "file.txt";
public:
	ifofstream() {};
	ifofstream(string Filename) :filename(Filename) {};
	void ifstr(personal& x);
	void ofstr(personal& x);
};
void ifofstream::ifstr(personal& x)
{
	ifstream ifs;
	ifs.open(filename);
	if (ifs.is_open())
	{	
		while (!ifs.eof())
		{
			person y;
			ifs >> y;
			x.addperson(y);
		}
	}
	else
		cout << "error open file ";
}
void ifofstream::ofstr(personal& x)
{
	ofstream ofs;
	ofs.open(filename,ios_base::app);
	if (ofs.is_open())
	{
		ofs << endl;
		for (int i = 0; i < x.get_size(); i++)
		{
			ofs << x[i];
			if (x.get_size() - 2 >= i)
				ofs << endl;
		}
		ofs.close();
	}
	else
		cout << "error open file ";
}
//----------------------------------------------------------------------
int main()
{
	setlocale(LC_ALL, "rus");
	personal test, test2;
	ifofstream x;
	for (int i = 0; i < 3; i++)
	{
		person t;
		t.craete();
		test.addperson(t);
	}
	test.show();
	x.ifstr(test2);
	test2.show();
	x.ofstr(test);
}