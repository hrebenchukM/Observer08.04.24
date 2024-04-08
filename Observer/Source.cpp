#include <iostream>
using namespace std;
#include <string>
#include <vector>
	/*
	 * Паттерн Наблюдатель позволяет определить взаимоотношения между объектами таким образом,
	 * что если один из них меняет своё состояние, остальные тут же об этом оповещаются.
	 * Благодаря слабой связанности между объектами классов Subject и Observer, можно менять их независимо друг от друга.
	 */



	 /*
		 Observer - наблюдатель: это общий базовый класс для всех возможных наблюдателей.
				  - определяет интерфейс обновления для объектов, которые должны быть уведомлены об изменении субъекта;
		 */
class Customer abstract
{
	string name;
	int age;
public:
	virtual void PurchaseProduct() abstract;
};


/* Subject
- субъект: располагает информацией о своих наблюдателях. За субъектом может «следить» любое число наблюдателей;
- предоставляет интерфейс для присоединения и отделения наблюдателей;
*/


class Shop abstract
{
	vector<Customer*> customers;
public:
	void Add(Customer* observer)
	{
		customers.push_back(observer);//добавляет єлемент в конец вектора
	}
	void Remove(Customer* observer)//удаляет 
	{
		auto iter = find(customers.begin(), customers.end(), observer);
		if (iter != customers.end())
			customers.erase(iter);
	}
	void ReceivingProduct()
	{
		for (Customer* o : customers)
		{
			o->PurchaseProduct();//Для каждого обсервера(подписчика-наблюдателя) генерируем апдейт событие .
		}
	}
};

/*
  ConcreteSubject - конкретный субъект:
	 - сохраняет состояние, представляющее интерес для конкретного наблюдателя ConcreteObserver;
	 - посылает информацию своим наблюдателям, когда происходит изменение;
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
 ConcreteObserver - конкретный наблюдатель:
	 - хранит ссылку на объект класса ConcreteSubject;
	 - сохраняет данные, которые должны быть согласованы с данными субъекта;
	 - реализует интерфейс обновления, определенный в классе Observer, чтобы поддерживать согласованность с субъектом.
*/

class ConcreteCustomer : public Customer
{
	ConcreteShop* shop;//инкапсулирует обьект клок
	string name;
	int age;

public:
	ConcreteCustomer(ConcreteShop* shop, string name,int age)//Инициализация
	{
		this->shop = shop;
		this->name = name;
		this->age = age;
	}
	void PurchaseProduct() override//Переопределяем и показываем время
	{
		
		cout << "Producer: " << shop->GetProducer() << ". Price: " << shop->GetPrice() << ". Brand: " << shop->GetBrand() << "." << endl;
		cout << name << " (" << age <<")" << endl;
		
	}
	ConcreteShop* GetShop()//Возвращаем
	{
		return this->shop;
	}
	void SetShop(ConcreteShop* shop)//устанавливаем
	{
		this->shop = shop;
	}
};







	


int main()
{
	ConcreteShop* pShop = new ConcreteShop();//Создаем обьект который инициирует событие

	Customer* o1 = new ConcreteCustomer(pShop, "Observer #1",18);
	Customer* o2 = new ConcreteCustomer(pShop, "Observer #2",54);
	Customer* o3 = new ConcreteCustomer(pShop, "Observer #3",29);

	pShop->Add(o1);//добавляем в конец подписчиков
	pShop->Add(o2);
	pShop->Add(o3);

	pShop->SetProducer("Odesa");
	pShop->SetPrice(20);
	pShop->SetBrand("Nike");
	pShop->ReceivingProduct();//Генерация события

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