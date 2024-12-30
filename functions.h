#include<iostream>
using namespace std;
#include"menu.h"
#include "order.h"
#include "customerManager.h"
#include "customer.h"
#include "orderItem.h"
#include "menuItem.h"
#include "loyalityProgram.h"
#include <ctime>
#include<string>
#include"loyalityProgram.h"


int checkLoyalityPoints(string Name){
	string FN="customerData.csv";
		ifstream checkData(FN);
	
	if(!checkData.is_open()){
		return 0 ;
	}

	string line,name,contactDetails,dietryPrefences,id,loyalityPoints;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,dietryPrefences,',');
	     getline(ss,contactDetails,',');
	     getline(ss,loyalityPoints,',');
	     getline(ss,id,',');
	     if(name==Name){
	     	return stoi(loyalityPoints);
	     	break;
		 }
	     
	}
	
	checkData.close();
	return 0;
}

 string getCurrentDateTime() {
    time_t now = time(0);  // Get the current time
    char* dt = ctime(&now);  // Convert to a string
    return string(dt);
}
///////////////////////////////////       Generating Unique Customer Id ///////////////////////////////////////////////////////////////////////
long readCustomerLastID() {
	string fileName = "last_Customer_id.txt";
    ifstream file(fileName);
    long lastID = 1;

    if (file.is_open()) {
        file >> lastID;
        file.close();
    }

    return lastID;
}

void saveCustomerLastID(long lastID) {
	string fileName = "last_Customer_id.txt";
    ofstream file(fileName);

    if (file.is_open()) {
        file << lastID;
        file.close();
    }
}

string generateCustomerUniqueID(int& currentID) {
    return "CUST" + to_string(currentID++);
}
/////////////////////////////////////////////////////////////////////////// END ///////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////    ID OF Menu Item /////////////////////////////////////////////////////////////
int readMenuItemLastID() {
	string fileName = "last_MenuItem_id.txt";
    ifstream file(fileName);
    int lastID = 21;

    if (file.is_open()) {
        file >> lastID;
        file.close();
    }

    return lastID;
}

void saveMenuItemLastID(int lastID) {
	string fileName = "last_MenuItem_id.txt";
    ofstream file(fileName);

    if (file.is_open()) {
        file << lastID;
        file.close();
    }
}

int generateMenuItemUniqueID(int& currentID) {
    return currentID++;
}

///         All input and fucntionalities



void userInputAddItem(Menu &menu) {
   
    string name, category;
    int stock,id;
    double price;

                cout << "\n---------------Adding Item ----------------\n";
                cout << "Enter name of item: ";
                getline(cin, name);
        

                cout << "Enter price of item: ";
                cin >> price;
                cin.ignore();

                cout << "Enter stock of item: ";
                cin >> stock;
                cin.ignore();

                cout << "Enter category of item: ";
                getline(cin, category);
                menu.addCategory(category);
                
                int lastId=readMenuItemLastID();
                id= generateMenuItemUniqueID(lastId);
                saveMenuItemLastID(lastId);
               
           
               
                
                MenuItem *item = new MenuItem(name, category,stock, price,id);
                menu.addItem(item); 
                menu.writeMenuData(name,category,stock,price,item->getId());
                cout << "Item added successfully!" << endl; 
                cout << "----------------------------------------\n";
                
}



void registerCustomer(CustomerManager &manager){
	
	    string name,prefences,contactDetails;
         int lastId;

                cout << "\n---------------Registering.. Customer ----------------\n";
                cout << "Enter name of Customer: ";
                getline(cin, name);
        

                cout << "Enter Dietry Prefences of Customer: ";
                getline(cin,prefences);
            

                cout << "Enter Contact Details of the Customer : ";
                getline(cin,contactDetails);
                
                lastId=readCustomerLastID();
                string uniqueid=generateCustomerUniqueID(lastId);
                saveCustomerLastID(lastId);
                
                

               manager.registerCustomer(name,prefences,contactDetails,uniqueid);
             


                cout << "----------------------------------------\n";
	
}



 void orderItem(Menu &menu,CustomerManager &manager){
 	Customer *c;
 	MenuItem *m;
 	
 	
 	            bool is_True=true;
 	            int choice;
 	            string  name,customization;
 	            int id,quantity;
 	            Order *order=new Order();
 	            
 	            cout<<"Enter customer name to order: ";
 	            getline(cin,name);
 	            c=manager.findCustomerByName(name);
 	            if(c!=nullptr){
 	            	
 	            jump:
				cout<<"Enter id of the item to order :";
				cin>>id;
				cin.ignore();
				
					m=menu.searchItemById(id);
				
			if(m!=nullptr){
				cout<<"Enter quantity of the item: ";
				cin>>quantity;
				cin.ignore();
				cout<<"Enter Customizations if u want to else enter none: ";
				getline(cin,customization);
				order->addItem(m,quantity,customization);
				
			}
			else{
				cout<<"Item not found\n";
				//return;
				goto jump;
			}
			
			
			while(is_True){
				cout<<"Enter 1 to order another item\n";
				cout<<"Enter 2 to confirm and view recipt\n";
				cout<<"Enter 3 to exit order \n";
				
				cin>>choice;
				cin.ignore();
				
				
				
				switch(choice){
					
					case 1:{
						
				cout<<"Enter id of the item to order :";
				cin>>id;
				cout<<"Enter quantity of the item: ";
				cin>>quantity;
				cin.ignore();
				cout<<"Enter Customizations if u want to else enter none: ";
				getline(cin,customization);
	
				
				m=menu.searchItemById(id);
				
			if(m!=nullptr){
				order->addItem(m,quantity,customization);
				
			}
			else{
				cout<<"Item not found\n";
				return;
			}
						break;
					}
					
				case 2:
					{
					LoyalityProgram l1;
					double totalPrice=order->getTotalPrice();
				
					
					c->setLoyalityPoints(checkLoyalityPoints(c->getName()));
					l1.applyLoyalityPoints(c,totalPrice);
					order->discountPrice(totalPrice);
					
					 manager.updateCustomerData(c->getName(),c->getId(),c->getDietryPrefences(),c->getLoyalityPoints(),c->getContactDetails() );
					order->displayOrderDetails();
					
					
					double amount;
					payment:
					cout<<"Enter Amount: ";
					cin>>amount;
					if(amount>=totalPrice){
					    cout << "Payment successful! Change: $" << amount - totalPrice << endl;
					    c->addSpending(amount-(amount-totalPrice));
					   manager.updateCustomerData(c->getName(),c->getId(),c->getDietryPrefences(),c->getLoyalityPoints(),c->getContactDetails() );
					    cout<<"Order Confirmed\n";
					    cout<<"------------------------\n";
					    order->markAsPaid("Paid");
					    order->setOrderTime(getCurrentDateTime());
					
					    c->addOrder(order);
					    c->writeOrderHistory();
					    	is_True=false;	
					}
					
					else{
						cout << "Insufficient payment. Please pay  $" << totalPrice <<endl;
						goto payment;
					}
					
					
					
					break;
				}
						
				case 3:
				is_True=false;		
				break;
						
				default:
				 cout<<"Invalid choice\n";
				break;			
						
						
						
				}
			}
 	            	
 	            	
				 }
				
			
 }
 
 












//	  MenuItem* menuItem[] = {
//    
//        new MenuItem("Veggie Burger", "Vegetarian",25, 8.99),
//        new MenuItem("Veggie Wrap", "Vegetarian",  20, 7.49),
//        new MenuItem("Grilled Cheese Sandwich", "Vegetarian", 30, 5.99),
//        new MenuItem("Vegetable Stir Fry", "Vegetarian",  18, 9.49),
//        
//        new MenuItem("Vegan Buddha Bowl", "Vegan",  15, 10.99),
//        new MenuItem("Vegan Tacos", "Vegan",  20, 8.49),
//        new MenuItem("Vegan Quinoa Salad", "Vegan",  12, 9.29),
//        new MenuItem("Vegan Chili", "Vegan",  25, 7.99),
//        
//        new MenuItem("Gluten-Free Margherita Pizza", "Gluten-Free",  10, 11.49),
//        new MenuItem("Grilled Chicken Salad", "Gluten-Free",  18, 10.99),
//        new MenuItem("Gluten-Free Pancakes", "Gluten-Free", 15, 6.99),
//        new MenuItem("Gluten-Free Pasta Primavera", "Gluten-Free", 14, 12.49),
//        
//        new MenuItem("Classic Cheeseburger", "Specialty",  20, 9.99),
//        new MenuItem("BBQ Pulled Pork Sandwich", "Specialty",  15, 9.49),
//        new MenuItem("Chicken Caesar Wrap", "Specialty",25, 8.9),
//        new MenuItem("Grilled Salmon Plate", "Specialty", 10, 13.49),
//        
//        new MenuItem("Iced Latte", "Drinks",  30, 4.29),
//        new MenuItem("Cappuccino", "Drinks",  20, 3.49),
//        new MenuItem("Fresh Fruit Smoothie", "Drinks",25, 9.99),
//        new MenuItem("Lemonade", "Drinks",  35, 2.99),
//     
//        
//    };
//    
//    int size=sizeof(menuItem)/sizeof(menuItem[0]);




// void addItemLocally(Menu &menu,MenuItem *m[],int &size){
//   
// 	for(int i=0;i<size;i++){
// 		menu.addItem(m[i]);
// 		menu.writeMenuData(m[i]->getItemName(),m[i]->getCategory(),m[i]->getItemPrice(),m[i]->getItemStock(),m[i]->getId());
//	 }
// }

//addItemLocally(menu,menuItem,size);