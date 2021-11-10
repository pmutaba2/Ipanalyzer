/*
 *      Author: kompalli
 */

#ifndef IPADDRESSANALYZE_H_
#define IPADDRESSANALYZE_H_

#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include "./util/GetMemUsage.h"
#include "./util/LogManager.h"

typedef struct {
    int octet1;
    int octet2;
    int octet3;
    int octet4;
    
    int num_requests;
} ip_format;

struct Node {
    typedef ip_format Item;
    Item data;
    Node *link=NULL;
};

class IPAddressAnalyzer{
	 private:
         Node *List;
    public:
        IPAddressAnalyzer() {
        	List = NULL;
        }
		Node *SetIp(Node *entry, Node *temp);	

		Node *GetIp();

        void insertIp(ip_format entry);
		
		Node* searchIp(Node *List, Node::Item& entry);
		void  updateIp(Node::Item& oldIPdata,Node::Item& newIpdata);
		Node* sortIp(Node *List);
        
        std::string loadIps(int n);
		int getListSize(Node *node);
		Node * GetList()
		{
			return List;
		}

		

		
		

	static ip_format readNextItemFromFile(FILE* inputFileStream);



	
	/**
	 *
	 *
	 * @param inputFilePath Path of the input file.
	 * @param outputFilePath Path of the output file.
	 * @param topN Number of
	 *
	 * If the input file cannot be read throw an error of type ios_base::failure
	 * If the output file cannot be generated, then throw an error of type ios_base::failure
	 */
	static void getMostFrequentIPAddress(char* inputFilePath, char* outputFilePath, int n);

};
#endif /* IPADDRESSANALYZE_H_ */
