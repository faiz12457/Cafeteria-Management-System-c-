#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
#include "menuitem.h"
#include "inventoryManager.h"



class Menu{
	private:
		MenuItem *items[100];
		int size=sizeof(items)/sizeof(items[0]);
		int itemCount;
		string category[40]={};
	
		int currCateogrySize=5;
		string FN="menuItem.csv";
		string temp="tempMenuItem.csv";
		
		
		public:
			Menu(){
				itemCount=0;
			}
			~Menu() {
   					 for (int i = 0; i <size; ++i) {
        				delete items[i];
    										
											}
					}
				
				
				void addCategory( string& newCategory) {
        for (int i = 0; i < currCateogrySize; i++) {
            if (category[i] == newCategory) {
               // cout << "Category already exists: " << newCategory << endl;
                return;
            }
        }

        
        if (currCateogrySize < 40) {
            category[currCateogrySize++] = newCategory;
           // cout << "Category added: " << newCategory << endl;
        } else {
          //  cout << "Category limit reached. Cannot add more categories." << endl;
        }
    }
					
				
					

			
			void addItem(MenuItem *item){
				if(itemCount<50){
				items[itemCount]=item;
				itemCount++;
				}
				
				else{
					cout<<"Menu is full cannot add more items\n";
				}
			
			}
			
			MenuItem* searchItem(string name){
				for (int i=0;i<itemCount;i++ ){
					if(items[i]->getItemName()==name){
						return items[i];
					}
				}
				
				return nullptr;
				
			}
			
			
			
			MenuItem* searchItemById(int id){
				for (int i=0;i<itemCount;i++ ){
					if(items[i]->getId()==id){
						return items[i];
					}
				}
				
				return nullptr;
				
			}
			
			
			bool removeItem(string name,int id){
				for(int i=0;i<itemCount;i++){
					if(items[i]->getItemName()==name && items[i]->getId()){
						
						   delete items[i];
						   
						   
						   
				for(int j=i;j<itemCount-1;j++){
					items[j]=items[j+1];
				}
				
				items[itemCount-1]=nullptr;
				itemCount--;
				cout<<"\n---------------------------------------------------------------\n\n";
				 cout << "Item: "<<name<<" Id: "<<id << " has been successfully deleted.\n";
				 	cout<<"\n---------------------------------------------------------------\n";
        		    return true;
		
						   
					}
					
				}
				cout<<"\n---------------------------------------------------------------\n\n";
				cout << "Item '" << name<<" Id: "<<id << " not found in the menu.\n";
					cout<<"\n---------------------------------------------------------------\n";
				return false;
				
			}
			

					
		
		void displayMenu() {
    cout << "\n---------------------------------------CampusBites Cafeteria Menu---------------------------------------------\n\n";
    
    for (int a = 0; a < currCateogrySize; a++) {
        bool hasItems = false;
        
        
        for (int i = 0; i < itemCount; i++) {
            if (category[a] == items[i]->getCategory()) {
                hasItems = true;
                break; 
            }
        }
        
    
        if (hasItems) {
            cout << category[a] << ":\n";
            for (int i = 0; i < itemCount; i++) {
                if (category[a] == items[i]->getCategory()) {
                    items[i]->display();
                }
            }
            cout << endl;
        }
    }
    
    cout << "\n---------------------------------------CampusBites Cafeteria Menu---------------------------------------------\n\n";
}
	
			
						
		
			
			
		
			bool modify_item_by_name(string& name,InventoryManager &inventoryManager) {
                 MenuItem *singleItem=searchItem(name);
                
				 if (singleItem!=nullptr) {
				 	
            int choice;
            cout << "Item found. What do you want to modify?\n";
            cout << "1. Name\n2. Category\n3. Price\n4. Stock\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();
            

            switch (choice) {
                case 1: {
                	
                    string newName;
                    cout << "Enter new name: ";
                    getline(cin,newName);
                    singleItem->setItemName(newName);
                    UpdateMenuData(newName,singleItem->getId(),singleItem->getCategory(),singleItem->getItemStock(),singleItem->getItemPrice());
                    break;
                }
                case 2: {
                    string category;
                    cout << "Enter new Category: ";
                    getline(cin,category);
                    singleItem->setCategory(category);
                    UpdateMenuData(singleItem->getItemName(),singleItem->getId(),category,singleItem->getItemStock(),singleItem->getItemPrice());
                    addCategory(category);
                    break;
                }
                case 3: {
                    double newPrice;
                    cout << "Enter new price: ";
                    cin >> newPrice;
                    singleItem->setItemPrice(newPrice);
                    UpdateMenuData(singleItem->getItemName(),singleItem->getId(),singleItem->getCategory(),singleItem->getItemStock(),newPrice);
                    break;
                }
                
                case 4:{
                	int stock;
                	cout<<"Enter new Stock: ";
                	cin>>stock;
                	
                	singleItem->setItemStock(stock);
                	UpdateMenuData(singleItem->getItemName(),singleItem->getId(),singleItem->getCategory(),stock,singleItem->getItemPrice());
                	inventoryManager.ModifyItem(singleItem->getItemName(),stock);
					break;
				}
//                case 4: {
//                    bool newAvailability;
//                    std::cout << "Enter availability (1 for available, 0 for unavailable): ";
//                    std::cin >> new_availability;
//                    items[i].set_availability(new_availability);
//                    break;
//                }
                default:
                	
                    cout << "Invalid choice.\n";
                    return false;
            }
            
            cout << "Item modified successfully.\n";
            return true;
        }
    
     cout << "Item not found.\n";
    return false; 
}


bool trackSalesData(string name,int quantity){
	MenuItem *item=searchItem(name);
	
	if(item!=nullptr){
		item->increment_sales(quantity);
		return true;
	}
	
	return false;
	
}


    void displaySalesData(string name){
    	MenuItem *item=searchItem(name);
    	if(item!=nullptr){
    		cout<<item->getItemName()<<" Category: "<<item->getCategory()<<" Sales: "<<item->getSalesData()<<endl;
		}
	}

///////////////////////////////////////////////////// File Handling /////////////////////////////////////////////////////////////////////////

bool checkDataExistById(int prevId){
	
	
	ifstream checkData(FN);
	
	if(!checkData.is_open()){
		return false;
	}
	string line,name,category,price,stock,id;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,category,',');
	     getline(ss,price,',');
	     getline(ss,stock,',');
	     getline(ss,id,',');
	     
	     if(id==to_string(prevId) ){
	     	return true;
		 }
		 
	}
	
	checkData.close();
	return false;
	
}
bool checkDataExist(string prevName,int prevId){
	
	
	ifstream checkData(FN);
	
	if(!checkData.is_open()){
		return false;
	}
	string line,name,category,price,stock,id;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,category,',');
	     getline(ss,price,',');
	     getline(ss,stock,',');
	     getline(ss,id,',');
	     
	     if(name==prevName && id==to_string(prevId) ){
	     	return true;
		 }
		 
	}
	
	checkData.close();
	return false;
	
}

void writeMenuData(string name,string category,double price,int stock,int id){
	
	if(checkDataExist(name,id)){
		return;
	}
	ofstream writeData(FN,ios::app);
	if(!writeData.is_open()){
		return ;
	}
	
	writeData<<name<<","<<category<<","<<price<<","<<stock<<","<<id<<endl;
	writeData.close();
	
	
	
}

void deleteMenuData(string Name,int Id){
	ifstream read(FN);
	ofstream write(temp,ios::app);
	string line,name,category,price,id,stock;
	bool flag=false;
	
	
	if(!write.is_open()){
		return;
	}
	
	while(getline(read,line)){
		stringstream ss(line);
		
		getline(ss,name,',');
	    getline(ss,category,',');
	    getline(ss,price,',');
	    getline(ss,stock,',');
	    getline(ss,id,',');
	    
	    if(name==Name and id==to_string(Id)){
	    	flag=true;
		}
		else{
		
				write<<name<<","<<category<<","<<price<<","<<stock<<","<<id<<endl;
				
		}
		
	}
	read.close();
	write.close();
	
	if(flag){
			remove(FN.c_str());
			rename(temp.c_str(),FN.c_str());
		
		
	}
	else{
		remove(temp.c_str());
	}
}




void UpdateMenuData(string Name,int Id,string newCategory,int newstock,double newPrice){
	ifstream read(FN);
	ofstream write(temp,ios::app);
	string line,name,category,price,id,stock;
	bool flag=false;
	
	
	if(!write.is_open()){
		return;
	}
	
	while(getline(read,line)){
		stringstream ss(line);
		
		getline(ss,name,',');
	    getline(ss,category,',');
	    getline(ss,price,',');
	    getline(ss,stock,',');
	    getline(ss,id,',');
	    
	    if(name==Name){
	    	write<<Name<<","<<newCategory<<","<<newPrice<<","<<newstock<<","<<Id<<endl;
	    	flag=true;
		}
		else{
		
				write<<name<<","<<category<<","<<price<<","<<stock<<","<<id<<endl;
				
		}
		
	}
	read.close();
	write.close();
	
	if(flag){
			remove(FN.c_str());
			rename(temp.c_str(),FN.c_str());
		
		
	}
	else{
		remove(temp.c_str());
	}
}




};
