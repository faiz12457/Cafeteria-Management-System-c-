#pragma once
#include<iostream>
#include "customer.h";
using namespace std;

class LoyalityProgram{
	public:
		
		void applyLoyalityPoints(Customer *c, double &totalPrice){
			 double discount=0;
			 
			 if(c->redeemLoyaltyPoints(discount)){
			 	totalPrice-=discount;
			 }
			 
			 else{
			 //s	 cout << "No loyalty points available for discount.\n";
			 }
			
		}
};