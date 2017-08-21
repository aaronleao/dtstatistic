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
		//Atom properties according to the PDB Format v33 pg 186
		std::string record_name;				//1-6
		int serial_number;						//7-11
		std::string atom_name;					//13-16
		char alternate_location_indicator;		//17
		std::string residue_name;				//18-20
		char chain_id;							//22
		int residue_sequence;					//23-26
		char icode;								//27
		float x;								//31-38
		float y;								//39-46
		float z;								//47-54
		float occupancy;						//55-60
		float temperature_factor;				//61-66
		std::string element;					//77-78
		std::string charge;						//79-80


	public:
		atom();
		//atom(std::string v_type, float v_x,float v_y, float v_z):type(v_type),x(v_x),y(v_y),z(v_z){};

		std::string get_record_name(){return record_name;};
		void set_record_name(std::string var){record_name = var;};
		int get_serial_number(){return serial_number;};
		void set_serial_number(int var){serial_number = var;};
		std::string get_atom_name(){return atom_name;};
		void set_atom_name(std::string var){atom_name = var;};
		char get_alternate_location_indicator(){return alternate_location_indicator;};
		void set_alternate_location_indicator(char var){alternate_location_indicator = var;};
		std::string get_residue_name(){return residue_name;};
		void set_residue_name(std::string var){residue_name = var;};
		char get_chain_id(){return chain_id;};
		void set_chain_id(char var){chain_id = var;};
		int get_residue_sequence(){return residue_sequence;};
		void set_residue_sequence(int var){residue_sequence = var;};
		char get_icode(){return icode;};
		void set_icode(char var){icode = var;};
		float get_x(){return x;};
		void set_x(float v_x){x=v_x;};
		float get_y(){return y;};
		void set_y(float v_y){y=v_y;};
		float get_z(){return z;};
		void set_z(float v_z){z=v_z;};		
		float get_occupancy(){return occupancy;};
		void set_occupancy(float var){occupancy = var;};
		float get_temperature_factor(){return temperature_factor;};
		void set_temperature_factor(float var){temperature_factor = var;};
		std::string get_element(){return element;};
		void set_element(std::string var){element = var;};
		std::string get_charge(){return charge;};
		void set_charge(std::string var){charge = var;};

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
		unsigned short number_of_heavy_atoms;

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
		unsigned short get_number_of_heavy_atoms();

		void set_id(int var);
		void set_log_file_name(std::string var);
		void set_pdb_file_name(std::string var);
		void set_total_energy(float var);
		void set_interaction_energy(float var);
		void set_coulomb(float var);
		void set_vdW(float var);
		void set_rmsd_leader(float var);
		void set_number_of_heavy_atoms(unsigned short var);
		void print();

};

void read_molecule(std::string  file_name, std::vector<molecule *> *molecules_vector);
std::vector<molecule*> *create_molecule_vector( std::vector<std::string> log_files);

int mol2_converter(std::vector<std::string>  *pdb_files);

#endif