#include "clustering.h"

std::vector<molecule*> *clustering(std::vector<molecule*> molecules , float rmsd_clustering)
{
	std::vector<molecule*> *leaders = new std::vector<molecule*>;
	leaders->push_back(molecules[0]);
	(*leaders)[0]->set_rmsd_leader(0);

	unsigned int molecules_max =molecules.size();	
	unsigned int i=0,j=0;
	float rmsd;
	unsigned int count=0;

	//rmsd = get_molecules_RMSD((*molecules)[0],(*leaders)[0]);
	//std::cout << "RMSD: " << rmsd << std::endl;
	for(i=1; i< molecules_max ; i++)
	{
		count = 0;
		for(j=0; j < leaders->size() ; j++)
		{
			rmsd = get_molecules_RMSD(molecules[i],(*leaders)[j]);
			if(rmsd >= rmsd_clustering )
			{
				count ++;
				if(count==1)
				{
					molecules[i]->set_rmsd_leader(rmsd);
				}
			}
		}
		if(count == leaders->size())
		{
			leaders->push_back(molecules[i]);
		}
	}
	
	return leaders;
}