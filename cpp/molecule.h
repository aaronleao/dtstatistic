#include <openbabel/obconversion.h>
#include <vector>
#include <boost/algorithm/string.hpp>

// void print( std::vector <std::string> v )
// {
//   for (size_t n = 0; n < v.size(); n++)
//     std::cout << "\"" << v[ n ] << "\"\n";
//   std::cout << std::endl;
// }

int mol2_converter(std::vector<std::string>  *pdb_files)
{

	//OpenBabel::OBConversion conv(in, out);
	
	std::string aux;
	for (std::vector<std::string>::iterator it = pdb_files->begin(); it != pdb_files->end(); ++it)
    {
		aux=*it;
		std::string mol2_name = aux.substr(0, aux.find(".pdb"));
		mol2_name=mol2_name+".mol2";
		std::cout<<"NOME: "<<mol2_name<<std::endl;
	}
}