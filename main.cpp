#include<iostream>
using namespace std;
#include"menu.h"
#include "order.h"
#include "customerManager.h"
#include "customer.h"
#include "orderItem.h"
#include "menuItem.h"
#include "loyalityProgram.h"
#include "functions.h"
#include<string>

void readMenuData(Menu &menu){
	string FN="menuItem.csv";
	
	int size=0;
	ifstream checkData(FN);
	
	if(!checkData.is_open()){
		cout<<"Error\n";
	}
	
	string line,name,category,price,stock,id;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,category,',');
	     getline(ss,price,',');
	     getline(ss,stock,',');
	     getline(ss,id,',');
	     
	     MenuItem *m=new MenuItem(name,category,stoi(stock),stod(price),stoi(id));
	     menu.addCategory(category);
	     menu.addItem(m);
	}
	
	checkData.close();
	
}


void readCustomerData(CustomerManager &Manager){
	string FN="customerData.csv";
		ifstream checkData(FN);
	
	if(!checkData.is_open()){
		return;
	}
	string line,name,contactDetails,dietryPrefences,id,loyalityPoints;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,dietryPrefences,',');
	     getline(ss,contactDetails,',');
	     getline(ss,loyalityPoints,',');
	     getline(ss,id,',');
	     
	  Manager.registerCustomer(name,dietryPrefences,contactDetails,id,stoi(loyalityPoints));
	     
		 
	}
	
	checkData.close();
}

 

 

int main() {
	
	 Menu menu;
	 CustomerManager Manager;
	 Order order;
	 
	 readMenuData(menu); // extract menu item to menu for display
	 readCustomerData(Manager); // extract data from customer file
	 
	 int choice;
	 bool isTrue=true;
	 while(isTrue){
	 	
	 	cout<<"Enter 1 for add item to the menu\n";
	 	cout<<"Enter 2 for Modify item from the menu\n";
	 	cout<<"Enter 3 for display  menu\n";
	 	cout<<"Enter 4 for delete an item from menu\n";
	 	cout<<"Enter 5 for Register Customer\n";
	 	cout<<"Enter 6 for Modify Customer details\n";
	 	cout<<"Enter 7 for delete a Customer\n";
	 	cout<<"Enter 8 for display all Customer data\n";
	 	cout<<"Enter 9 to order food\n";
	 	cout<<"Enter 10 to display order history of Customer\n";
	 	cout<<"Enter 11 to exit\n";
	 	cin>>choice;
	 	cin.ignore();
	 	switch(choice){
	 		case 1:{
	 			userInputAddItem(menu);
				break;
			 }
	 			
	 		case 2:{
	 			
				string name;
	 			cout<<"Enter name of the Item to modify: ";
	 			getline(cin,name);
	 			
			 	menu.modify_item_by_name(name);
			 	
	 	    break;
			 }
	 			
	 	     
			case 3:
				 menu.displayMenu();
				 break;
				 
			case 4:{
				string name;
				int id;
				cout<<"Enter name of the item: ";
				getline(cin,name);
				cout<<"Enter id of the item: ";
				cin>>id;
			menu.removeItem(name,id);
			menu.deleteMenuData(name,id);
				break;
			}
			
			case 5:{
				registerCustomer(Manager);
				break;
			}
			
			case 6:{
				string id;
				cout<<"Enter Id of Customer to Modify Details: ";
				cin>>id;
				Manager.modifyCustomerDetails(id);
				break;
			}
			
			case 7:{
				string name;
				string id;
				cout<<"Enter name of the customer: ";
				getline(cin,name);
				
				cout<<"Enter id of the customer: ";
				cin>>id;
				cin.ignore();
				Manager.deleteCustomer(name,id);
				break;
			}
			
			case 8:{
				Manager.getAllCustomerDetails();
				break;
			}
			
			case 9:{
		
			orderItem(menu,Manager);
				break;
			}
			
			
			case 10:{
				Customer *c;
				
				string id;
				cout<<"Enter customer id for history: ";
				cin>>id;
				c=Manager.findCustomer(id);
				if(c!=nullptr){
					//c->displayOrderHistory();
				}
				else{
					cout<<"Invalid id!\n";
				}
				
				
			//	Manager->getAllCustomerHistory();
				break;
			}
				 
			case 11:
				cout << "Exiting program. Goodbye!\n";
				isTrue=false;
				break;
				
				
				 
			default:
			
			cout<<"Enter valid choice\n";
			break;	       
	 			
		 }
	 	  
          
	 }
         
  

}
	

