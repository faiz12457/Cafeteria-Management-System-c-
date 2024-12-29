#pragma once
#include <iostream>
#include "orderItem.h"
#include "menuItem.h"
using namespace std;

class Order {

	private:
		
		OrderItem *orderItem[20];
		int size=sizeof(orderItem)/sizeof(orderItem[0]);
		int itemCount;
		double totalPrice;
		int orderId;
		string paymentStatus;
		string time;
	
	
	public:
		
		
		
		Order(){
			itemCount=0;
			totalPrice=0.0;
			
	
			
		}
		~Order(){
			for(int i=0;i<size;i++){
				delete orderItem[i];
			}
		}
	
		
	OrderItem* getOrderItem(int index) {
    if (index >= 0 && index < itemCount) {
        return orderItem[index];
    }
    else{
    	return nullptr;
	}
     
    }
    
    int getItemCount() {
    return itemCount;
}


     void setOrderTime(string t){
     	time=t;
	 }
	 
	 string getOrderTime(){
	 	return time;
	 }









		bool addItem(MenuItem *item,int qty,string custom=""){
			if(itemCount<20){
				orderItem[itemCount]=new OrderItem(item->getItemName(),item->getItemPrice(),qty,custom);
				itemCount++;
				updateTotalPrice();
				return true;
			}
			
			
			cout<<"Order is full cannot add more items\n";
			return false;
		}
		
		void updateTotalPrice(){
			totalPrice=0;
			for (int i=0;i<itemCount;i++){
				totalPrice+=orderItem[i]->getTotalPrice();
			}
		}
		
		
	
    void markAsPaid(const string& status) {
        if (status == "Paid" || status == "Unpaid") {
            paymentStatus = status;
        } else {
           cout << "Invalid payment status. Use 'Paid' or 'Unpaid'.\n";
        }
    }

    string getPaymentStatus()  {
       return paymentStatus;
   
   }
   
   void discountPrice(double price){
   	totalPrice=price;
   }
   
   double getTotalPrice(){
   	return totalPrice;
   }
   
   void displayOrderDetails(){
   	
   	cout<<"--- Recipt---\n\n";
   	for(int i=0;i<itemCount;i++){
   		
   		orderItem[i]->displayOrderItem();
   		
	   }
	   
	   
	   cout<<"- Total Price : $"<<getTotalPrice()<<endl<<endl;
	cout<<"-----------\n\n";
	   

   }
   
   
   
   


        
};


