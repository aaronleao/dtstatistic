#include "directory.h"

DIR * open_directory(const char * path_name)
{
	DIR *dir=opendir(path_name);
	if(!dir)
    {
        std::cerr<<"[DTSTATISTIC] Cannot access directory."<<std::endl;
        exit(1);
    }
    else
    {   
        return dir;
    }
}


void list_directory(DIR * dir, std::vector<std::string>  *log_files, std::vector<std::string>  *pdb_files)
{
    struct dirent *dirent;
    std::string aux;
    while (dirent = readdir(dir))
    {
        aux=dirent->d_name;
        if( aux.compare(".") && aux.compare("..") && aux.find("_run_")!=std::string::npos) //Not selecting "."" and ".." and not .log nor .pdb
        {
            if(aux.find(".log")!=std::string::npos)
            {
                log_files->push_back(aux);
            }
            if(aux.find(".pdb")!=std::string::npos)
            {
                pdb_files->push_back(aux);
            }
        }
    }
}

void open_log_files(std::vector<std::string>  *files, std::vector<leader>  *leaders)
{
    std::ifstream file;
    std::string trash;// Garbage string
    
    for (std::vector<std::string>::iterator it = files->begin(); it != files->end(); ++it)
    {
        std::cout<<"VALOR: "<<*it<<std::endl;
        //file.open(*it,std::fstream::in);
        if(file.is_open())
        {
            //std::cout<<"Opening file: "<<*it<<std::endl;
            int number_of_Clusters;
            int seed;
            file>>trash>>trash>>number_of_Clusters;//Geting number of clusters of the first line
            file>>trash>>trash>>seed;


            for(int i=1;i<=number_of_Clusters;i++)
            {
                getline(file,trash);
                int id;
                int number_of_members;
                float total_Energy;
                float internal_Energy;
                float coulomb;
                float vdw;
                float rmsd;

                file>>trash>>id>>trash;
                getline(file,trash);
                file>>trash>>trash>>number_of_members;
                file>>trash>>trash>>total_Energy;
                file>>trash>>trash>>vdw;
                file>>trash>>trash>>coulomb;
                file>>trash>>trash>>internal_Energy;
                file>>trash>>trash>>rmsd;
                getline(file,trash);
                getline(file,trash);
                leader lider1(id,number_of_members,total_Energy,internal_Energy,coulomb,vdw,rmsd);
                leaders->push_back(lider1);
            }
        }
        for (std::vector<leader >::iterator it = leaders->begin(); it != leaders->end(); ++it)
        {
            //std::cout<<"total_Energy: "<<it->get_total_energy()<<std::endl;
        }
        file.close();

    }



// if (myReadFile.is_open())
// {
//     while (!myReadFile.eof())
//     {
//         myReadFile >> output;
//         cout<<output;
//     }
// }



}
