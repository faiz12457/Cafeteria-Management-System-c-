#pragma once
#include<iostream>
#include "user.h"
#include "order.h"
#include<fstream>
#include<sstream>
#include "orderItem.h"
using namespace std;



class Customer:public User{
	
	private:
		int loyalityPoints;
		string dietryPrefences;
		Order *orderHistory[1];
		double totalSpent;
	
		
		public:
		
		Customer(){
			loyalityPoints=0;
			dietryPrefences="";
			totalSpent=0.0;
		}
		
		~Customer(){
	
				delete orderHistory[0];
			
		}
		
		
		
		Customer(string name,string dietryprefences,string contact,string id){
			setName(name);
			setId(id);
			this->dietryPrefences=dietryprefences;
			setContactDetails(contact);
			totalSpent=0.0;
			loyalityPoints=0;
		}
		
		
			
		Customer(string name,string dietryprefences,string contact,string id,int points){
			setName(name);
			setId(id);
			this->dietryPrefences=dietryprefences;
			setContactDetails(contact);
			totalSpent=0.0;
			loyalityPoints=points;
		}
		
		
		
		
	
		
		void addOrder(Order *order){
				orderHistory[0]=order;
		}
		
		
			void addSpending(double amount){
				if(amount>=0){
				totalSpent+=amount;
			calculateLoyalityPoints( amount);
				}
			}
			
				

		
		
		  bool redeemLoyaltyPoints(double& discount) {
           if (loyalityPoints > 0) {
        	
            discount = loyalityPoints; 
          loyalityPoints = 0; 
            return true;
        }
        return false; 
    }
		

		
		
		void setDietryPrefences(string d){
			dietryPrefences=d;
		}
		
		string getDietryPrefences(){
			return dietryPrefences;
		}
		
		string role(){
			return "Customer";
		}
		
		void  calculateLoyalityPoints(int amount){
			
			loyalityPoints+=(amount/50);
			
		}
		
		void setLoyalityPoints(int points){
			loyalityPoints=points;
		}
		
		int getLoyalityPoints(){
			return loyalityPoints;
		}
		
		
		
		void displayCustomerDetails(){
		
			  cout << "Customer ID: " << getId() << "\n"
             << "Name: " << getName() << "\n"
             << "Contact: " << getContactDetails() << "\n"
             << "Dietary Preferences: " <<getDietryPrefences() << "\n"
             << "Total Spent: $" << totalSpent << "\n"
             << "Loyalty Points: " << getLoyalityPoints() << "\n\n";
        
		}
		

		
		
		////////////////////////////////////////// FilE Handling for order history /////////////////
		
		
		
		
		
		
		void writeOrderHistory() {
    string filename = "orderHistory.csv";
    ofstream write(filename, ios::app); 

    if (!write.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

   
        string customerId = getId();
        string orderDetails = ""; 
        
       

        for (int j = 0; j < orderHistory[0]->getItemCount(); j++) {
            OrderItem* item = orderHistory[0]->getOrderItem(j); 
    
            orderDetails += ","+item->getName() + " x " + to_string(item->getQuantity()) + " ($" + to_string(item->getTotalPrice()) + ")";
        }

        write << customerId<< orderDetails << "," <<orderHistory[0]->getTotalPrice()<<","<<orderHistory[0]->getOrderTime();
  
  

    write.close();
  
}

	
		
		
		
		
		
		
		
		
	
};

