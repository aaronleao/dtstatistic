#include "molecule.h"

atom::atom(){}
molecule::molecule()
{
    id=0;
    log_file_name="";
    pdb_file_name="";
    total_energy=0;
    internal_energy=0;
    interaction_energy=0;
    coulomb=0;
    vdW=0;
    rmsd_leader=0;
    number_of_heavy_atoms = 0;

}
int molecule::get_id(){	return id;}
std::string molecule::get_log_file_name(){	return log_file_name;}
std::string molecule::get_pdb_file_name(){	return pdb_file_name;}
float molecule::get_total_energy(){	return total_energy;}
float molecule::get_internal_energy(){   return internal_energy;}
float molecule::get_interaction_energy(){	return interaction_energy;}
float molecule::get_coulomb(){	return coulomb;}
float molecule::get_vdW(){	return vdW;}
float molecule::get_rmsd_leader(){    return rmsd_leader;}
unsigned short molecule::get_number_of_heavy_atoms(){return number_of_heavy_atoms;};
void molecule::set_id(int var){id=var;}
void molecule::set_log_file_name(std::string var){log_file_name=var;}
void molecule::set_pdb_file_name(std::string var){pdb_file_name=var;}
void molecule::set_total_energy(float var){total_energy=var;}
void molecule::set_internal_energy(float var){internal_energy=var;}
void molecule::set_interaction_energy(float var){interaction_energy=var;}
void molecule::set_coulomb(float var){coulomb=var;}
void molecule::set_vdW(float var){vdW=var;}
void molecule::set_rmsd_leader(float var){rmsd_leader=var;}
//void molecule::set_number_of_heavy_atoms(unsigned short var){number_of_heavy_atoms = var;};


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
            new_molecule->set_interaction_energy(coulomb + vdw);
            pdb_file >> trash >> aux_id;
            std::getline(pdb_file,trash);
            while( trash.compare("ENDMDL") )
            {
                std::getline(pdb_file,trash);
                if(trash.compare("ENDMDL")) // trash != "ENDMDL"
                {
                    atom *new_atom = new atom;

                    new_atom->set_record_name(trash.substr(0,6));
                    new_atom->set_serial_number(stoi(trash.substr(6,5)));
                    new_atom->set_atom_name(trash.substr(11,5));
                    if(new_atom->get_atom_name().compare("    H")) // If currenty atom is not H.
                        new_molecule->set_number_of_heavy_atoms(); // Increase the number of heavy atoms.

                    /*Not used in Dockthor*/
                    //new_atom->set_alternate_location_indicator(trash.substr(16,2));
                    new_atom->set_residue_name(trash.substr(17,3));
                    new_atom->set_chain_id(trash.substr(21,1).c_str()[0]);
                    new_atom->set_residue_sequence(stoi(trash.substr(22,4)));
                    /*Not used in Dockthor*/
                    //new_atom->set_icode(trash.substr(26,1).c_str()[0]);
                    new_atom->set_x(stof(trash.substr(30,7)));
                    new_atom->set_y(stof(trash.substr(38,7)));
                    new_atom->set_z(stof(trash.substr(46,7)));
                    new_atom->set_occupancy(stof(trash.substr(54,6)));
                    new_atom->set_temperature_factor(stof(trash.substr(60,6)));
                    new_atom->set_element(trash.substr(76,2));
                    new_atom->set_charge(trash.substr(78,2));

                    new_molecule->atom_list.push_back(new_atom);
                    //mostrar(new_atom);

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

molecule * load_atoms(std::string file_name)
{
    check_file(file_name);
    molecule *new_molecule = new molecule;
    new_molecule->set_pdb_file_name(file_name);

    std::ifstream pdb_file;
    std::string trash;
    pdb_file.open(file_name, std::fstream::in);
    if(pdb_file.is_open())
    {
        std::getline(pdb_file,trash);
        while( trash.compare("ENDMDL") || !pdb_file.eof() )
        {
            std::getline(pdb_file,trash);
            if(trash.compare("ENDMDL")) // trash != "ENDMDL"
            {
                atom *new_atom = new atom;
                new_atom->set_record_name(trash.substr(0,6));
                new_atom->set_serial_number(stoi(trash.substr(6,5)));
                new_atom->set_atom_name(trash.substr(11,5));
                if(new_atom->get_atom_name().compare("    H")) // If currenty atom is not H.
                    new_molecule->set_number_of_heavy_atoms(); // Increase the number of heavy atoms.

                /*Not used in Dockthor*/
                //new_atom->set_alternate_location_indicator(trash.substr(16,2));
                new_atom->set_residue_name(trash.substr(17,3));
                new_atom->set_chain_id(trash.substr(21,1).c_str()[0]);
                new_atom->set_residue_sequence(stoi(trash.substr(22,4)));
                /*Not used in Dockthor*/
                //new_atom->set_icode(trash.substr(26,1).c_str()[0]);
                new_atom->set_x(stof(trash.substr(30,7)));
                new_atom->set_y(stof(trash.substr(38,7)));
                new_atom->set_z(stof(trash.substr(46,7)));
                new_atom->set_occupancy(stof(trash.substr(54,6)));
                new_atom->set_temperature_factor(stof(trash.substr(60,6)));
                new_atom->set_element(trash.substr(76,2));
                new_atom->set_charge(trash.substr(78,2));

                new_molecule->atom_list.push_back(new_atom);
                //mostrar(new_atom);

            }
            else
                break;
        }
        return new_molecule;
    }
    else
        return NULL;
}

void mostrar(atom *new_atom)
{
    std::cout<<\
    std::setw(6)<<\
    new_atom->get_record_name() <<\
    std::setw(5)<<\
    new_atom->get_serial_number()<<\
    std::setw(5)<<\
    new_atom->get_atom_name() <<\
    /*  Not used in Dockthor */
    /*std::setw(2)<<\*/
    /*new_atom->get_alternate_location_indicator()<<\*/
    std::setw(4)<<\
    new_atom->get_residue_name()<<\
    std::setw(2)<<\
    new_atom->get_chain_id()<<\
    std::setw(4)<<\
    new_atom->get_residue_sequence()<<\
    /*  Not used in Dockthor */
    /*std::setw(1)<<\*/
    new_atom->get_icode()<<"   "<<\
    std::setw(12)<<std::setprecision(3)<<\
    new_atom->get_x()<<\
    std::setw(8)<<std::setprecision(3)<<std::fixed<<\
    new_atom->get_y()<<\
    std::setw(8)<<std::setprecision(3)<<std::fixed<<\
    new_atom->get_z()<<\
    std::setw(6)<<std::setprecision(2)<<std::fixed<<\
    new_atom->get_occupancy()<<\
    std::setw(6)<<std::setprecision(2)<<std::fixed<<\
    new_atom->get_temperature_factor()<<\
    std::setw(12)<<\
    new_atom->get_element()<<\
    std::setw(2)<<\
    new_atom->get_charge()<<std::endl;
}