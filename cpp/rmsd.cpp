#include <cmath>
#include "rmsd.h"

float get_molecules_RMSD(molecule * molecule1, molecule * molecule2)
{
	int aux1 =molecule1->get_number_of_heavy_atoms();
	int aux2 =molecule1->get_number_of_heavy_atoms();
	if(aux1 != aux2)
	{
		std::cerr << "[DTSTATISTIC] RMSD: Molecules sizes mismatch: " <<molecule1->get_pdb_file_name() << " model: " << molecule1->get_id() <<" has " << aux1 << " heavy atoms " << molecule2->get_pdb_file_name() << " model: " << molecule2->get_id() <<" has " << aux2 << " heavy atoms " << std::endl;
        exit(1);
	}

	float aux_x=0,aux_y=0,aux_z=0;
	for(int i=0 ; i< aux1 ; i++)
	{
		aux_x += (molecule1->atom_list[i]->get_x() - molecule2->atom_list[i]->get_x() ) * (molecule1->atom_list[i]->get_x() - molecule2->atom_list[i]->get_x() );
		aux_y += (molecule1->atom_list[i]->get_y() - molecule2->atom_list[i]->get_y() ) * (molecule1->atom_list[i]->get_y() - molecule2->atom_list[i]->get_y() );
		aux_z += (molecule1->atom_list[i]->get_z() - molecule2->atom_list[i]->get_z() ) * (molecule1->atom_list[i]->get_z() - molecule2->atom_list[i]->get_z() );
	}
	//std::cout<< "Cheguei aqui";
	return sqrt((aux_x + aux_y + aux_z)/aux1);
}