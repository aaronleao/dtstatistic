#include "parsing.h"

void parse(int argc , char * argv[] , std::string *label_name , std::string *path_name , std::string *output_name , unsigned int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, float *rmsd_clestering, bool *print_help, bool *only_rmsd_calculation, std::string * rmsd_file1, std::string *rmsd_file2)
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

		if(! aux.compare("-d") )
		{
			if(i+1<argc)
			{
				*path_name=argv[i+1];	
				i++;
			}
			else
				fprint_help();
		}
		else
		{
			if(! aux.compare("-l") )
			{
				if(i+1<argc)
				{
					*label_name=argv[i+1];
					i++;
				}
				else
					fprint_help();
			}
			else
			{
				if(! aux.compare("-o"))
				{
					if(i+1<argc)
					{
						*output_name=argv[i+1];
						i++;
					}
					else
						fprint_help();
				}
				else
				{
					if(! aux.compare("-n") )
					{
						if(i+1<argc)
						{
							*number_of_ligands=atoi(argv[i+1]);	
							i++;
						}
						else
							fprint_help();
					}
					else
					{
						if(! aux.compare("-t"))
						{
							*analysis_by_total_energy=true;
							*analysis_by_internal_energy=false;
						}
						else
						{
							if(! aux.compare("-i"))
							{
								*analysis_by_total_energy=false;
								*analysis_by_internal_energy=true;
							}
							else
							{
								if(!aux.compare("-c"))
								{
									if(i+1<argc)
									{
										*rmsd_clestering=atof(argv[i+1]);
										i++;
									}
									else
									{
										if(!aux.compare("-g"))
										{
											if(i+2 < argc)
											{
												*only_rmsd_calculation = true;
												*rmsd_file1 = argv[i+1];
												*rmsd_file2 = argv[i+2];
											}
										}
										else
											fprint_help();
									}
								}
								else
								{
									std::cerr<<"[DTSTATISTIC] Unknown parameter "<<aux<<std::endl;
        							exit(1);
								}

							}
						}
					}
				}
			}
		}
	}
	if(! aux.compare("-h") || argc==1)	
		fprint_help();
}

void fprint_help()
{
	std::cout<<"\
[DTSTATISTIC] Help message\n\n\
Usage: dtstatistic -l <LABEL> -d <DIR> -i  -n 20 -o my_output\n\n\
Parameters: \n\
  -h          show this help message and exit\n\
  -l name     set label name\n\
  -t          analysis by total energy\n\
  -i          analysis by interaction energy\n\
  -o name     output file label (out)\n\
  -n number   number of ligands to log (10)\n\
  -c number   clustering rmsd (2.0)\n";
	exit(0);
}	