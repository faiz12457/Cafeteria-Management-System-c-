#pragma once
#include <iostream>
using namespace std;
#include "inventory.h"
#include<fstream>
#include<sstream>
#include<string>
class InventoryManager{
	
	Inventory *inventory[100];
	int inventoryCount;
	string FN="inventory.csv";
	string temp="temp.csv";
	public:
		InventoryManager(){
			Inventory *inventory[50];
			inventoryCount=0;
			
		}
		
		void addInventoryitem(Inventory *item){
			if(inventoryCount<100){
				inventory[inventoryCount++]=item;
			}
			
			else{
				cout<<"Limit exceed\n";
			}
		}
		
		Inventory* findInventoryItem(string name){
			for(int i=0;i<inventoryCount;i++){
				if(inventory[i]->getItemName()==name){
				 return	inventory[i];
				}
			}
			
			return nullptr;
		}
		
		void ModifyItem(string name,int stock){


		
			Inventory *n=findInventoryItem(name);
			
			if(n!=nullptr){
					n->setItemStock(stock);
					modifyStock(name,stock);
				
			} 
			
			else{
				cout<<"Item not found\n";
			}
		}
		
		
		
		void deleteInventoryItem(string name){
			for(int i=0;i<inventoryCount;i++){
				
				if(inventory[i]->getItemName()==name){
					deleteStock(name);
					delete inventory[i];
				
					for(int j=i;j<inventoryCount-1;j++){
						inventory[j]=inventory[j+1];
						
					}
					
					inventory[inventoryCount-1]=nullptr;
					inventoryCount--;
					
				}
				
				
			}
			
		}
		
		
		
		///////////////////////////////////////////////////// File handling ////////////////////////////////////////////////////////////////////////
		bool checkDataExist(string Name){
			ifstream read(FN);
			
			string line,name,stock;
			
			if(!read.is_open()){
				cout<<"Error\n";
				return false ;
			}
			
			while(getline(read,line)){
				stringstream ss(line);
				
				getline(ss,name,',');
				getline(ss,stock,',');
				
				if(name==Name){
					return true;
					break;
				}
				
				
			}
			
			read.close();
			
			return false;
		}
		
		
		void writeData(string name,int stock){
			
			ofstream write(FN,ios::app);
			
			
			if(!write.is_open()){
				return;
			}
			
			if(checkDataExist(name)){
				return;
			}
			
			write<<name<<","<<stock<<endl;
			
			
		}
		
		void modifyStock(string name ,int stock){
			  ifstream read(FN);
			  ofstream write (temp,ios::app);
			  bool flag=false;
			  
			  string line,newName,newStock;
			  if(!write.is_open()){
			  	cout<<"Error\n";
			  	return ;
			  }
			  
			  
			 while(getline(read,line)){
			 	stringstream ss(line);
			 	getline(ss,newName,',');
			 	getline(ss,newStock,',');
			 	
			 	if(name==newName){
			 		write<<name<<","<<stock<<endl;
			 		flag=true;
				 }
				 
				 else{
				 	
				 		write<<newName<<","<<newStock<<endl;
				 }
			 }
			 
			 write.close();
			 read.close();
			 
			 if(flag){
			 	remove(FN.c_str());
			 	rename(temp.c_str(),FN.c_str());
			 } 
			 else{
			 	
			 	remove(temp.c_str());
			 }
			  
		}
		
				void deleteStock(string name){
			  ifstream read(FN);
			  ofstream write (temp,ios::app);
			  bool flag=false;
			  
			  string line,newName,newStock;
			  if(!write.is_open()){
			  	cout<<"Error\n";
			  	return ;
			  }
			  
			  
			 while(getline(read,line)){
			 	stringstream ss(line);
			 	getline(ss,newName,',');
			 	getline(ss,newStock,',');
			 	
			 	if(name==newName){
			 		flag=true;
				 }
				 
				 else{
				 	
				 		write<<newName<<","<<newStock<<endl;
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