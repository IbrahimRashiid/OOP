
#include <iostream>
using namespace std;

class Item {
private:
	string name;
	double price;
	int quantity, itemID;;
	static int ID;
	friend class Seller;

public:
    //default constructor
	Item() {
		name = "NULL";
		price = 0.0;
		quantity = 0;
		itemID = ID-1;

	}
	//parameterized constructor
	Item(string Name, double Price, int quan) {
		name = Name;
		price = Price;
		quantity = quan;
		ID++;
		itemID = ID;
	}
	//copy constructor
	Item(Item& obj) {
		name = obj.name;
		price = obj.price;
		quantity = obj.quantity;
		ID++;
		itemID = ID;
	}
	void setName(string name) {
		this->name = name;
	}
	void setPrice(double price) {
		this->price = price;
	}
	void setQuantity(int quantity) {
		this->quantity = quantity;
	}
	void setID() {
		ID;
	}
	string getName() {
		return name;
	}
	double getPrice() {
		return price;
	}
	int getQuantity() {
		return quantity;
	}
	int getID() {
		return ID;
	}
	bool operator ==(const Item& obj1);
	Item operator+=(const Item& obj2);
	Item operator -=(const Item& obj3);
	friend istream& operator>>(istream& is, Item& itm);
	friend ostream& operator<<(ostream& os, const Item& itm);
};
// check if two items have the same type
bool Item::operator==(const Item& obj1) {
	if (name == obj1.name)
		return true;
	else
		return false;
}
// Adding quantities of items of the same type
Item Item::operator+=(const Item& obj2) {
	Item result;
	result=obj2;
	result.quantity = (quantity += obj2.quantity);
	return result;
}
// subtract quantities of items of the same type
Item Item::operator-=(const Item& obj3) {
	Item result2;
	result2 = obj3;
	result2.quantity = (quantity -= obj3.quantity);
	return result2;
}
// Reading the item iformation
istream& operator>>(istream& is, Item& itm) {
	cout << "Please Enter the Name of the item:\n ";
	is >> itm.name;
	cout << "Please Enter the Price of the item:\n ";
	is >> itm.price;
	cout << "Please Enter the quantity of the item:\n ";
	is >> itm.quantity;
	return is;
}
// printing the Item iformation
ostream& operator<<(ostream& os, const Item& itm) {
	os << "Name: " << itm.name << endl
		<< "ID: " << itm.itemID << endl
		<< "Price: " << itm.price << " L.E\n"
		<< "quantity:" << itm.quantity << endl;
	return os;
}
int Item::ID = 0;

class Seller {
private:
	string name, email;
	int maxItem;
	Item* items;
public:
    //parameterized constructor
	Seller(string name, string email, int maxItem) {
		this->name = name;
		this->email = email;
		this->maxItem = maxItem;
		items = new Item[maxItem];
	}
	void SetName(string name) {
		this->name = name;
	}
	void SetEmail(string eamil) {
		this->email = email;
	}
	// Add an item to the seller list
	bool AddAnItem(Item AddedItem);
	// sell an item from the seller list
	bool SellAnItem(string SoldItem, int &SoldQuantity);
	// Print all Items in the seller list
	void PrintItems();
	// searching for a specific item by its ID
	Item FindAnItemByID(int id);
	// printing the seller information
	friend ostream& operator<<(ostream& COUT, Seller& seller);
	// Reading the seller information from the user
	friend istream& operator>>(istream& CIN, Seller& seller);

	~Seller() { delete[] items; }
};
bool Seller:: AddAnItem(Item AddedItem) {
		for (int i = 0; i < maxItem; i++) {
			if (AddedItem == items[i]) {
				items[i] += AddedItem;
				AddedItem.ID--;
				return true;
			}
		}
		if (AddedItem.ID <= maxItem) {
			items[AddedItem.ID-1] = AddedItem;
			return true;
		}
		return false;
	}
bool Seller:: SellAnItem(string SoldItem, int &SoldQuantity) {
		bool found = false;
		for (int i = 0; i < maxItem; i++) {
			if (items[i].name  == SoldItem)
				found = true;
			if (found) {
				if (SoldQuantity <= items[i].quantity)
					items[i].quantity -= SoldQuantity;
				else
					found = false;
			}
		}
            if(found == false)
                cout<<"Cant complete the selling process.\n";
		return found;
	}
void Seller::PrintItems() {
		for (int i = 0; i < maxItem; i++) {
			cout << items[i]<<endl<<endl;
		}
	}
Item Seller::FindAnItemByID(int id) {
		for (int i = 0; i < maxItem; i++) {
			if (id == items[i].itemID){
				return items[i];
		}
		}
	}
istream& operator>>(istream& CIN, Seller& seller) {
	cout << "Please Enter Your Name : \n";
	CIN >> seller.name;
	cout << "Please Enter Your Email : \n";
	CIN >> seller.email;
	cout << "Please Enter the Maximum Store Capacity: \n";
	CIN >> seller.maxItem;
	return CIN;
}
ostream& operator<<(ostream& COUT, Seller &seller) {
	COUT << "Seller Name: " << seller.name << endl
		<< "Seller Email: " << seller.email << endl
		<< "Maximum Items Number: " << seller.maxItem << endl;
	return COUT;
}
// showing the menu to the user
void menu() {
	cout << "\nPlease Choose a Number.\n\n"
		<< "1-Print My Info.\n"
		<< "2-Add An Item.\n"
		<< "3-Sell An Item.\n"
		<< "4-Print Items.\n"
		<< "5-Find an Item by ID\n"
		<< "6-Exit.\n";
}
// processing the user choise
void Choose(int &choise,Seller &seller,Item &AddedItem,string &SoldItemName,int &SoldItemQuantity,int &FindID) {
	switch (choise)
	{
    case 1:
		cout<< "\n1-Print My Info.\n\n";
		cout << seller;
		menu();
		cin>>choise;
		Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);

	case 2:
	    cout<<"\n2-Add An Item.\n\n";
		cin >> AddedItem;
		seller.AddAnItem(AddedItem);
		menu();
		cin>>choise;
		Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);
	case 3:
	    cout<<"\n3-Sell An Item.\n\n"
	    <<"Please Enter the name of the item you want to sell:\n";
		cin >> SoldItemName;
		cout << "Please Enter the quantity of item you want to sell:\n ";
		cin >> SoldItemQuantity;
		seller.SellAnItem(SoldItemName,SoldItemQuantity);
		menu();
		cin>>choise;
		Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);
	case 4:
	    cout<<"\n4-Print Items.\n\n";
		seller.PrintItems();
		menu();
		cin>>choise;
		Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);
	case 5:
		cout << "\n5-Find an Item by ID\n\n"<<"Please enter the ID of the item you want to find: \n";
		cin >> FindID;
		cout << seller.FindAnItemByID(FindID);
		menu();
		cin>>choise;
		Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);
	case 6:
	    cout<< "\n6-Exit.\n\n";
		break;
    default:
        cout<<endl<<"Invalid Input! \n\n";
        menu();
	    cin>>choise;
		Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);
        }
	}

int main() {
    string SellerName ,email,SoldItemName;
    Item AddedItem;
	int choise=0,maxQuantity=0, SoldItemQuantity=0,FindID=0;

	cout<<"Please Enter your Name: \n";
	getline(cin,SellerName);
	cout<<"Please Enter your Email: \n";
	cin>>email;
	cout<<"Please Enter your Store Capacity: \n";
	cin>>maxQuantity;

	Seller seller(SellerName,email,maxQuantity);

	menu();
		cin>>choise;

    Choose(choise, seller, AddedItem, SoldItemName, SoldItemQuantity, FindID);

}
