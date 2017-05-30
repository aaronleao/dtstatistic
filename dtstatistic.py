#!/usr/bin/python2

'''
Created on 19/06/2012

@author: diogo
'''

import math
import sys
import optparse
import os
from openbabel import OBConversion, OBMol
import re
import time

def clustering1(mol_list, RMSD_PARAMETER, type,nmax):
        
    if type:
        print "clustering by total energy"
        start_time = time.time()
        qsort_energy(mol_list, 0, len(mol_list) - 1)
        elapsed_time = time.time() - start_time
        print("CLUSTERING_t_qsort: %f"%elapsed_time)
        
    else:
        print "clustering by interaction energy"
        start_time = time.time()
        qsort_ienergy(mol_list, 0, len(mol_list) - 1)
        elapsed_time = time.time() - start_time
        print("CLUSTERING_i_qsort: %f"%elapsed_time)


    print "CLUSTERING_for"
    start_time = time.time()
   


    pivot = mol_list[0]
    leader_list = []
    ncluster = 0
    
   
    for i in range(1, len(mol_list)):
        aux=getRMSD(pivot, mol_list[i]) 
        if aux > float(RMSD_PARAMETER) and ncluster <= nmax:
            leader_list.append(pivot)
            ncluster = ncluster+1
            pivot = mol_list[i]


    elapsed_time = time.time() - start_time
    print("CLUSTERING_for: %f"%elapsed_time)
   
   

    return leader_list

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


def searchFiles(label):

    files = os.listdir('.')

    file_list = []
    
    for f in files:
        
        if re.search("^"+label+"_", f):
            #print("searchFiles: %s"%f)
            tokz = f.split('.')
            
            if tokz[1] == "log":
                file_list.append(tokz[0])

    
    return  file_list


def getLigandList(list_files):

    obmol_list = []
    
    for f in list_files:        
        
        mol = Molecula()
        
#########################################################
#Substiuir esses passos para remocao do openbabel ######       
        pdb_file_name = f + ".pdb"
        
        conv = OBConversion()
        
        conv.SetInFormat("pdb")
             
        end = conv.ReadFile(mol, pdb_file_name)
        
        obmol_list.append(mol)
        
        while end:
            
            mol = Molecula()
            
            end = conv.Read(mol)
            
            obmol_list.append(mol)

        obmol_list.pop()    #retira a ultima molecula
        
###########################################################  
##### Etapa de busca da informacao da energia #############

    j = 0
    
    for f in list_files:
        
        log_file_name = f + ".log"
        file_log = open(log_file_name)

                
        for lines in file_log:
            if re.search("^\$Leader_Info", lines) is not None:
                aux=int( re.search("\d+", lines).group(0))
                obmol_list[j].setIDLog( aux )
                
            elif re.search("Total_Energy", lines) is not None:
                obmol_list[j].setTotalEnergy( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("vdW", lines) is not None:
                obmol_list[j].setVdw( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("Coulomb", lines) is not None:
                obmol_list[j].setCoulomb( float(re.search(".\d+.\d+", lines).group(0)) )
                                
            elif re.search("^}", lines) is not None:
                            
                obmol_list[j].setFileBelow(log_file_name)
                
                obmol_list[j].setInteractionEnergy()

                j+=1
                            
        file_log.close()
    return obmol_list




def getLigandListRMSD(list_files, ref):
    
    obmol_list = []
    
    rmsd_list = []
    
    j = 0
    
    for f in list_files:        

        mol = Molecula()
        
#########################################################
#Substiuir esses passos para remocao do openbabel ######       
        pdb_file_name = f + ".pdb"
        
        conv = OBConversion()
        
        conv.SetInFormat("pdb")
             
        end = conv.ReadFile(mol, pdb_file_name)
        obmol_list.append(mol)
        
        
        while end:
            
            mol = Molecula()
            
            end = conv.Read(mol)
            
            obmol_list.append(mol)

        obmol_list.pop()    #retira a ultima molecula
        
###########################################################  
##### Etapa de busca da informacao da energia #############

    
        log_file_name = f + ".log"
                
        file_log = open(log_file_name)

                
        for lines in file_log:
            if re.search("^\$Leader_Info", lines) is not None:
                obmol_list[j].setIDLog( int( re.search("\d+", lines).group(0)) )
                
            elif re.search("Total_Energy", lines) is not None:
                obmol_list[j].setTotalEnergy( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("vdW", lines) is not None:
                obmol_list[j].setVdw( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("Coulomb", lines) is not None:
                obmol_list[j].setCoulomb( float(re.search(".\d+.\d+", lines).group(0)) )
                                
            elif re.search("^}", lines) is not None:
                            
                obmol_list[j].setFileBelow(log_file_name)
                
                obmol_list[j].setInteractionEnergy()

                j+=1
        
        qsort_RMSD(obmol_list, 0, len(obmol_list)-1, ref)
        
        rmsd_list.append(obmol_list[0])
        
        obmol_list = []
                       
        file_log.close()
        
        j = 0
        
    
    qsort_RMSD(rmsd_list, 0, len(rmsd_list)-1, ref)
                                      
    return rmsd_list


def getLigandListLeaders(list_files):
    
    obmol_list = []
    
    for f in list_files:        
        
        mol = Molecula()
        
#########################################################
#Substiuir esses passos para remocao do openbabel ######       
        pdb_file_name = f+".pdb"
        
        conv = OBConversion()
        
        conv.SetInFormat("pdb")
             
        end = conv.ReadFile(mol, pdb_file_name)
        
        obmol_list.append(mol)
        
        
###########################################################  
##### Etapa de busca da informacao da energia #############

    j = 0
    
    for f in list_files:
        
        log_file_name = f + ".log"
                
        file_log = open(log_file_name)

                
        for lines in file_log:
            if re.search("^\$Leader_Info", lines) is not None:
                aux=int( re.search("\d+", lines).group(0))
                obmol_list[j].setIDLog( aux )
                
            elif re.search("Total_Energy", lines) is not None:
                obmol_list[j].setTotalEnergy( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("vdW", lines) is not None:
                obmol_list[j].setVdw( float(re.search(".\d+.\d+", lines).group(0)) )
            
            elif re.search("Coulomb", lines) is not None:
                obmol_list[j].setCoulomb( float(re.search(".\d+.\d+", lines).group(0)) )
                                
            elif re.search("^}", lines) is not None:
                            
                obmol_list[j].setFileBelow(log_file_name)
                
                obmol_list[j].setInteractionEnergy()
                
                break

        j+=1
                            
        file_log.close()
                                                      
    return obmol_list


def getNumSolutions(log_file):
    
    n = 1
    
    f = open(log_file)

    for lines in f:
        if re.search("^\$Number_of_Clusters", lines) is not None:
            n =  int( re.search("\d+", lines).group(0))
            break
        
    f.close()

    return n


def loadReferenceMolecule(file_name):
    
        ext = file_name.split(".")[1]
    
        mol = Molecula() 
        
        conv = OBConversion()
        
        conv.SetInFormat(ext)
             
        conv.ReadFile(mol, file_name)    
        
        return mol


def clustering(mol_list, RMSD_PARAMETER, type):
        
    if type:
        print "clustering by total energy"
        start_time = time.time()
        qsort_energy(mol_list, 0, len(mol_list) - 1)
        elapsed_time = time.time() - start_time
        print("CLUSTERING_t_qsort: %f"%elapsed_time)
        
    else:
        print "clustering by interaction energy"
        start_time = time.time()
        qsort_ienergy(mol_list, 0, len(mol_list) - 1)
        elapsed_time = time.time() - start_time
        print("CLUSTERING_i_qsort: %f"%elapsed_time)


   
    leader_list = []
    leader_list.append(mol_list[0])
   
    ncluster = 1


    start_time = time.time()
    for i in range(1, len(mol_list)):
        count = 0
        
        for j in range(len(leader_list)):
            aux=getRMSD(leader_list[j], mol_list[i])
            if aux > float(RMSD_PARAMETER):
                count+=1

        if count == ncluster:
            
            ncluster+=1
            
            leader_list.append(mol_list[i])

    elapsed_time = time.time() - start_time
    print("CLUSTERING_for: %f"%elapsed_time)
    
    return leader_list


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

def pivot_RMSD(v, left, right, ref):
    i = left
    for j in range(left + 1, right + 1):
        if getRMSD(v[j], ref) < getRMSD(v[left], ref):
            i += 1 # .. incrementa-se i
            v[i], v[j] = v[j], v[i]
    v[i], v[left] = v[left], v[i]
    return i

def qsort_RMSD(v, left, right, ref):
    if right > left:
        r = pivot_RMSD(v, left, right, ref)
        qsort_RMSD(v, left, r - 1, ref)
        qsort_RMSD(v, r + 1, right, ref)

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


def log_new_clusters(output_file, n, leader_list, ref=None):
    
    print "log %d ligands. For change this number set the -n parameter" % n 
    
    str_info = "\t%s\t  %20s\t %20s\t %20s \t%15s\n" % ("File", "Model", "T.Energy", "I.Energy", "RMSD")
    
    if ref != None:
        mol_ref = loadReferenceMolecule(ref)
    
    if ref != None:
        for i in range(0, n):
            str_info+="%s\t%20s\t%20s\t%20s\t%15.3f\n" % (leader_list[i].getFileBelow(), leader_list[i].getID(), leader_list[i].getTotalEnergy(), leader_list[i].getInteractionEnergy(), getRMSD(leader_list[i], mol_ref))
    else:
        for i in range(0, n):
            str_info+="%s\t%20s\t%20s\t%20s\t%15.3f\n" % (leader_list[i].getFileBelow(), leader_list[i].getID(), leader_list[i].getTotalEnergy(), leader_list[i].getInteractionEnergy(), getRMSD(leader_list[i], leader_list[0]))


    out_log = file(output_file+".log", "w")
    
    out_log.write(str_info)
    
    out_log.close()
    
    conv = OBConversion()
    
    conv.SetOutFormat("mol2")
    
    conv.WriteFile(leader_list[0], output_file + ".mol2")
    

    for i in range(1, n):
        conv.Write(leader_list[i])
        
    conv.CloseOutFile()


def sucess_analyses(output, leader_list, n, ref):

    print "Calculating RMSD with the reference"
    
    ext = ref.split(".")[1]
    
    conv = OBConversion()
        
    conv.SetInFormat(ext)
    
    mol = OBMol()
    
    conv.ReadFile(mol, ref)
            
    str_info = "\t%s\t  %20s\t %20s\n" % ("File", "Model", "RMSD")
    
    
    for i in range(0, n):
        
        rmsd = getRMSD(leader_list[i], mol)
        
        str_info+="%s\t%20s    \t%20.3f\n" % (leader_list[i].getFileBelow(), leader_list[i].getID(), rmsd)


    out_log = file(output+"_rmsd_"+".info", "w")
    
    out_log.write(str_info)
    
    out_log.close()

    
def calcRMSD(a, b):
    
    mol1 = loadReferenceMolecule(a)
    
    mol2 = loadReferenceMolecule(b)
    
    print "RMSD: %3.5f" % getRMSD(mol1, mol2)
    

def rate_of_sucess(v, list_files, ref):
    
    l = getLigandListLeaders(list_files)
    
    mol2 = loadReferenceMolecule(ref)
    
    qsort_energy(l, 0, len(l)-1) 
    
    s = 0.0
    
    print "\nRate Sucess of Best Energy:"
    print "    %s\t   %20s\t %20s \t%15s" % ("File", "T.Energy", "I.Energy", "RMSD")
    
    for i in range (0, len(l)):
        
        rmsd = getRMSD(l[i], mol2)
        
        print "%s\t %20s\t%20s\t%15.3f" % (l[i].getFileBelow(), l[i].getTotalEnergy(), l[i].getInteractionEnergy(), getRMSD(l[i], mol2))
         
        if rmsd < float(v):
            s +=1.0

    str="%"    
    
    print "sucess rate with best energy criterion is %3.2f%s and has RMSD of %3.2f" % (((s/float(len(l))) * 100.0), str, (getRMSD(l[0], mol2)))
    
    
    list_rmsd = getLigandListRMSD(list_files, mol2)

    print "\nRate Sucess of Low RMSD:"
    
    print "    %s\t   %20s\t %20s \t%15s" % ("File", "T.Energy", "I.Energy", "RMSD")
    
    s = 0.0
    
    for i in range (0, len(list_rmsd)):
        
        rmsd = getRMSD(list_rmsd[i], mol2)
        
        print "%s\t %20s\t%20s\t%15.3f" % (list_rmsd[i].getFileBelow(), list_rmsd[i].getTotalEnergy(), list_rmsd[i].getInteractionEnergy(), getRMSD(list_rmsd[i], mol2))
         
        if rmsd < float(v):
            s +=1.0

    str="%"    
    
    print "sucess rate with low RMSD criterion is %3.2f%s and has RMSD of %3.2f" % (((s/float(len(list_rmsd))) * 100.0), str, (getRMSD(list_rmsd[0], mol2)))
    
    

def main(): 
    
    strinfo = '''
            dtstatistic -l lig -i -n 20 -o my_output
    '''
    
    p = optparse.OptionParser(strinfo)
    
    p.add_option("-l",  type="string", help="set label name", metavar="name")
    
    p.add_option("-t", help="analysis by total energy", action="store_true", default=True)
    
    p.add_option("-i", help="analysis by interaction energy", action="store_false", default=True)
    
    p.add_option("-r",  type="string", help="reference file for rmsd", metavar="name")
    
    p.add_option("-c", type="float", help="cluster parameter (2.0)", metavar="number", default = 2.0)

    p.add_option("-o",  type="string", help="output file label (out)", metavar="name", default="out")
    
    p.add_option("-n",  type="int", help="number of ligands to log (10)", metavar="number", default=10)
    
    p.add_option("-g", type="string",nargs=2 ,help="calc rmsd for two ligands", metavar="file1 file2")
    
    p.add_option("-s", help="sucess rate of runs", type="float" , metavar="number")

        
    (options, args) = p.parse_args()
    
 
    if len(sys.argv) == 1:
        p.print_help()
        sys.exit()
        
    
    mol_list = []
    
    if options.g!=None:
        calcRMSD(options.g[0], options.g[1])
    


    


    if options.l!=None:
        
        start_time = time.time()
        array=searchFiles(options.l)
        elapsed_time = time.time() - start_time
        print("SEARCH FILES: %f"%elapsed_time)
        
        start_time = time.time()
        mol_list = getLigandList(array)
        elapsed_time = time.time() - start_time
        print("GET LIGAND LIST: %f"%elapsed_time)
        
        print "Loading %d conformers" % len(mol_list)
        
        leader_list = []
        
        if not(options.i):
            start_time = time.time()
            leader_list = clustering(mol_list,options.c, options.i)
            elapsed_time = time.time() - start_time
            print("CLUSTERING_i: %f"%elapsed_time)
        
                
        elif options.t:
            start_time = time.time()
            leader_list = clustering1(mol_list,options.c, options.t,options.n)
            #leader_list = clustering(mol_list,options.c, options.t)
            elapsed_time = time.time() - start_time
            print("CLUSTERING_t: %f"%elapsed_time)

            
        else:
            print "You need choose a option of clustering, -t or -i, bye"
            sys.exit()
        
        n = options.n
        
        if n > len(leader_list):
            n = len(leader_list)
        
        
#        print "Number of clusters is %d" % len(leader_list)

        log_new_clusters(options.o, n, leader_list, options.r)
        
                    
        if options.s != None and options.r != None:
            rate_of_sucess(options.s, searchFiles(options.l), options.r)
        
    else:
        print "No analyses was done, bye"
        sys.exit()


if __name__ == '__main__':
    start_time = time.time() 
    main()
    elapsed_time = time.time() - start_time
    print("TOTAL_TIME: %f"%elapsed_time)
    print 'End.' 
