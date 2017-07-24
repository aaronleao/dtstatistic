#include "log.h"

void write_output_clustering(std::vector<molecule*> leaders, std::string output_name, unsigned int number_of_ligands)
{
	std::ofstream output_file;
	//output_file.open(output_name, std::fstream::out);
	output_file.open(output_name);
	
	if(number_of_ligands >= leaders.size())
		number_of_ligands = leaders.size();
	if(output_file.is_open())
	{
		//output_file << std::setw(24) << std::setw(26) << std::setw(7) << std::setw(7) << std::setw(7);
 		output_file << "\tFile\t\t" << "Model\t" << "T_Energy " << "I_Energy " << "RMSD" << std::endl;
		for( unsigned int i=0 ; i < number_of_ligands ; i++)
		{
			output_file << leaders[i]->get_log_file_name() << "\t" << leaders[i]->get_id() << "\t" << leaders[i]->get_total_energy() << "\t" << leaders[i]->get_interaction_energy() << "\t" << leaders[i]->get_rmsd_leader() << std::endl;
		}
		std::cerr << "[DTSTATISTIC] Logged successfully in file " << output_name << "." << std::endl;
	}	
	output_file.close();

}