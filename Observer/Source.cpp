#include <iostream>
using namespace std;
#include <string>
#include <vector>
	/*
	 * ������� ����������� ��������� ���������� ��������������� ����� ��������� ����� �������,
	 * ��� ���� ���� �� ��� ������ ��� ���������, ��������� ��� �� �� ���� �����������.
	 * ��������� ������ ����������� ����� ��������� ������� Subject � Observer, ����� ������ �� ���������� ���� �� �����.
	 */



	 /*
		 Observer - �����������: ��� ����� ������� ����� ��� ���� ��������� ������������.
				  - ���������� ��������� ���������� ��� ��������, ������� ������ ���� ���������� �� ��������� ��������;
		 */
class Customer abstract
{
	string name;
	int age;
public:
	virtual void PurchaseProduct() abstract;
};


/* Subject
- �������: ����������� ����������� � ����� ������������. �� ��������� ����� ��������� ����� ����� ������������;
- ������������� ��������� ��� ������������� � ��������� ������������;
*/


class Shop abstract
{
	vector<Customer*> customers;
public:
	void Add(Customer* observer)
	{
		customers.push_back(observer);//��������� ������� � ����� �������
	}
	void Remove(Customer* observer)//������� 
	{
		auto iter = find(customers.begin(), customers.end(), observer);
		if (iter != customers.end())
			customers.erase(iter);
	}
	void ReceivingProduct()
	{
		for (Customer* o : customers)
		{
			o->PurchaseProduct();//��� ������� ���������(����������-�����������) ���������� ������ ������� .
		}
	}
};

/*
  ConcreteSubject - ���������� �������:
	 - ��������� ���������, �������������� ������� ��� ����������� ����������� ConcreteObserver;
	 - �������� ���������� ����� ������������, ����� ���������� ���������;
*/
class ConcreteShop : public Shop
{
	string producer;
	double price;
	string brand;
public:
	string GetProducer()
	{
		return producer;
	}
	void SetProducer(string p)
	{
		producer = p;
	}
	double GetPrice()
	{
		return price;
	}
	void SetPrice(double p)
	{
		price = p;
	}
	string GetBrand()
	{
		return brand;
	}
	void SetBrand(string b)
	{
		brand = b;
	}
};


/*
 ConcreteObserver - ���������� �����������:
	 - ������ ������ �� ������ ������ ConcreteSubject;
	 - ��������� ������, ������� ������ ���� ����������� � ������� ��������;
	 - ��������� ��������� ����������, ������������ � ������ Observer, ����� ������������ ��������������� � ���������.
*/

class ConcreteCustomer : public Customer
{
	ConcreteShop* shop;//������������� ������ ����
	string name;
	int age;

public:
	ConcreteCustomer(ConcreteShop* shop, string name,int age)//�������������
	{
		this->shop = shop;
		this->name = name;
		this->age = age;
	}
	void PurchaseProduct() override//�������������� � ���������� �����
	{
		
		cout << "Producer: " << shop->GetProducer() << ". Price: " << shop->GetPrice() << ". Brand: " << shop->GetBrand() << "." << endl;
		cout << name << " (" << age <<")" << endl;
		
	}
	ConcreteShop* GetShop()//����������
	{
		return this->shop;
	}
	void SetShop(ConcreteShop* shop)//�������������
	{
		this->shop = shop;
	}
};







	


int main()
{
	ConcreteShop* pShop = new ConcreteShop();//������� ������ ������� ���������� �������

	Customer* o1 = new ConcreteCustomer(pShop, "Observer #1",18);
	Customer* o2 = new ConcreteCustomer(pShop, "Observer #2",54);
	Customer* o3 = new ConcreteCustomer(pShop, "Observer #3",29);

	pShop->Add(o1);//��������� � ����� �����������
	pShop->Add(o2);
	pShop->Add(o3);

	pShop->SetProducer("Odesa");
	pShop->SetPrice(20);
	pShop->SetBrand("Nike");
	pShop->ReceivingProduct();//��������� �������

	pShop->Remove(o2);
	pShop->ReceivingProduct();

	pShop->Remove(o1);
	pShop->ReceivingProduct();

	delete pShop;
	delete o1;
	delete o2;
	delete o3;

	system("pause");
	return 0;
}