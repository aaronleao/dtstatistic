#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <string>

class leader
{
	private:
		int id;
		int number_of_members;
		float total_energy;
		float internal_energy;
		float coulomb;
		float vdw;
		float rmsd;
	public:
		leader(int id,int number_of_members,float total_energy, float internal_energy,float coulomb,float vdw, float rmsd):id(id),number_of_members(number_of_members),total_energy(total_energy),internal_energy(internal_energy),coulomb(coulomb),vdw(vdw),rmsd(rmsd){}
		int get_id(){return id;}
		int get_number_of_members(){return number_of_members;}
		float get_total_energy(){return total_energy;}
		float get_internal_energy(){return internal_energy;}
		float get_coulomb(){return coulomb;}
		float get_vdw(){return vdw;}
		float get_rmsd(){return rmsd;}
};



DIR *check_directory(std::string directory_name);
void list_directory(DIR * dir, std::string label_name, std::vector<std::string>  *log_files, std::vector<std::string>  *pdb_files);
void list_files_vector(std::vector<std::string>  *array);

#endif