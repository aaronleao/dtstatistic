#include "parsing.h"

void parse(int argc,char * argv[],std::string *label_name, std::string *output_name, int *number_of_ligands, bool *analysis_by_total_energy, bool *analysis_by_internal_energy, bool *print_help)
{
	
	std::string aux;
	for(int i=0;i<argc;i++)
	{
		aux=argv[i];
		if(! strcmp(argv[i],"-h")|| argc==1)
		{
			*print_help=true;
		}
		if(i+1<argc)
		{

			if(! strcmp(argv[i],"-l") )
			{
				*label_name=argv[i+1];
				//i++;
			}
		
			if(! strcmp(argv[i],"-o"))
			{
				*output_name=argv[i+1];
				//i++;
			}
			if(! strcmp(argv[i],"-n") )
			{
				*number_of_ligands=atoi(argv[i+1]);
				//i++;
			}

			if(! strcmp(argv[i],"-t"))
			{
				*analysis_by_total_energy=true;
				*analysis_by_internal_energy=false;
			}
			if(! strcmp(argv[i],"-i"))
			{
				*analysis_by_total_energy=false;
				*analysis_by_internal_energy=true;
			}
		}
	}

}

void fprint_help()
{
	std::cout<<"\
[DTSTATISTIC] Help message\n\n\
Usage: dtstatistic -l dir/ -i  -n 20 -o my_output\n\n\
Parameters: \n\
  -h          show this help message and exit\n\
  -l name     set label name\n\
  -t          analysis by total energy\n\
  -i          analysis by interaction energy\n\
  -o name     output file label (out)\n\
  -n number   number of ligands to log (10)\n";
	exit(0);
}	