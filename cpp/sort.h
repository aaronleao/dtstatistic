#include <vector>
#include "molecule.h"
#include <algorithm>


bool sort_by_total_energy(molecule *i , molecule *j);
bool sort_by_interaction_energy(molecule *i , molecule *j);
void sort_molecule(std::vector<molecule *> *aux,bool total_energy);
