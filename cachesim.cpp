#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cmath>
#include <stdlib.h>

using namespace std;
long long hits,total, sets_used, number_sets, cache_size;
int block_size, nways, victim_size, victim_ways, victim_sets;
class cache_handle {
public:
	std::map<string, int> block_matrix;
	int flag_bit;
	int full_set;
};

std::map<string, cache_handle> index_matrix;


void static vc_cache(string index_address, string tag_address, int flag){
	
	if (index_matrix.find(index_address) == index_matrix.end()){
		cache_handle *instance = new cache_handle();
		instance->block_matrix[tag_address]= 0;
		instance->flag_bit =1;
		index_matrix[index_address] = *instance;
	}
	else {
		cache_handle cache_object = index_matrix[index_address];
		cache_handle *mem = &cache_object;
		if (flag == 0){
			nways = ceil ((double)cache_size / (block_size));
		}
		if (mem->block_matrix.find(tag_address) == mem->block_matrix.end())
		{
			if (mem->flag_bit < nways)
			{
				typedef std::map<string, int>::iterator it_type;
				for (it_type iterator = mem-> block_matrix.begin(); iterator != mem-> block_matrix.end(); iterator++){
					iterator->second = iterator->second +1;
				}

				mem->block_matrix[tag_address] = 0;
				mem->flag_bit = mem->flag_bit +1;
			}
			else
			{
				if (mem-> full_set == 0)
				{
					mem->full_set = 1;
					sets_used++;
				}
				string removalKey;
				typedef std::map<string, int> ::iterator it_type;
				for (it_type iterator = mem-> block_matrix.begin(); iterator != mem-> block_matrix.end(); iterator++)
				{
					if (iterator->second == nways - 1)
						removalKey = iterator -> first;
					iterator->second = iterator->second +1;
				}
				mem->block_matrix.erase(removalKey);
				mem->block_matrix[tag_address]=0;
			}
		}

		else 
		{
			hits++;
			int current_tag_level = mem->block_matrix[tag_address];
			typedef std::map<string, int> :: iterator it_type;
			for (it_type iterator = mem-> block_matrix.begin(); iterator != mem-> block_matrix.end(); iterator++)
			{
				if (iterator->second < current_tag_level){
					iterator -> second = iterator->second +1;
				}
			}
			mem-> block_matrix[tag_address] = 0;
		}
		index_matrix[index_address] = *mem;
	}
	total++;
}


void static cache_l1(string index_address, string tag_address)
{
	if (index_matrix.find(index_address) == index_matrix.end()){
		cache_handle *instance = new cache_handle();
		instance->block_matrix[tag_address]= 0;
		instance->flag_bit =1;
		index_matrix[index_address] = *instance;
	}
	else {
		cache_handle cache_object = index_matrix[index_address];
		cache_handle *mem = &cache_object;
		if (mem->block_matrix.find(tag_address) == mem->block_matrix.end())
		{
			if (mem->flag_bit < nways){
				typedef std::map<string, int>::iterator it_type;
				for (it_type iterator = mem-> block_matrix.begin(); iterator != mem-> block_matrix.end(); iterator++){
					iterator->second = iterator->second +1;
				}

				mem->block_matrix[tag_address] = 0;
				mem->flag_bit = mem->flag_bit +1;
			}
			else{
				if (mem-> full_set == 0)
				{
					mem->full_set = 1;
					sets_used++;
				}
				string removalKey;
				typedef std::map<string, int> ::iterator it_type;
				for (it_type iterator = mem-> block_matrix.begin(); iterator != mem-> block_matrix.end(); iterator++){
					if (iterator->second == nways - 1)
						removalKey = iterator -> first;
					iterator->second = iterator->second +1;
				}
				mem->block_matrix.erase(removalKey);
				mem->block_matrix[tag_address]=0;
			}
		}

		else {
			hits++;
			int current_tag_level = mem->block_matrix[tag_address];
			typedef std::map<string, int> :: iterator it_type;
			for (it_type iterator = mem-> block_matrix.begin(); iterator != mem-> block_matrix.end(); iterator++)
			{
				if (iterator->second < current_tag_level){
					iterator -> second = iterator->second +1;
				}
			}
			mem-> block_matrix[tag_address] = 0;
		}
		index_matrix[index_address] = *mem;
	}
	total++;
}



int main (int argc, char *argv[]){
	hits = 0;
	total = 0;
	if (argc > 6) {
		cerr << "ERROR: Provide a file name for trace file, cache size and block size in bytes, number of ways(1 direct mapped) \n";
		return 0;
	}

	ifstream fileIn(argv[1]);
	if (!fileIn.is_open()){
		cerr << "ERROR: File does not exist \n";
		return 1;
	}

	cache_size = atol(argv[2]);
	block_size= atoi(argv[3]);
	nways = atoi(argv[4]);
	if (argc == 6)
	{
	victim_size = atoi(argv[5]);
	victim_ways = ceil((double)victim_size/(block_size));
	victim_sets = ceil((double)victim_size/ (block_size*victim_ways));
	}

	if (nways == 0){
		nways = ceil ((double)cache_size / (block_size));
		cout << "cache size ->" << cache_size << " , " << "block_size -> " << block_size << " , " << "number of Ways -> " << nways << endl;

	}
	else
	{
		cout << "cache size ->"<<cache_size<< ","<<"block_size - >" << block_size << "," << "number of ways -> " << nways << endl;

	}

	long long list_array[10];
	string pc_addr[10];
	char branch_status[10];
	long long index = 0;
	long long offset;
	char instructionType;

	int tag_bits, index_bits, offset_bits;
	number_sets = ceil ((double)cache_size / (block_size* nways));
	index_bits = log (number_sets) / log(2);
	offset_bits = log (block_size) /log(2);
	tag_bits = 32 - index_bits - offset_bits;
	cout << "number of sets= :" << number_sets << "\n number of tag Bits: " << tag_bits << " , " << "\n number of index bits: " << index_bits << " , " << "\n number of offset bits: " << offset_bits << endl;
	cout << "\n Calculating Cache hit and miss rate ... \n" << endl;
	while (!fileIn.eof())
	{
		string currentAddress, tag_address, index_address;

		fileIn >> instructionType;
		if (fileIn.fail()) break;

		fileIn >> dec >> offset;
		if (fileIn.fail ()) break;

		long long address;
		fileIn >> hex >> address;
		if (fileIn.fail()) break;

		fileIn.ignore(256, '\n');

		std:: string binary = std:: bitset <44>(address). to_string();
		currentAddress = binary.substr(binary.length() -32);
		//cout << "currentAddress: " << currentAddress << endl;
		tag_address = currentAddress.substr(0, tag_bits);
		//cout << "Tag address: " << tag_address << endl;
		index_address = currentAddress.substr(tag_bits, index_bits);
		//cout << "Line address: " << index_address << endl;
		if ((argc == 6) && (nways!=1))
		{
			vc_cache(index_address, tag_address, 0);
		}
		if ((argc ==6) && (nways==1))
		{
			vc_cache(index_address, tag_address, 1);
		}
		else{
			cache_l1(index_address, tag_address);
		}
	} 

	cout << " Cache hits-> " << hits << " , " << "\n Cache Miss-> " << total- hits << " , "  << "\n Total-> " << total << "\n" << endl;
	cout << " Cahe  Hit rate-> " << ((double) (hits) / total) * 100 << " % " << " , " << "\n Cache Miss rate-> " << ((double)(total - hits) / total) * 100 << "%" << endl;
	cout << "********************************************" << endl;

	return 0; 

}











