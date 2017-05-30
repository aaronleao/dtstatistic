#include "directory.h"

DIR * check_directory(std::string path_name)
{
	DIR *dir=opendir(path_name.c_str());
	if(!dir)
    {
        std::cerr<<"[DTSTATISTIC] Cannot access directory "<<path_name<<"."<<std::endl;
        exit(1);
    }
    else
    {   
        return dir;
    }
}


void list_directory(DIR * dir, std::string label_name, std::vector<std::string>  *log_files, std::vector<std::string>  *pdb_files)
{
    struct dirent *dirent;
    std::string file_name;

    while (dirent = readdir(dir))
    {
        file_name=dirent->d_name;
        if(!label_name.empty() )
        {

//            std::cout<<"-l flag is set"<<std::endl;
        
            /*
                Excluding "." and ".."  and taking exact match of label_name
            */
            std::size_t count=label_name.size();//label size
            std::size_t pos=0;                  //Search in the begining of the string
            std::size_t found=file_name.find(label_name.c_str(),pos,count);//Search a substring with size exact size of label

            if( found!=std::string::npos)
            {   
                std::string proximo=file_name.substr(count,5); //After found, check is the 5-following characters is "_run_"
                if(proximo == "_run_" && file_name.compare(".") && file_name.compare("..")) 
                {
                    if(file_name.find(".log")!=std::string::npos)
                    {
                        log_files->push_back(file_name);
                    }
                    if(file_name.find(".pdb")!=std::string::npos)
                    {
                        pdb_files->push_back(file_name);
                    }

                }
            }
        }
        else
        {
            //std::cout<<"-l flag is not set, trying with *\"_run\""<<std::endl;

            /*
                Excluding "." and ".." 
            */
            if( file_name.compare(".") && file_name.compare("..") && file_name.find("_run_")!=std::string::npos ) 
            {
                if(file_name.find(".log")!=std::string::npos)
                {
                    log_files->push_back(file_name);
                }
                if(file_name.find(".pdb")!=std::string::npos)
                {
                    pdb_files->push_back(file_name);
                }
            }

        }
    }

    if(pdb_files->size() == 0)
    {
        std::cerr<<"[DTSTATISTIC] Label not found: "<<label_name<<"."<<std::endl;
        exit(1);
    }

}


void open_log_files(std::vector<std::string>  *files, std::vector<leader>  *leaders)
{
    std::ifstream file;
    std::string trash;// Garbage string
    
    for (std::vector<std::string>::iterator it = files->begin(); it != files->end(); ++it)
    {
        //std::cout<<"VALOR: "<<*it<<std::endl;
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
