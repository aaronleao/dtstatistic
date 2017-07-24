#include <cmath>
#include "rmsd.h"

float get_molecules_RMSD(molecule * aux1, molecule * aux2)
{
	int aux1_size = aux1->atom_list.size();
	int aux2_size = aux2->atom_list.size();
	if(aux1_size != aux2_size)
	{
		std::cerr << "[DTSTATISTIC] RMSD: Molecules sizes mismatch: " <<aux1->get_pdb_file_name() << " model: " << aux1->get_id() <<" has " << aux1_size << " atoms " << aux2->get_pdb_file_name() << " model: " << aux2->get_id() <<" has " << aux2_size << " atoms " << std::endl;
        exit(1);
	}

	float aux_x=0,aux_y=0,aux_z=0;
	for(int i=0 ; i< aux1_size ; i++)
	{
		aux_x += (aux1->atom_list[i]->get_x() - aux2->atom_list[i]->get_x() ) * (aux1->atom_list[i]->get_x() - aux2->atom_list[i]->get_x() );
		aux_y += (aux1->atom_list[i]->get_y() - aux2->atom_list[i]->get_y() ) * (aux1->atom_list[i]->get_y() - aux2->atom_list[i]->get_y() );
		aux_z += (aux1->atom_list[i]->get_z() - aux2->atom_list[i]->get_z() ) * (aux1->atom_list[i]->get_z() - aux2->atom_list[i]->get_z() );
	}
	return sqrt((aux_x + aux_y + aux_z)/aux1_size);
}