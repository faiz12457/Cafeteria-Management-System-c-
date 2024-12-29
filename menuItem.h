#pragma once
#include<iostream>
using namespace std;


class MenuItem{
	private:
		
		int id;
		int sales;
		string itemName;
		double price;
		int itemStock;
		string category;
		
		public:
			
			MenuItem(){
				itemName="";
				price=0.0;
				itemStock=0;
				id=0;
				sales=0;
			}
			
			MenuItem(string name,string category,int stock,double price,int id){
				itemName=name;
				this->price=price;
				itemStock=stock;
				this->category=category;
				this->id=id;
			//	id=itemId++;
		}
			
			void increment_sales(int quantity){
				sales+=quantity;
			}
			
			int getSalesData(){
				return sales;
			}
			 
			
			  
			void setCategory(string c){
				category=c;
			}
			
			string getCategory(){
				return category;
			}
			
			void setItemName(string n){
				itemName=n;
			}
			
			string getItemName(){
			return itemName;
			}
			
			void setItemPrice(double p){
				price=p;
			}
			
			double getItemPrice(){
				return price;
			}
			
			void setItemStock(int s){
				itemStock=s;
			}
			
			
			int getItemStock(){
				return itemStock;
			}
			
			bool isAvailable(){
				if(itemStock>0){
					return true;
				}
				
				return false;
			}
			
			int  getId(){
				return id;
			}
			
			void setId(int id){
				this->id=id;
			}
			
			
			void display(){
				cout<<getId()<<". "<<getItemName()<<"-$"<<getItemPrice()<<"(Available:"<<getItemStock()<<")"<<endl;
			}
			
			
					
};

