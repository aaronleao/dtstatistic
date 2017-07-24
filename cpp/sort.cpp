#include "sort.h"

bool sort_by_total_energy(molecule *i , molecule *j)
{
	return i->get_total_energy() < j->get_total_energy() ;
}
bool sort_by_interaction_energy(molecule *i , molecule *j)
{
	return i->get_interaction_energy() < j->get_interaction_energy();
}



void sort_molecule(std::vector<molecule*> *aux , bool total_energy)
{

	if(total_energy)
	{
		std::sort(aux->begin(),aux->end(),sort_by_total_energy);
	}
	else
	{
		std::sort(aux->begin(),aux->end(),sort_by_interaction_energy);
	}
}