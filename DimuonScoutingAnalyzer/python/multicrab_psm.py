##########################
# #
# HLTPhysics Run2017A #
# #
##########################


if __name__ == '__main__':
    from CRABAPI.RawCommand import crabCommand

    def submit(config):
        res = crabCommand('submit', config = config)

    from CRABClient.UserUtilities import config
    config = config()

    dataset = {
        'ParkingScoutingMonitor-Run2017D-PromptReco-v1' : '/ParkingScoutingMonitor/Run2017D-PromptReco-v1/MINIAOD',
        'ParkingScoutingMonitor-Run2017E-PromptReco-v1' : '/ParkingScoutingMonitor/Run2017E-PromptReco-v1/MINIAOD',
        'ParkingScoutingMonitor-Run2017F-PromptReco-v1' : '/ParkingScoutingMonitor/Run2017F-PromptReco-v1/MINIAOD',
        }
    parent = {
        'ParkingScoutingMonitor-Run2017D-PromptReco-v1' : '/ParkingScoutingMonitor/Run2017D-v1/RAW',
        'ParkingScoutingMonitor-Run2017E-PromptReco-v1' : '/ParkingScoutingMonitor/Run2017E-v1/RAW',
        'ParkingScoutingMonitor-Run2017F-PromptReco-v1' : '/ParkingScoutingMonitor/Run2017F-v1/RAW',
        }       
        
    nfiles = -1 
    filesPerJob = 10
    masks = {
        #'Golden' : '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-301997_13TeV_PromptReco_Collisions17_JSON.txt',
        'DCSonly' : '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/DCSOnly/json_DCSONLY.txt'
        }
    
    for key, mask in masks.iteritems():
        config.General.transferLogs = True
        
        config.JobType.maxMemoryMB = 2500
        #config.JobType.numCores = 4

        name = 'ScoutingDQMv9'
        config.General.workArea = 'crab_'+name+'_'+key
        config.General.transferLogs = True
        config.JobType.pluginName = 'Analysis'
        config.JobType.psetName = 'ConfFile_cfg.py'
        config.Data.inputDBS = 'global'
        config.Data.splitting = 'LumiBased'
        config.Data.publication = True
        config.JobType.outputFiles = ['AnalysisOutput.root']
        #config.JobType.pyCfgParams = running_options
        config.Site.storageSite = 'T3_US_FNALLPC' # change this depending on where you want to store things
        config.Data.ignoreLocality = True #Required for CAF submission
        #config.Site.whitelist = ['T3_CH_CERN_CAF'] #Required for CAF submission
        #config.Site.ignoreGlobalBlacklist = True #Required for CAF submission
        
        listOfSamples = dataset.keys()
        for sample in listOfSamples:
            config.General.requestName = sample
            config.Data.inputDataset = dataset[sample]
            config.Data.secondaryInputDataset = parent[sample]        
            config.Data.unitsPerJob = filesPerJob
            config.Data.totalUnits = nfiles
            config.Data.outputDatasetTag = sample
            config.Data.lumiMask = mask
            config.Data.outLFNDirBase = '/store/user/woodson/' + name + '_' + key # change this depending on where you want to store things (your username)
            submit(config)
            
            
