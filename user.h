#pragma once
#include<iostream>
using namespace std;

class User{
	private:
		string name;
		string id;
	    string contactDetails;
		
		
		public:
			
			User(){
				name="";
				id="";
			 contactDetails="";
			}
			
			void setContactDetails(string c){
				contactDetails=c;
			}
			
			string getContactDetails(){
				return contactDetails;
			}
			
			void setName(string n){
				name=n;
			}
			
			string getName(){
				return name;
			}
			
			void setId(string id){
				this->id=id;
			}
			
			string getId(){
				return id;
			}
			
		virtual	string role()=0;
};


