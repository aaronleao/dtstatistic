
#ifndef parsing
#define parsing

#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "directory.h"

//void parse(int argc , char * argv[] , std::string *label_name , std::string *path_name , std::string *output_name , unsigned int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, float *rmsd_clustering, bool *print_help, bool *only_rmsd_calculation, std::string *rmsd_file1, std::string  *rmsd_file2);
void parse(int argc , char * argv[] , std::string *label_name , std::string *path_name , std::string *output_name , unsigned int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, float *rmsd_clustering, bool *print_help, bool *only_rmsd_calculation, std::string *rmsd_file1, std::string  *rmsd_file2);
void check_flags(const std::string label_name,std::string * directory_name, std::vector<std::string> *log_files, std::vector<std::string> *pdb_files);
void fprint_help();

#endif