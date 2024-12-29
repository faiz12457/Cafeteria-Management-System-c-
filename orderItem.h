#pragma once
#include <iostream>
#include "menuItem.h"
using namespace std;


class OrderItem:public MenuItem{
	private:

    int quantity;
    string customizations;
    
    public:
    	OrderItem(){
    		
    		quantity=0;
    		customizations="";
		}
		
		OrderItem(string name,double price,int quantity,string custom=""){
			 setItemName(name);
			setItemPrice(price);
			this->quantity=quantity;
			customizations=custom;
		}
		

        
		int getTotalPrice(){
			return (getItemPrice()*quantity);
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
			cout <<"-"<<getItemName() <<" x "<<getQuantity()<<", Customizations:"<<(customizations.empty()? "None":customizations)<<"= $"<<getTotalPrice()<<endl;
			
		}
		
		
		
		
		
		
		
};