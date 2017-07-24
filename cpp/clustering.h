#include <vector>
#include "molecule.h"
#include "rmsd.h"

std::vector<molecule*> *clustering(std::vector<molecule*> molecules , float rmsd_clustering=2.0);