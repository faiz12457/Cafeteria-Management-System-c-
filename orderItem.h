#pragma once
#include <iostream>
using namespace std;


class OrderItem{
	private:
	string itemName;
    double price;
    int quantity;
    string customizations;
    
    public:
    	OrderItem(){
    		itemName="";
    		price=0.0;
    		quantity=0;
    		customizations="";
		}
		
		OrderItem(string name,double price,int quantity,string custom=""){
			itemName=name;
			this->price=price;
			this->quantity=quantity;
			customizations=custom;
		}
		
		void setName(string name){
			itemName=name;
		}
		
		string getName(){
			return itemName;
		}
		
		void setPrice(double p){
			price=p;
		}
        
		int getTotalPrice(){
			return (price*quantity);
		}		
		
		void setQuantity(int q){
			quantity=q;
		}
		
		int getQuantity(){
			return quantity;
		}
		
		void setCustomizations(string c){
			customizations=c;
		}
		
		string getCustomizations(){
			return customizations;
		}
		
		
		void displayOrderItem(){
			cout <<"-"<<getName() <<" x "<<getQuantity()<<", Customizations:"<<(customizations.empty()? "None":customizations)<<"= $"<<getTotalPrice()<<endl;
			
		}
		
		
		
		
		
		
		
};