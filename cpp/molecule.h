#ifndef MOLECULE_H
#define MOLECULE_H


// #include <openbabel/obconversion.h>
// #include <openbabel/mol.h>
#include <iostream>
#include <cstring>
#include <vector>
//#include <dirent.h>
//#include <unistd.h>
#include <fstream>


class atom
{
	private:
		std::string type;
		float x;
		float y;
		float z;
	public:
		atom();
		atom(std::string v_type, float v_x,float v_y, float v_z):type(v_type),x(v_x),y(v_y),z(v_z){};

		std::string get_type(){return type;};
		void set_type(std::string var){type=var;};

		float get_x(){return x;};
		void set_x(float v_x){x=v_x;};

		float get_y(){return y;};
		void set_y(float v_y){y=v_y;};

		float get_z(){return z;};
		void set_z(float v_z){z=v_z;};
};

class molecule
{
	private:
		int id;
		std::string log_file_name;
		std::string pdb_file_name;
		float total_energy;
		float interaction_energy;
		float coulomb;
		float vdW;
		float rmsd_leader;

	public:
		std::vector <class atom*> atom_list;
		molecule(){};
		molecule(int var_id,std::string var_log_file_name,std::string var_pdb_file_name,float var_total_energy,float var_interaction_energy,float var_coulomb,float var_vdW):id(var_id),log_file_name(var_log_file_name),pdb_file_name(var_pdb_file_name),total_energy(var_total_energy),interaction_energy(var_interaction_energy),coulomb(var_coulomb),vdW(var_vdW){};

		//int get_id(){return id;};
		int get_id();
		std::string get_log_file_name();
		std::string get_pdb_file_name();
		float get_total_energy();
		float get_interaction_energy();
		float get_coulomb();
		float get_vdW();
		float get_rmsd_leader();

		void set_id(int var);
		void set_log_file_name(std::string var);
		void set_pdb_file_name(std::string var);
		void set_total_energy(float var);
		void set_interaction_energy(float var);
		void set_coulomb(float var);
		void set_vdW(float var);
		void set_rmsd_leader(float var);
		void print();

};

void read_molecule(std::string  file_name, std::vector<molecule *> *molecules_vector);
std::vector<molecule*> *create_molecule_vector( std::vector<std::string> log_files);

int mol2_converter(std::vector<std::string>  *pdb_files);

#endif