#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class FoodStore {     			
  	public:
    	int menuSize = 8;		// Number of menu items
		bool isMemberCard;		// Customer uses member card (use: true, not used: false)
		string menuName[7] 	= {"Red", "Green", "Blue", "Yellow", "Pink", "Purple", "Orange"}; // Name in food menu
		float menuPrice[7] 	= {50, 40, 30, 50, 80, 90, 120}; // Price in food menu
		int sumOrder[7] 	= { 0,  0,  0,  0,  0,  0,   0}; // default value on index => Red = 0, Green = 1, Blue = 2, Yellow = 3, Pink = 4, Purple = 5, Orange = 6
		float sumPrice[7] 	= { 0,  0,  0,  0,  0,  0,   0}; // default value on index => Red = 0, Green = 1, Blue = 2, Yellow = 3, Pink = 4, Purple = 5, Orange = 6
	
	int getMenuSize() {
		return menuSize;
	}
	
	string getMenuName(int menu) { // menu is -1
		return menuName[menu];
	}
	
	// Food label
	void getMenu() {
		cout << " ======================= Menu ====================== \n";
		for (int i=0; i<menuSize; i++) {
			if (i==7) {
				cout << " (" << (i+1) << ") Pay for food \n";
			} else {
				cout << " (" << (i+1) << ") " << menuName[i] << " set			" << menuPrice[i] << "	THB/set \n";
			}
		}
		cout << " =================================================== \n";
	}
	
	// Shopping cart
	void getSummary() {
		bool showHeader = true;
		for (int i=0; i<(menuSize-1); i++) {
			if (sumOrder[i] > 0) {
				if(showHeader) {
					cout << "=> Menu is selected  \n";
					showHeader = false;	
				}
				cout << menuName[i] << " " << sumOrder[i] << " set, ";
			}
		}
		if (!showHeader) {
			cout << "\n---------------------------------------------------- \n";
		}
	}
	
	// Cost summary
	void getBilling() {
		bool showHeader = true;
		float totalPrice = 0;
		float totalOrder = 0;
		for (int i=0; i<(menuSize-1); i++) {
			if (sumOrder[i] > 0) {
				if(showHeader) {
					cout << "********************** Billing ********************* \n";
					
					if (isMemberCard) {
						cout << "Use member card \n";
					}
					
					cout << "---------------------------------------------------- \n";
					cout << "List		Amount		Price \n";
					cout << "---------------------------------------------------- \n";
					showHeader = false;	
				}
				
				// sum 
				totalOrder += sumOrder[i];
				totalPrice += sumPrice[i];
				
				cout << menuName[i] << "		" << sumOrder[i] << " set		" << sumPrice[i] << " THB \n";
			}
		}
		cout << "---------------------------------------------------- \n";
		cout << "TOTAL		" << totalOrder << " set		" << totalPrice << " THB \n";
	}
	
	void calcuratePrice(int menu, int amount){ // menu - 1
		float tmpPrice = 0;
		// Customers can get 10% if customers have a member card.
		if (isMemberCard) { // discount is true
			tmpPrice = menuPrice[menu] - (menuPrice[menu]*0.1);
		} else {
			tmpPrice = menuPrice[menu];
		}
		
		sumPrice[menu] = (sumOrder[menu] + amount) * tmpPrice;
		sumOrder[menu] = (sumOrder[menu] + amount);
		
		// Order doubles of Orange, Pink or Green sets will get a 5% discount.
		if (((menu+1) == 2 || (menu+1) == 5 || (menu+1) == 7) && sumOrder[menu] >= 2) {
			sumPrice[menu] = sumPrice[menu] - (sumPrice[menu]*0.05);
		}
	} 

	void insMemberCard(){
		string tmpMemberCard = "";
		bool isMmCdRunning = true;
		while(isMmCdRunning) {
			cout << "-> Customer have member card ? (Y/N) : ";
			cin >> tmpMemberCard;
			if (tmpMemberCard == "Y" ) {
				isMemberCard = true;
				isMmCdRunning = false;
			} else if (tmpMemberCard == "N") {
				isMemberCard = false;
				isMmCdRunning = false;
			} else {
				cout << "Member card format incorrect, Please try again ! \n";
			}
		}
	}
	
	bool isNumber(string str) {
	    double d;
	    istringstream is(str);
	    is >> d;
	    return !is.fail() && is.eof();
	}
};

int main() {
	string tmpMenu;
	string tmpAmount;
	bool isMenuRunning = true;

	FoodStore fs;
	
	fs.getMenu();

	fs.insMemberCard();
	
	// Take orders
	while(isMenuRunning){
		fs.getSummary();
		
		cout << "-> Please enter menu (?) : ";
		cin >> tmpMenu;
		
		stringstream ssTmpMenu;
		ssTmpMenu << tmpMenu; 
		int tmpMenuInt;
		ssTmpMenu >> tmpMenuInt;
		
		if (tmpMenuInt >= 1 && tmpMenuInt <= (fs.getMenuSize()-1)) { // Menu 1-7
			bool isReceiveAmount = true;
			while(isReceiveAmount){
				cout << "-> Please enter amount of " << fs.getMenuName(tmpMenuInt-1) << " : ";
				cin >> tmpAmount;
				cout << "---------------------------------------------------- \n";
				
				stringstream ssTmpAmount;
				ssTmpAmount << tmpAmount; 
				int tmpAmountInt;
				ssTmpAmount >> tmpAmountInt;
				if(fs.isNumber(tmpAmount)){
					fs.calcuratePrice(tmpMenuInt-1, tmpAmountInt);
					isReceiveAmount = false;
				} else {
					cout << "Amount format incorrect, Please try again ! \n";
				}
			}
		} else if (tmpMenuInt == fs.getMenuSize()) { // Menu 8 
			isMenuRunning = false;
			fs.getBilling();
		} else {
			cout << "Menu format incorrect, Please try again ! \n";
		}
	}	
	
  	return 0;
}
