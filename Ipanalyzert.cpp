/*
 *      Author: kompalli
 */
#include "IPAddressAnalyze.h"
#include <iostream>
#include <cstring>
using namespace std;


		Node *IPAddressAnalyzer::SetIp(Node *entry, Node *temp)
		{
			
			if(temp==NULL)
				temp=entry;
				
			else
			{
				temp->link = SetIp(entry,temp->link);

			}
			return temp;
		}		

		Node *IPAddressAnalyzer::GetIp(){
			return List->link;
		}

		void IPAddressAnalyzer::updateIp(Node::Item& oldIPdata,Node::Item& newIpdata) {
			int pos = 0;
   
  			if(List==NULL) {
      			printf("Linked List not initialized");
      			return;
 		  	} 

   			Node *current = List;
  			while(current->link!=NULL) {
				if(current->data.octet1 == oldIPdata.octet1) {
					current->data.num_requests = newIpdata.num_requests + current->data.num_requests;
					
					return;
				}
      
				current = current->link;
				pos++;
			}
		}


		void IPAddressAnalyzer::insertIp(ip_format entry) {
            
			Node *insert_ptr;
            insert_ptr = new Node;
            insert_ptr->data = entry;
            insert_ptr->link = NULL;
			
			Node *temp = List;
			Node *search_result=IPAddressAnalyzer::searchIp(List,entry);
			if (search_result==NULL){
            List=SetIp(insert_ptr,temp);
			}
			else{
				IPAddressAnalyzer::updateIp(search_result->data,entry);
			}
        }
		int IPAddressAnalyzer::getListSize(Node *node)
		{
			if(node == NULL)
				return 0;
			int listSize = 1;
			listSize += getListSize(node->link); 
			return listSize;
		}

		Node *IPAddressAnalyzer::sortIp(Node *Data){
			//Node current will point to head  of the list
        Node *current = Data, *index = NULL;  
        Node::Item temp;  
          
        if(Data == NULL) {  
            return NULL;  
        }  
        else {  
            while(current != NULL) {  
                //Node index will point to node next to current  
                index = current->link;  
                  
                while(index != NULL) {  
                    //If current node's data is greater than index's node data, swap the data between them  
                    if(current->data.num_requests <= index->data.num_requests) {  
						temp = current->data;  
						current->data = index->data;  
						index->data = temp;
					}
                    index = index->link;  
                }  
                current = current->link;  
            }   
			Node *Sorted = Data;
			while(Sorted != NULL) {  
                //Node index will point to node next to Sorted  
                index = Sorted->link;  
                  
                while(index != NULL) {  
                    //If Sorted node's data is greater than index's node data, swap the data between them  
                    if(
						Sorted->data.num_requests == index->data.num_requests && 
						Sorted->data.octet1 >= index->data.octet1
					) {  
						temp = Sorted->data;  
						Sorted->data = index->data;  
						index->data = temp;
					} else if(
						Sorted->data.num_requests == index->data.num_requests && 
						Sorted->data.octet1 >= index->data.octet1 && 
						Sorted->data.octet2>= index->data.octet2
					) {  
						temp = Sorted->data;  
						Sorted->data = index->data;  
						index->data = temp;
					}   else if(
						Sorted->data.num_requests == index->data.num_requests && 
						Sorted->data.octet1 >= index->data.octet1 && 
						Sorted->data.octet2>= index->data.octet2 && 
						Sorted->data.octet3>= index->data.octet3
					) {  
						temp = Sorted->data;  
						Sorted->data = index->data;  
						index->data = temp;
					}  else if(
						Sorted->data.num_requests == index->data.num_requests && 
						Sorted->data.octet1 >= index->data.octet1 && 
						Sorted->data.octet2>= index->data.octet2 && 
						Sorted->data.octet3>= index->data.octet3 && 
						Sorted->data.octet4>= index->data.octet4
					) {  
						temp = Sorted->data;  
						Sorted->data = index->data;  
						index->data = temp;
					}
                    index = index->link;  
                }  
                Sorted = Sorted->link;  
            }     
        }  
		return Data;
		}
        
        std::string IPAddressAnalyzer::loadIps(int n) {
           
			Node *cursor;
			int i;
			int loop = n;
			std::string result = "";
            if (List != NULL) {
                for(cursor=IPAddressAnalyzer::sortIp(List), i=1, loop; cursor != NULL, loop > 0; cursor=cursor->link, loop--) {
                    result = std::to_string(i) + ", " + std::to_string(cursor->data.octet1) + "." + std::to_string(cursor->data.octet2) + "." + std::to_string(cursor->data.octet3) + "." + std::to_string(cursor->data.octet4) + "," + " " + std::to_string(cursor->data.num_requests) + "\n";
					cout << result;
					if (cursor->data.num_requests != cursor->link->data.num_requests) {
						++i;
					}
                }
            } else {
               	return "No nodes found!";
            }
			return result;
			
        }

		Node *IPAddressAnalyzer::searchIp(Node* List, Node::Item& entry)
		{
			// Precondition: head_ptr is a head pointer to a linked list
			// Postcondition: return value is pointer to first node containing
			// specified cursor. Returns NULL if no matching node found.
			Node *cursor;
			for(cursor = List; cursor != NULL; cursor = cursor->link)
			if(entry.octet1 == cursor->data.octet1)
			{
			return cursor;
			}
			return NULL;
        }

			

ip_format IPAddressAnalyzer::readNextItemFromFile(FILE* inputFileStream){
	if (! inputFileStream){
		std::string message("Cannot open input file for reading");
		throw std::invalid_argument(message.c_str());
	}
	char str[200];

	int num_request;
	int octet1;
	int octet2;
	int octet3;
	int octet4;

	ip_format data;
	

	while (!feof(inputFileStream))
	{
	  	fgets(str, sizeof str, inputFileStream);
		  if(str[0]=='\n'){
			  continue;
		  }
		std::string list = str;
		
		  
		char Ip_address[200];

		strcpy(Ip_address, list.c_str());
		char *token = strtok(Ip_address, ",");
		char *IpAddress =token;

		token = strtok(NULL, ",");
		data.num_requests =atoi(token);
	
		list = IpAddress;
		
		char Octets[200];
		

		strcpy(Octets, list.c_str());
		token = strtok(Octets, ".");
		data.octet1 = atoi(token);

		token = strtok(NULL, ".");
		data.octet2 = atoi(token);
		token = strtok(NULL, ".");
		data.octet3 = atoi(token);
		token = strtok(NULL, ".");
		data.octet4 =atoi(token);
		return data;
		
	}
	
	

}


void IPAddressAnalyzer::getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n){
	
	FILE* inFileStream = fopen(inputFilePath, "r");
	if (! inFileStream){
		char message[1024];
		sprintf(message, "Cannot open input file for reading: %s", inputFilePath);
		throw std::ios_base::failure(message);
	}

	FILE* outFileStream = fopen(outputFilePath, "w");
	if (! outFileStream){
		
		char message[1024];
		sprintf(message, "Cannot open output file for writing: %s", outputFilePath);
		throw std::ios_base::failure(message);
	}
	
	LogManager::writePrintfToLog(LogManager::Level::Status,
			"IPAddressAnalyzer::getMostFrequentIPAddress",
			"Starting to process file %s", inputFilePath);
			
			

			IPAddressAnalyzer Analyzer= IPAddressAnalyzer();
			
			while(!feof(inFileStream))
			{
				
				Analyzer.insertIp(readNextItemFromFile(inFileStream));
				
			}
			
			Analyzer.loadIps(n);
			
			fprintf(outFileStream,"%s",Analyzer.loadIps(n).c_str());

			

			// cout << Analyzer.getListSize(Analyzer.GetList()) << endl << endl;
			


	fflush(outFileStream);
	fclose(outFileStream);

	fclose(inFileStream);
}
