#!bin/bash

python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_QCD_PUPPI/uhh2.AnalysisModuleRunner.MC.MC_QCD_HT300to500_2018*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_QCD_PUPPI/uhh2.AnalysisModuleRunner.MC.MC_QCD_HT500to700_2018*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_QCD_PUPPI/uhh2.AnalysisModuleRunner.MC.MC_QCD_H700to1000_2018*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_QCD_PUPPI/uhh2.AnalysisModuleRunner.MC.MC_QCD_HT1000to1500_2018*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_QCD_PUPPI/uhh2.AnalysisModuleRunner.MC.MC_QCD_HT1500to2000_2018*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_QCD_PUPPI/uhh2.AnalysisModuleRunner.MC.MC_QCD_HT2000toInf_2018*'

python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_data_JetHT_PUPPI/uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018A*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_data_JetHT_PUPPI/uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018B*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_data_JetHT_PUPPI/uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018C*'
python /nfs/dust/cms/user/zoiirene/RunII_102X/CMSSW_10_2_10/src/UHH2/scripts/create-multi-dataset-xmlfiles.py '/nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/workdir_data_JetHT_PUPPI/uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018D*'

mv uhh2.AnalysisModuleRunner.MC.MC_QCD_HT300to500_2018.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.MC.MC_QCD_HT500to700_2018.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.MC.MC_QCD_HT700to1000_2018.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.MC.MC_QCD_HT1000to1500_2018.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.MC.MC_QCD_HT1500to2000_2018.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.MC.MC_QCD_HT2000toInf_2018.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018A.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018B.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018C.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv uhh2.AnalysisModuleRunner.Data.DATA_JetHT_Run2018D.xml /nfs/dust/cms/user/zoiirene/DiBoson/102X/OutputBatch/PreSelection/xmlfiles/
mv TEMPLATE*xml