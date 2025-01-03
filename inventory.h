#pragma once

#include<iostream>
#include "menuItem.h"
using namespace std;

class Inventory:public MenuItem{
	
	public:
		
		Inventory(){
		}
		Inventory(string name,int stock){
			setItemName(name);
			setItemStock(stock);
		}
		
		
		
		void reduceStock(int quantity) {
			
			int stock=getItemStock()-quantity;
			setItemStock(stock);
    }
    
    
    bool isLowStock() {
      return  getItemStock()<=5 ? true :false;

    }
    
};