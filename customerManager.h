#pragma once
#include<iostream>
using namespace std;
#include "customer.h"
#include<fstream>
#include<sstream>
#include<string>

class CustomerManager{
	Customer *customer[1000];
	int size=sizeof(customer)/sizeof(customer[0]);
	int customerCount;
	string FN="customerData.csv";
	string temp="temp.csv";
	
	public:
		
		CustomerManager(){
			customerCount=0;
		}
		
		~CustomerManager(){
			for(int i=0;i<size;i++){
				delete customer[i];
			}
		}
		
		string registerCustomer(string name,string dietryPrefences,string contactDetails,string id){
			
			if(customerCount<1000){
				customer[customerCount]=new Customer(name,dietryPrefences,contactDetails,id);
				customerCount++;
				cout << "Customer registered successfully with ID: " << customer[customerCount-1]->getId() << "\n";
				writeCustomerData(name,dietryPrefences,contactDetails,customer[customerCount-1]->getLoyalityPoints(),customer[customerCount-1]->getId());
				return customer[customerCount-1]->getId();
			}
			else{
			cout << "Registration failed. Customer limit reached.\n";
       				 return 0;
			}
			
		}
		
		
		
		
		
			string registerCustomer(string name,string dietryPrefences,string contactDetails,string id,int points){
			
			if(customerCount<1000){
				customer[customerCount]=new Customer(name,dietryPrefences,contactDetails,id,points);
				customerCount++;
				
				writeCustomerData(name,dietryPrefences,contactDetails,customer[customerCount-1]->getLoyalityPoints(),customer[customerCount-1]->getId());
				return customer[customerCount-1]->getId();
			}
			else{
	
       				 return 0;
			}
			
		}
		
		
		
		
	
		
		Customer* findCustomer(string id) {
        	for (int i = 0; i < customerCount; ++i) {
        		
           		if (customer[i]->getId() == id) {
                    return customer[i];
            }
        }
        return nullptr;
    }
    
    
    Customer* findCustomerByName(string name) {
        	for (int i = 0; i < customerCount; ++i) {
        		
           		if (customer[i]->getName() == name) {
                    return customer[i];
            }
        }
        return nullptr;
    }
    
    
    
    
    
    bool deleteCustomer(string name,string id){
    	 deleteCustomerData(name,id);
    	for(int i=0;i<customerCount;i++){
    		if(customer[i]->getName()==name && customer[i]->getId()==id){
    			
    			delete customer[i];
    			
    			for(int j=i;j<customerCount;j++){
    				customer[j]=customer[j+1];
				}
				
				customer[customerCount-1]=nullptr;
				customerCount--;
				
				cout<<"\n---------------------------------------------------------------\n\n";
				 cout << "Customer: "<<name<<" with Id: "<<id << " has been successfully deleted.\n";
				 	cout<<"\n---------------------------------------------------------------\n";
        		    return true;
				
				
			}
			
			
		}
		
		cout<<"\n---------------------------------------------------------------\n\n";
				cout << "Customer: " << name<<" with Id: "<<id << " not found in the menu.\n";
					cout<<"\n---------------------------------------------------------------\n";
				return false;
    	
	}
		
		
		bool modifyCustomerDetails(string id){
			Customer *customer=findCustomer(id);
			if(customer!=nullptr){
			int choice;
			cout<<"--------------------------------------------------------------------------\n";
            cout << "Customer found. What do you want to modify?\n";
            cout << "1. Name\n2. Dietry Prefences\n3. Contact details\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();
            

            switch (choice) {
                case 1: {
                	
                    string newName;
                    cout << "Enter new name: ";
                    getline(cin,newName);
                    customer->setName(newName);
                    updateCustomerData(newName,customer->getId(),customer->getDietryPrefences(),customer->getLoyalityPoints(),customer->getContactDetails()); 
                    break;
                }
                case 2: {
                    string dietryPrefences;
                    cout << "Enter new DietryPrefences: ";
                    getline(cin,dietryPrefences);
                    customer->setDietryPrefences(dietryPrefences);
                     updateCustomerData(customer->getName(),customer->getId(),dietryPrefences,customer->getLoyalityPoints(),customer->getContactDetails());
                    break;
                }
                case 3: {
                    string details;
                    cout << "Enter new Contact Details: ";
                    getline(cin,details);
                    customer->setContactDetails(details);
                    updateCustomerData(customer->getName(),customer->getId(),customer->getDietryPrefences(),customer->getLoyalityPoints(),details);
                    break;
                }

                default:
                	
                    cout << "Invalid choice.\n";
                    return false;
                    break;
            
            
           
        }
         cout << "Customer  modified successfully.\n";
         cout<<"---------------------------------------------------------------------------\n";
            return true;
    
    
			}
			
			 cout << "Customer not found.\n";
			   cout<<"---------------------------------------------------------------------------\n";
    return false; 
			
		}
		
		
		
		
		
		
		    
    
    
    void getAllCustomerDetails(){
    	  cout << "---------------------------------Customer List:----------------------------------\n\n";
    	for(int i=0;i<customerCount;i++){
    		customer[i]->displayCustomerDetails();
    		cout<<"-----------------------------------------------------------------------------------\n";
		}
	}
	
	
	
	
//	  void getAllCustomerHistory(){
//    	  cout << "---------------------------------Customers History:----------------------------------\n\n";
//    	for(int i=0;i<customerCount;i++){
//    		customer[i]->displayOrderHistory();
//    		cout<<"-----------------------------------------------------------------------------------\n";
//		}
//	}
//	
	////////////////////////////////////////////// File Handling ////////////////////////////////////////////////////////////////////////////////
	
	bool checkCustomerDataExistById(string prevId){
	
	
	ifstream checkData(FN);
	
	if(!checkData.is_open()){
		return false;
	}
	string line,name,contactDetails,dietryPrefences,id,loyalityPoints;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,dietryPrefences,',');
	     getline(ss,contactDetails,',');
	     getline(ss,loyalityPoints,',');
	     getline(ss,id,',');
	     
	     if(id==prevId ){
	     	return true;
		 }
		 
	}
	
	checkData.close();
	return false;
	
}





	bool checkCustomerDataExist(string prevId,string prevName){
	
	
	ifstream checkData(FN);
	
	if(!checkData.is_open()){
		return false;
	}
	string line,name,contactDetails,dietryPrefences,id,loyalityPoints;
	while(getline(checkData,line)){
	
	     stringstream ss(line);
	     
	     getline(ss,name,',');
	     getline(ss,dietryPrefences,',');
	     getline(ss,contactDetails,',');
	     getline(ss,loyalityPoints,',');
	     getline(ss,id,',');
	     
	     if(id==prevId && name==prevName ){
	     	return true;
		 }
		 
	}
	
	checkData.close();
	return false;
	
}


void writeCustomerData(string name,string dietryPrefences,string contact,int loyalityPoints,string id){
	
	if(checkCustomerDataExist(id,name)){
		return;
	}
	ofstream writeData(FN,ios::app);
	if(!writeData.is_open()){
		return ;
	}
	
	writeData<<name<<","<<dietryPrefences<<","<<contact<<","<<loyalityPoints<<","<<id<<endl;
	writeData.close();
	
	
	
}

void deleteCustomerData(string Name,string Id){
	ifstream read(FN);
	ofstream write(temp,ios::app);
	string line;
	string name;
	string dietryPrefences;
	string contact;
	string loyalityPoints, id;
	bool flag=false;
	
	
	if(!write.is_open()){
		return;
	}
	
	while(getline(read,line)){
		stringstream ss(line);
		
		getline(ss,name,',');
	    getline(ss,dietryPrefences,',');
	    getline(ss,contact,',');
	    getline(ss,loyalityPoints,',');
	    getline(ss,id,',');
	    
	    if(name==Name && id==Id){
	    	flag=true;
		}
		else{
		
	      	write<<name<<","<<dietryPrefences<<","<<contact<<","<<loyalityPoints<<","<<id<<endl;
				
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

void updateCustomerData(string Name,string Id,string newDietryPrefences, int newLoyalityPoints,string newContact ){
	ifstream read(FN);
	ofstream write(temp,ios::app);
	string line;
	string name;
	string dietryPrefences;
	string contact;
	string loyalityPoints, id;
	bool flag=false;
	
	
	if(!write.is_open()){
		return;
	}
	
	while(getline(read,line)){
		stringstream ss(line);
		
		getline(ss,name,',');
	    getline(ss,dietryPrefences,',');
	    getline(ss,contact,',');
	    getline(ss,loyalityPoints,',');
	    getline(ss,id,',');
	    
	    if(name==Name && id==Id){
	    	write<<Name<<","<<newDietryPrefences<<","<<newContact<<","<<newLoyalityPoints<<","<<Id<<endl;
	    	
	    	flag=true;
		}
		else{
			
			write<<name<<","<<dietryPrefences<<","<<contact<<","<<loyalityPoints<<","<<id<<endl;
	      			
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