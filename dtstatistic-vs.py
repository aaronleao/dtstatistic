#!/usr/bin/python    

'''
Created on 19/06/2012

@author: diogo
'''

from openbabel import OBConversion, OBMol
import math
import optparse
import os
import re
import sys


class Molecula(OBMol): #heranca de OBMol
    def setIDLog(self, id_log):
        self.id_log = id_log
        
    def setFileBelow(self, file_below):
        self.file_below = file_below
    
    def setTotalEnergy(self, totalenergy):
        self.totalenergy = float(totalenergy)
        
    def setInteractionEnergy(self):
        self.interaction_energy = self.vdw + self.coulomb
        
    def setCoulomb(self, coulomb):
        self.coulomb = float(coulomb)
                   
    def setVdw(self, vdw):
        self.vdw = float(vdw)
            
    def getCoulomb(self):
        return self.coulomb
                   
    def getVdw(self):
        return self.vdw
        
    def getID(self):
        return self.id_log
        
    def getFileBelow(self):
        return self.file_below
    
    def getTotalEnergy(self):
        return float(self.totalenergy)
        
    def getInteractionEnergy(self):
        return float(self.interaction_energy)
    
    def log(self):
        
        print "ID " + str(self.id_log) 
        print "Interaction Energy %3.3f" % (float(self.vdw) + float(self.coulomb))
        print "Total Energy %3.3f" % float(self.totalenergy)
        print "File %s" % self.file_below 


def searchFiles():

    files = os.listdir('.')

    file_list = []
    
    for f in files:
        if re.search("_run_1.log$", f):            
            tokz = f.split('_run_')
            file_list.append(str(tokz[0]))
            
            
    return  file_list


def discoverNumberOfRuns():

    files = os.listdir('.')

    file_list = []
    
    for f in files:
        if re.search(".log$", f):
            
            tokz = f.split('.')
            
            if tokz[1] == "log":
                file_list.append(tokz[0])
                
    integer_list = []
    
    
    for f in file_list:
        
        m = (re.search("[\d+]*$", f))
        
        if m!=None:
            integer_list.append(int(m.group(0)))
        
    
    integer_list = sorted(integer_list)    
    
    return integer_list.pop()


def getListByLigand(f, nruns):
        
    mol_list = []
    
    for i in range(1, nruns+1):
            
        file_log_name =  f +"_run_"+str(i)+".log"
        
        file_log = open(file_log_name)
        
        mol = Molecula()
        
        
        for lines in file_log:
            if re.search("^\$Leader_Info", lines) is not None:
                
                mol.setIDLog( int( re.search("\d+", lines).group(0)) )
            elif re.search("Total_Energy", lines) is not None:
                mol.setTotalEnergy( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("vdW", lines) is not None:
                mol.setVdw( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("Coulomb", lines) is not None:
                mol.setCoulomb( float(re.search(".\d+.\d+", lines).group(0)) )
                                
            elif re.search("^}", lines) is not None:
                            
                mol.setFileBelow(file_log_name)
                
                mol.setInteractionEnergy()

                mol_list.append(mol)
                    
    return mol_list

def load_conformation(mol_list):
    
    for mol in mol_list:
        
        file_name = mol.getFileBelow().split('.')[0] + ".pdb"
        
#########################################################
#Substiuir esses passos para remocao do openbabel ######              
        conv = OBConversion()
        
        conv.SetInFormat("pdb")
             
        end = conv.ReadFile(mol, file_name)
                
        for i in range(1, int(mol.getID())):            
            mol = Molecula()
            
            end = conv.Read(mol)
            

def getNumSolutions(log_file):
    
    n = 1
    
    f = open(log_file)

    for lines in f:
        if re.search("^\$Number_of_Clusters", lines) is not None:
            n =  int( re.search("\d+", lines).group(0))
            break
        
    f.close()

    return n


#ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# |    
def pivot_energy(v, left, right):
    i = left
    for j in range(left + 1, right + 1):
        if v[j].getTotalEnergy() < v[left].getTotalEnergy():
            i += 1 # .. incrementa-se i
            v[i], v[j] = v[j], v[i]
    v[i], v[left] = v[left], v[i]
    return i

def qsort_energy(v, left, right):
    if right > left:
        r = pivot_energy(v, left, right)
        qsort_energy(v, left, r - 1)
        qsort_energy(v, r + 1, right)
        
        
def pivot_ienergy(v, left, right):
    i = left
    for j in range(left + 1, right + 1):
        if v[j].getInteractionEnergy() < v[left].getInteractionEnergy():
            i += 1 # .. incrementa-se i
            v[i], v[j] = v[j], v[i]
    v[i], v[left] = v[left], v[i]
    return i

def qsort_ienergy(v, left, right):
    if right > left:
        r = pivot_ienergy(v, left, right)
        qsort_ienergy(v, left, r - 1)
        qsort_ienergy(v, r + 1, right)


#ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# #ORDENACAO# |    


def getRMSD(mol1, mol2):
    
    natoms = 0.0

    xx = 0.0
    yy = 0.0
    zz = 0.0
        
    for i in range(0, mol1.NumAtoms()):
    
        atom1 = mol1.GetAtom(i+1)
    
        atom2 = mol2.GetAtom(i+1)
        
        if not(atom1.IsHydrogen()):
            x = atom1.GetX() - atom2.GetX()
            y = atom1.GetY() - atom2.GetY()
            z = atom1.GetZ() - atom2.GetZ()
    
            xx += (x*x)
            yy += (y*y)
            zz += (z*z)
    
            natoms+= 1.0
            
    return math.sqrt( (xx+yy+zz)/natoms )


def log_new_clusters(output_file, n, leader_list):
    
    print "log %d ligands. For change this number set the -n parameter" % n 
    
    str_info = "\t%s\t  \t%20s\t %20s\t %20s\n" % ("File", "Model", "T.Energy", "I.Energy")
    
    for i in range(0, n):
        str_info+="%s\t%20s\t%20s\t%20s\n" % (leader_list[i].getFileBelow().split('/').pop(), leader_list[i].getID(), 
                                                      leader_list[i].getTotalEnergy(), leader_list[i].getInteractionEnergy())

    out_log = file(output_file+".log", "w")
    
    out_log.write(str_info)
    
    out_log.close()
    
    conv = OBConversion()
    
    conv.SetOutFormat("mol2")
    
    conv.WriteFile(leader_list[0], output_file + ".mol2")
    

    for i in range(1, n):
        conv.Write(leader_list[i])
        
    conv.CloseOutFile()


def main(): 
    
    strinfo = '''
            dtstatistic -l dir/ -i -n 20 -o my_output
    '''
    
    p = optparse.OptionParser(strinfo)
    
    p.add_option("-l",  type="string", help="set label name", metavar="name")
    
    p.add_option("-t", help="analysis by total energy", action="store_true", default=True)
    
    p.add_option("-i", help="analysis by interaction energy", action="store_false", default=True)
    
    p.add_option("-o",  type="string", help="output file label (out)", metavar="name", default="out")
    
    p.add_option("-n",  type="int", help="number of ligands to log (10)", metavar="number", default=10)
    
            
    (options, args) = p.parse_args()
    
 
    if len(sys.argv) == 1:
        p.print_help()
        sys.exit()

    mol_list = []

    if options.l!=None:
        
        os.chdir(options.l)
        
        base_file_list = searchFiles()
        
        nruns = discoverNumberOfRuns()
        print nruns
        for f in base_file_list:
            
            mol_list_aux = getListByLigand(f, nruns)#lista do mesmo ligante de diferentes runs
    
            if not(options.i):#ordena as conformacoes do mesmo ligantes de diferentes runs
                
                qsort_energy(mol_list_aux, 0, len(mol_list_aux)-1)
                
            else:
                qsort_ienergy(mol_list_aux, 0, len(mol_list_aux)-1)
                
            
            mol_list.append(mol_list_aux[0])#seleciona a melhor conformacao
        
    
        load_conformation(mol_list)
    
        if not(options.i):#ordena as conformacoes do mesmo ligantes de diferentes runs        
            qsort_ienergy(mol_list, 0, len(mol_list)-1)
            
        else:
            qsort_energy(mol_list, 0, len(mol_list)-1)
    
            
        n = options.n
        
        if n > len(mol_list):
            n = len(mol_list)
    
        log_new_clusters(options.o, n, mol_list)
        
    else:
        print "No analyses was done, bye"
        sys.exit()

#    print searchFiles(options.l)
    
#    if options.l!=None:
#        
#        mol_list_aux = getLigandList(searchFiles(options.l))
#        
#        print "Loading %d conformers" % len(mol_list_aux)
#        
#        leader_list = []
#        
#        if not(options.i):
#            leader_list = clustering(mol_list_aux,options.c, options.i)
#                
#        elif options.t:
#            leader_list = clustering(mol_list_aux,options.c, options.t)
#            
#        else:
#            print "You need choose a option of clustering, -t or -i, bye"
#            sys.exit()
#        
#        n = options.n
#        
#        if n > len(leader_list):
#            n = len(leader_list)
#        
#        
#        print "Number of clusters is %d" % len(leader_list)
#
#        log_new_clusters(options.o, n, leader_list, options.r)
#        
#                    
#        if options.s != None and options.r != None:
#            rate_of_sucess(options.s, searchFiles(options.l), options.r)
#        
#    else:
#        print "No analyses was done, bye"
#        sys.exit()


if __name__ == '__main__':
    main()
    print 'End.' 
