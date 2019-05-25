#include <unordered_map>
#include <string>
#include <utility>
#include <cstdint>
#include <ctime>
#include <set>
#include <iostream>
#include <queue>

enum speciality { Cashier, Consultant };

using namespace std;

class Animal {
protected:
	string species;
	string shortName;
	string name;
	bool gender;			// BEN SHAPIRO DESTROYS LIBERALS WITH FACTS AND LOGIC
public:
	Animal(
		string species,
		string shortName,
		string name,
		bool gender) :
		species{ species }, 
		shortName{ shortName },
		name{ name },
		gender{ gender }
	 {}
	Animal(const Animal &a) :
		species{ a.species },
		shortName{ a.shortName },
		name{ a.name },
		gender{ a.gender }
	{}
	string getSpecies() const {
		return species;
	}
	string getShortName() const {
		return shortName;
	}
	string getName() const {
		return name;
	}
	bool getGender() const {
		return gender;
	}
};


class Human : public Animal {
protected:
	string surname;
public:
	Human(
		string name,
		string surname,
		bool gender) :
		Animal("Homo Sapiens", "Human", name, gender),
		surname{ surname }
	{}
	Human(const Human &h) :
		Animal("Homo Sapiens", "Human", h.name, h.gender),
			surname{ h.surname }
	{}
	string getSurname() const {
		return surname;
	}
	string Fullname() const {
		return name + ' ' + surname;
	}
};

class Worker : public Human {
protected:
	set<speciality> specialities;
public:
	Worker(
		string name,
		string surname,
		bool gender) : 
		Human(name, surname, gender)
	{}
	Worker(const Worker &w) :
		Human(w.name, w.surname, w.gender)
	{}
	void addSpeciality(speciality s) {
		specialities.insert(s);
	}
	void removeSpeciality(speciality s) {
		specialities.erase(s);
	}
	bool checkSpeciality(speciality s) {
		return specialities.find(s) != specialities.end();
	}
};

class Item {
protected:
	int price;
public:
	Item(int price) :
		price { price }
	{}
	int getPrice() {
		return price;
	}
	void setPrice(int p) {
		price = p;
	}
	virtual void print() {
		cout << "Item of price: " << price << endl;
	}
};

class AnimalItem : public Item, public Animal {
public:
	AnimalItem(int price, Animal animal) : Item(price), Animal(animal)
	{}
	void print() override  {
		cout << shortName << " of price: " << price << endl;
	}
};

class FoodItem : public Item {
protected:
	int weight;
	string can_feed;
public:
	FoodItem(int price, int weight, string can_feed) : 
		weight{ weight }, can_feed{ can_feed }, Item(price) 
	{}
	void print() override  {
		cout << "Food item of weight: " << weight << " and price: "
			<< price << " for feeding " << can_feed << endl;
	}
};

class CageItem : public Item {
protected:
	int capacity;
	int size = 0;
	vector<AnimalItem*> animals;
	string animaltype;
public:
	CageItem(int price, int capacity, string animaltype) : 
		capacity{ capacity }, animaltype{ animaltype } , Item(price)
	{}
	int animalCount() {
		return animals.size();
	}
	bool addAnimal(AnimalItem* a) {
		if (a->getShortName() == animaltype && size < capacity) {
			animals.push_back(a);
			size++;
			return true;
		}
		else {
			cout << "Cannot place that animal in this cage" << endl;
			return false;
		}
	}
	int full_price() {
		int p = getPrice();
		for (unsigned i = 0; i < animals.size(); i++) {
			p += animals[i]->getPrice();
		}
		return p;
	}
	void print() override {
		cout << "A cage of price: " << price << " for " << animaltype <<
			" that contains " << animalCount() << " animals of total price " << full_price() << endl;;
	}
};

class Client {
private:
	bool needsCons;
	bool wtb;
	Item* wtb_item;
	Worker* assigned_worker;
public:
	Client(bool needsCons, bool wtb, Item* wtb_item = 0) : 
		needsCons{ needsCons }, wtb{wtb}, wtb_item{ wtb_item }{}
	void print() {
		cout << "Client that ";
		if (needsCons) {
			cout << "needs consultation";
		}
		else {
			cout << "doesn't need consultation";
		}
		if (wtb) {
			cout << " and wants to buy ";
			wtb_item->print();
		}
		else {
			cout << endl;
		}
	}
	bool NeedCons() {
		return needsCons;
	}
	void addWorker(Worker* w) {
		assigned_worker = w;
	}
	Worker* popWorker() {
		Worker* w = assigned_worker;
		assigned_worker = 0;
		return w;
	}
	Worker* getWorker() {
		return assigned_worker;
	}
	void Consult() {
		needsCons = false;
	}
	void SellItem() {
		wtb = false;
	}
	bool wantsToBuy() {
		return wtb;
	}
	Item* getItem() {
		return wtb_item;
	}
};




class StoreManager {
private:
	vector<Worker*> staff;
	vector<Item*> items;
	vector<bool> staff_free;
	queue<Client*> clients;
	int profit = 0;
public:
	StoreManager(vector<Worker*> staff) : staff{ staff } {
		for (unsigned i = 0; i < staff.size(); i++) {
			staff_free.push_back(0);
		}
	}
	void addItem(Item* it) {
		if (dynamic_cast<AnimalItem*>(it) != NULL) {
			AnimalItem* ait = dynamic_cast<AnimalItem*>(it);
			for (unsigned i = 0; i < items.size(); i++) {
				CageItem* cit = dynamic_cast<CageItem*>(items[i]);
				if (cit != NULL && cit->addAnimal(ait)) {
					return;
				}
			}
			cout << "Cannot find suitable cage for that animal" << endl;
		}
		else {
			items.push_back(it);
			cout << "Added item: ";
			it->print();
		}
	}
	void sellItem(Item* it) {
		for (unsigned i = 0; i < items.size(); i++) {
			if (it == items[i]) {
				swap(items[i], items[items.size()-1]);
				items.pop_back();
				profit += it->getPrice();
				cout << "Sold item: ";
				it->print();
			}
		}
	}
	bool checkItem(Item* it) {
		for (unsigned i = 0; i < items.size(); i++) {
			if (it == items[i]) {
				return true;
			}
		}
		return false;
	}
	Worker* assignWorker(speciality s) {
		for (unsigned i = 0; i < staff.size(); i++) {
			if (!staff_free[i] and staff[i]->checkSpeciality(s)) {
				staff_free[i] = 1;
				return staff[i];
			}
		}
		cout << "Cannot find necessary worker" << endl;
		return 0;
	}
	void unassignWorker(Worker* w) {
		for (unsigned i = 0; i < staff.size(); i++) {
			if (staff[i] == w) {
				staff_free[i] = 0;
			}
		}
	}
	void addClient(Client* c) {
		c->print();
		clients.push(c);
	}
	void serviceNextClient() {
		Client* c = clients.front();
		clients.pop();
		Worker* w;
		if (c->getWorker() != 0) {
			unassignWorker(c->popWorker());
		}
		if (c->NeedCons()) {
			w = assignWorker(Consultant);
			if (w != 0) {
				c->addWorker(w);
				c->Consult();
				clients.push(c);
			}
			else {
				cout << "Client left because he wasn't consulted in time" << endl;
			}
		}
		else if (c->wantsToBuy()) {
			if (checkItem(c->getItem())) {
				sellItem(c->getItem());
				w = assignWorker(Cashier);
				if (w != 0) {
					c->addWorker(w);
					c->SellItem();
					clients.push(c);
				}
				else {
					cout << "Client left because his item wasn't sold in time" << endl;
				}
			}
		}
	}
	bool hasClients() {
		return clients.size();
	}
};


int main() {
	vector<Worker*> staff;
	staff.push_back(new Worker("Cordelia", "Beaumont", 0));
	staff.push_back(new Worker("Iolo", "Nieves", 1));
	staff.push_back(new Worker("Devonte", "Matthams", 1));
	staff.push_back(new Worker("Jana", "Reilly", 0));
	staff.push_back(new Worker("Ava", "Mccormick", 0));
	staff[0]->addSpeciality(Cashier);
	staff[0]->addSpeciality(Consultant);
	staff[1]->addSpeciality(Consultant);
	staff[2]->addSpeciality(Cashier);
	staff[3]->addSpeciality(Cashier);
	staff[4]->addSpeciality(Cashier);
	staff[4]->addSpeciality(Consultant);
	StoreManager mng(staff);
	Item* it1 = new FoodItem(100, 10, "Cat");
	Item* it2 = new FoodItem(15, 1, "Hamster");

	Item* it3 = new CageItem(1000, 1, "Cat");
	Item* it4 = new CageItem(500, 3, "Rat");
	Item* it5 = new CageItem(200, 1, "Hamster");
	Item* it6 = new CageItem(300, 2, "Hamster");

	Animal an1 = Animal("Phodopus sungorus", "Hamster", "Hamster_1", 1);
	Animal an2 = Animal("Phodopus sungorus", "Hamster", "Hamster_2", 0);
	Animal an3 = Animal("Felis Catus", "Cat", "Tibbles", 1);
	Animal an4 = Animal("Felis Catus", "Cat", "Meower", 1);
	Animal an5 = Animal("Rattus rattus", "Rat", "Rat_1", 1);
	Item* it7 = new AnimalItem(300, an1);
	Item* it8 = new AnimalItem(400, an2);
	Item* it9 = new AnimalItem(3000, an3);
	Item* it10 = new AnimalItem(2000, an4);
	Item* it11 = new AnimalItem(500, an5);

	mng.addItem(it1);
	mng.addItem(it2);
	mng.addItem(it3);
	mng.addItem(it4);
	mng.addItem(it5);
	mng.addItem(it6);
	mng.addItem(it7);
	mng.addItem(it8);
	mng.addItem(it9);
	mng.addItem(it10);
	mng.addItem(it11);
	
	Client* cl1 = new Client(0, 1, it1);
	Client* cl2 = new Client(1, 0, 0);
	Client* cl3 = new Client(1, 1, it5);
	Client* cl4 = new Client(0, 1, it2);

	mng.addClient(cl1);
	while (mng.hasClients()) {
		mng.serviceNextClient();
	}
	mng.addClient(cl1);
	mng.addClient(cl2);
	mng.addClient(cl3);
	while (mng.hasClients()) {
		mng.serviceNextClient();
	}
	return 0;
}



