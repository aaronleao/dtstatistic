#include "molecule.h"

atom::atom()
{
}

int molecule::get_id()
{
	return id;
}
std::string molecule::get_log_file_name()
{
	return log_file_name;
}
std::string molecule::get_pdb_file_name()
{
	return pdb_file_name;
}
float molecule::get_total_energy()
{
	return total_energy;
}
float molecule::get_interaction_energy()
{
	return interaction_energy;
}
float molecule::get_coulomb()
{
	return coulomb;
}
float molecule::get_vdW()
{
	return vdW;
}
float molecule::get_rmsd_leader()
{
    return rmsd_leader;
}
void molecule::set_id(int var){id=var;}
void molecule::set_log_file_name(std::string var){log_file_name=var;}
void molecule::set_pdb_file_name(std::string var){pdb_file_name=var;}
void molecule::set_total_energy(float var){total_energy=var;}
void molecule::set_interaction_energy(float var){interaction_energy=var;}
void molecule::set_coulomb(float var){coulomb=var;}
void molecule::set_vdW(float var){vdW=var;}
void molecule::set_rmsd_leader(float var){rmsd_leader=var;}
void molecule::print(){std::cout<<"ID: "<<id<<std::endl;}

void read_molecule(std::string  log_file_name , std::vector <molecule*> *molecules_vector)
{
    std::ifstream log_file,pdb_file;

    /*
    *    Get pdb_file_name from log_file_name
    */
    std::size_t pos = log_file_name.find("."); 
    std::string pdb_file_name=log_file_name.substr (0,pos);
    pdb_file_name +=".pdb";

    /*
    *   Open log and pdb files
    */
    log_file.open(log_file_name, std::fstream::in);
    pdb_file.open(pdb_file_name, std::fstream::in);



    std::string trash;// Garbage string
    /*
    * log file variables
    */
    int id;
    int number_of_members;
    float total_Energy;
    float internal_Energy;
    float coulomb;
    float vdw;
    float rmsd;
    int number_of_Clusters;
    int seed;
    /*
    * pdb files variables
    */
    std::string type;
    float x_atom;
    float y_atom;
    float z_atom;

    if(log_file.is_open() && pdb_file.is_open())
    {
        log_file>>trash>>trash>>number_of_Clusters;//Geting number of clusters of the first line
        log_file>>trash>>trash>>seed;

        for(int i=1;i<=number_of_Clusters;i++)
        {
            getline(log_file,trash);
            log_file>>trash>>id>>trash;
            getline(log_file,trash);
            log_file>>trash>>trash>>number_of_members;
            log_file>>trash>>trash>>total_Energy;
            log_file>>trash>>trash>>vdw;
            log_file>>trash>>trash>>coulomb;
            log_file>>trash>>trash>>internal_Energy;
            log_file>>trash>>trash>>rmsd;
            getline(log_file,trash);
            getline(log_file,trash);
    
            int aux_id=0;

            molecule * new_molecule= new molecule(id,log_file_name,pdb_file_name,total_Energy,internal_Energy,coulomb,vdw);

            pdb_file >> trash >> aux_id;
            std::getline(pdb_file,trash);
            while( trash.compare("ENDMDL") )
            {
                std::getline(pdb_file,trash);
                if(trash.compare("ENDMDL")) // trash != "ENDMDL"
                {
                    type = trash.substr(76,77);
                    //if(type.compare(" H  ")) // Uncomment to allow only non Hydrogen atoms.
                    {
                        x_atom = stof(trash.substr(30,37));
                        y_atom = stof(trash.substr(38,45));
                        z_atom = stof(trash.substr(46,53));                        
                        atom *new_atom = new atom(type, x_atom, y_atom, z_atom);
                        new_molecule->atom_list.push_back(new_atom);
                    }
                }
                else
                    break;
            }
            molecules_vector->push_back(new_molecule);
        }
    }
    log_file.close();
    pdb_file.close();
}
std::vector<molecule*> *create_molecule_vector( std::vector<std::string> log_files)
{
	std::vector<molecule*> *new_molecule_vector=new std::vector<molecule*> ;
	for (std::vector<std::string>::iterator it = log_files.begin(); it !=  log_files.end(); it++)
	{
		read_molecule(*it,new_molecule_vector);
	}

	return new_molecule_vector;
}



