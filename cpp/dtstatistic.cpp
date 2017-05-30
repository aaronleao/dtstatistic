//#include <cstdlib>

#include <iostream>
#include <vector>
#include <cstdlib>
#include "directory.h"
#include "parsing.h"
#include "molecule.h"

/******************************************
*			GLOBAL VARIABLES
******************************************/
std::string label_name="";
std::string output_name="";
int nruns=1;
int number_of_ligands=1;
bool analysis_by_total_energy=true;
bool analysis_by_internal_energy=false;
bool print_help=false;
std::vector<std::string>  log_files;
std::vector<std::string>  pdb_files;
std::vector<leader>  leaders;
/*****************************************/



int main(int argc, char * argv[])
{
	// Parsing input command
	parse(argc, argv, &label_name, &output_name, &number_of_ligands, &analysis_by_total_energy, &analysis_by_internal_energy, &print_help);
	
	// Check if is needed to print help message
	if(print_help || !label_name.length() )fprint_help();
	
	// Open directory and list available files
	DIR * dir=open_directory(label_name.c_str());// Open directory
	list_directory(dir, &log_files, &pdb_files); // Selecting available files
	mol2_converter(&pdb_files);
	chdir(label_name.c_str());					 //	Change to the path
	open_log_files(&log_files,&leaders);		 // Open files

}





//	cout<<"label_name: "<<label_name<<endl<<"output_name: "<<output_name<<endl<<"n: "<<number_of_ligands<<endl<<"-t: "<<analysis_by_total_energy<<endl<<"-i: "<<analysis_by_internal_energy<<endl<<print_help<<endl;