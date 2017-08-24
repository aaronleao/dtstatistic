#include "parsing.h"

// void parse(int argc , char * argv[] , std::string *label_name , std::string *path_name , std::string *output_name , unsigned int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, float *rmsd_clestering, bool *print_help, bool *only_rmsd_calculation, std::string * rmsd_file1, std::string *rmsd_file2)
// {
	
// 	std::string aux;
// 	for(int i=1;i<argc;i++)
// 	{
// 		aux=argv[i];

// 		if(! aux.compare("-h") || argc==1)
// 		{
// 			*print_help=true;
// 			fprint_help();
// 		}

// 		if(! aux.compare("-d") )
// 		{
// 			if(i+1<argc)
// 			{
// 				*path_name=argv[i+1];	
// 				i++;
// 			}
// 			else
// 				fprint_help();
// 		}
// 		else
// 		{
// 			if(! aux.compare("-l") )
// 			{
// 				if(i+1<argc)
// 				{
// 					*label_name=argv[i+1];
// 					i++;
// 				}
// 				else
// 					fprint_help();
// 			}
// 			else
// 			{
// 				if(! aux.compare("-o"))
// 				{
// 					if(i+1<argc)
// 					{
// 						*output_name=argv[i+1];
// 						i++;
// 					}
// 					else
// 						fprint_help();
// 				}
// 				else
// 				{
// 					if(! aux.compare("-n") )
// 					{
// 						if(i+1<argc)
// 						{
// 							*number_of_ligands=atoi(argv[i+1]);	
// 							i++;
// 						}
// 						else
// 							fprint_help();
// 					}
// 					else
// 					{
// 						if(! aux.compare("-t"))
// 						{
// 							*analysis_by_total_energy=true;
// 							*analysis_by_internal_energy=false;
// 						}
// 						else
// 						{
// 							if(! aux.compare("-i"))
// 							{
// 								*analysis_by_total_energy=false;
// 								*analysis_by_internal_energy=true;
// 							}
// 							else
// 							{
// 								if(!aux.compare("-c"))
// 								{
// 									if(i+1<argc)
// 									{
// 										*rmsd_clestering=atof(argv[i+1]);
// 										i++;
// 									}
// 									else
// 									{
// 										if(!aux.compare("-g"))
// 										{
// 											if(i+2 < argc)
// 											{
// 												*only_rmsd_calculation = true;
// 												*rmsd_file1 = argv[i+1];
// 												*rmsd_file2 = argv[i+2];
// 											}
// 											else
// 											{
// 												fprint_help();
// 											}
// 										}	
// 									}
// 								}
// 								else
// 								{
// 									std::cerr<<"[DTSTATISTIC] Unknown parameter "<<aux<<std::endl;
//         							exit(1);
// 								}

// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	if(! aux.compare("-h") || argc==1)	
// 		fprint_help();
// }



void parse(int argc , char * argv[] , std::string *label_name , std::string *directory_name , std::string *output_name , unsigned int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, float *rmsd_clestering, bool *print_help, bool *only_rmsd_calculation, std::string * rmsd_file1, std::string *rmsd_file2)
{
	
	std::string aux;
	for(int i=1;i<argc;i++)
	{
		aux=argv[i];
		if(! aux.compare("-h") || argc==1)
		{
			*print_help=true;
			fprint_help();
		}

		if(! aux.compare("-l") )
		{
			if(i+1<argc)
			{
				*label_name=argv[i+1];
				i++;
				continue;
			}
			else
				fprint_help();
		}

		if(! aux.compare("-d") )
		{
			if(i+1<argc)
			{
				*directory_name=argv[i+1];	
				i++;
				continue;
			}
			else
				fprint_help();
		}

		if(! aux.compare("-o"))
		{
			if(i+1<argc)
			{
				*output_name=argv[i+1];
				i++;
				continue;
			}
			else
				fprint_help();
		}

		if(! aux.compare("-n") )
		{
			if(i+1<argc)
			{
				*number_of_ligands=atoi(argv[i+1]);	
				i++;
				continue;
			}
			else
				fprint_help();
		}

		if(! aux.compare("-t"))
		{
			*analysis_by_total_energy=true;
			*analysis_by_internal_energy=false;
			continue;
		}

		if(! aux.compare("-i"))
		{
			*analysis_by_total_energy=false;
			*analysis_by_internal_energy=true;
			continue;
		}

		if(!aux.compare("-c"))
		{
			if(i+1<argc)
			{
				*rmsd_clestering=atof(argv[i+1]);
				i++;
				continue;
			}
			else
				fprint_help();		
		}

		if(!aux.compare("-g"))
		{
			if(i+2 < argc)
			{
				*only_rmsd_calculation = true;
				*rmsd_file1 = argv[i+1];
				*rmsd_file2 = argv[i+2];
				i++;
				i++;
				continue;
			}
			else
				fprint_help();
		}
		else
		{
			std::cerr<<"[DTSTATISTIC] Unknown parameter "<<aux<<std::endl;
			exit(1);
		}
	}
	
}


void check_flags(const std::string label_name,std::string * directory_name, std::vector<std::string> *log_files, std::vector<std::string> *pdb_files)
{
	if(!directory_name->size() && !label_name.size())
	{
		std::cerr<<"[DTSTATISTIC] At least -l or -d flag should be set."<<std::endl;
		fprint_help();
	}

	/*
	*			Open directory in -d flag
	*/

	if(!directory_name->size())							//If -d flag is not set then, directory = "."
		*directory_name = ".";
	DIR *dir = check_directory(*directory_name);	// Check if exist and return DIR *

	log_files = get_file_list(dir, label_name, ".log");
	pdb_files = get_file_list(dir, label_name, ".pdb");
	for (std::vector<std::string>::iterator it = log_files->begin(); it !=  log_files->end(); it++)
	{
		std::cout<< *it <<std::endl;
	}	
	std::cout << label_name.size() << "\t" << directory_name->size() << std::endl;

}

void fprint_help()
{
	std::cout<<"\
[DTSTATISTIC] Help message\n\n\
Usage: dtstatistic -l <LIGAND_LABEL> -d <DIR> -i  -n 20 -o my_output\n\n\
Parameters: \n\
  -h          		show this help message and exit\n\
  -l name     		set ligand label\n\
  -d name     		set directory name\n\
  -t          		analysis by total energy\n\
  -i          		analysis by interaction energy\n\
  -o name     		output file label (out)\n\
  -n number   		number of ligands to log (10)\n\
  -c number   		clustering rmsd (2.0)\n\
  -g file1 file 	RMSD between file1 and file2\n";

	exit(0);
}	