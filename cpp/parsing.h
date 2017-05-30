#ifndef parsing
#define parsing

#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>

void parse(int argc,char * argv[],std::string *label_name, std::string *output_name, int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, bool *print_help);


void fprint_help();

#endif