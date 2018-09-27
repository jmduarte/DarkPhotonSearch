#! /usr/bin/env python
import os
import glob
import math
from array import array
import sys
import time
from optparse import OptionParser
import ROOT

def exec_me(command, dryRun=False):
    print command
    if not dryRun:
        os.system(command)

def justHadd(options,args):    
    DataDir = options.idir
    OutDir = options.idir
    
    EOS = '/usr/bin/eos'
    postfix = ''
    exec_me('mkdir -p $PWD/hadd_jobs/',options.dryRun)
    exec_me('%s mkdir -p /%s/hadd'%(EOS,OutDir),options.dryRun)

    label = options.label

    basename = label + '.root'
    
    filesToConvert = []
    badFiles = []
    filesToConvert, badFiles = getFilesRecursively(DataDir,label+'/',None,'failed')
    print "files To Convert = ",filesToConvert
    print "bad files = ", badFiles
    cwd = os.getcwd()

    haddAll = False
    haddOutExistsList = []
    haddOutList = []
    for i in range(0,len(filesToConvert)/500+1):
        if not os.path.isfile(OutDir+'/hadd/'+basename.replace('.root','_%i.root'%i)):
            haddOutExistsList.append(False)
            haddOutList.append(OutDir+'/hadd/'+basename.replace('.root','_%i.root'%i))
            haddCommand = '#!/bin/bash\n'
            haddCommand += 'pwd\n'
            haddCommand += 'cd %s\n'%cwd
            haddCommand += 'pwd\n'
            haddCommand += 'eval `scramv1 runtime -sh`\n'
            haddCommand += 'cd -\n'
            haddCommand += 'pwd\n'
            haddCommand += 'mkdir -p $PWD/hadd\n'        
            haddCommand += 'hadd -f hadd/%s %s\n'%(basename.replace('.root','_%i.root'%i),(' '.join(filesToConvert[i*500:(i+1)*500])).replace('eos','root://eoscms.cern.ch//eos'))
            haddCommand += '%s cp $PWD/hadd/%s /%s/hadd/%s\n'%(EOS,basename.replace('.root','_%i.root'%i),OutDir,basename.replace('.root','_%i.root'%i))
            haddCommand += 'rm -r $PWD/hadd\n'
            with open('hadd_jobs/hadd_command_%s.sh'%(basename.replace('.root','_%i.root'%i)),'w') as f:
                f.write(haddCommand)
            exec_me('bsub -q 8nh -o $PWD/hadd_jobs/hadd_command_%s.log source $PWD/hadd_jobs/hadd_command_%s.sh'%(basename.replace('.root','_%i.root'%i),basename.replace('.root','_%i.root'%i)),options.dryRun)
        else:
            haddOutExistsList.append(True)
            haddOutList.append(OutDir+'/hadd/'+basename.replace('.root','_%i.root'%i))
                
    haddAll = all(haddOutExistsList)

    print 'haddAll', haddAll
    print 'haddOutExistsList', haddOutList
    print 'haddOutList', haddOutList
        
    if haddAll:
        haddCommand = '#!/bin/bash\n'
        haddCommand += 'pwd\n'
        haddCommand += 'cd %s\n'%cwd
        haddCommand += 'pwd\n'
        haddCommand += 'eval `scramv1 runtime -sh`\n'
        haddCommand += 'cd -\n'
        haddCommand += 'pwd\n'
        haddCommand += 'mkdir -p $PWD/hadd\n'        
        haddCommand += 'hadd -f hadd/%s %s\n'%(basename,(' '.join(haddOutList)).replace('eos','root://eoscms.cern.ch//eos'))
        haddCommand += '%s cp $PWD/hadd/%s /%s/hadd/%s\n'%(EOS,basename,OutDir,basename)
        haddCommand += 'rm -r $PWD/hadd\n'
        with open('hadd_jobs/hadd_command_%s.sh'%(basename),'w') as f:
            f.write(haddCommand)
            exec_me('bsub -q 8nh -o $PWD/hadd_jobs/hadd_command_%s.log source $PWD/hadd_jobs/hadd_command_%s.sh'%(basename,basename),options.dryRun)
            

def getFilesRecursively(dir, searchString, additionalString = None, skipString = None):
    
    cfiles = []
    badfiles = []
    for root, dirs, files in os.walk(dir+'/'+searchString):
        if skipString is not None and skipString in root: continue

        nfiles = len(files)
        for ifile, file in enumerate(files):
            
            if ifile%100==0:
                print '%i/%i files checked in %s'%(ifile,nfiles,root)
            if skipString is not None and skipString in file: 
                print 'skipping %s due to skipString %s'%(file, skipString)
                continue            
            if '.root' not in file:
                print 'skipping %s'%(file)
                continue            
            try:
                #f = ROOT.TFile.Open((os.path.join(root, file)).replace('eos','root://eoscms.cern.ch//eos'))
                f = ROOT.TFile.Open((os.path.join(root, file)))
                if f.IsZombie():
                    print 'file is zombie'
                    f.Close()
                    badfiles.append(os.path.join(root, file))                    
                    continue
                elif not f.Get('demo/tree'):
                    print 'tree is false'
                    f.Close()
                    badfiles.append(os.path.join(root, file))                    
                    continue
                elif not f.Get('demo/tree').InheritsFrom('TTree'):
                    print 'tree is not a tree'
                    f.Close()
                    badfiles.append(os.path.join(root, file))                    
                    continue
                else:
                    f.Close()
                    cfiles.append(os.path.join(root, file))                    
            except:
                print 'could not open file or tree'
                badfiles.append(os.path.join(root, file))                    
                continue
                
    return cfiles, badfiles



if __name__ == '__main__':

    parser = OptionParser()
    parser.add_option('-i','--idir', dest='idir', default = 'data/',help='directory with bacon bits', metavar='idir')
    parser.add_option('-j','--job', dest='job', default =-1,type='int',help='just do part of it', metavar='idir')
    parser.add_option('-l','--label',dest="label", default="All",type='string',
                      help="label name")
    parser.add_option('--dry-run',dest="dryRun",default=False,action='store_true',
                  help="Just print out commands to run")
    (options, args) = parser.parse_args()

    
    justHadd(options,args)

    
