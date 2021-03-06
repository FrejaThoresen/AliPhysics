AliAnalysisTaskCheckPerformanceCascadePbPb *AddTaskCheckPerformanceCascadePbPb( Int_t    minnTPCcls           = 80,
                                                                                Float_t  centrlowlim          = 0.,
                                                                                Float_t  centruplim           = 90.,
                                                                                TString  centrest             = "V0M",
                                                                                Bool_t   kusecleaning         = kTRUE,
                                                                                Float_t  vtxlim               = 10.,
                                                                                Bool_t   kextrasel            = kFALSE,
                                                                                Bool_t   kacccut              = kFALSE,
                                                                                Bool_t   krelaunchvertexers   = kFALSE,
                                                                                Float_t  minptondaughtertracks= 0.,
                                                                                Float_t  etacutondaughtertracks = 9999999. ) {
// Creates, configures and attaches to the train a cascades check task.
   // Get the pointer to the existing analysis manager via the static access method.
   //==============================================================================
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
      ::Error("AddTaskCheckPerformanceCascadePbPb", "No analysis manager to connect to.");
      return NULL;
   }   

   // Check the analysis type using the event handlers connected to the analysis manager.
   //==============================================================================
   if (!mgr->GetInputEventHandler()) {
      ::Error("AddTaskCheckPerformanceCascadePbPb", "This task requires an input event handler");
      return NULL;
   }   
   TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"

   // Create and configure the task
   AliAnalysisTaskCheckPerformanceCascadePbPb *taskCheckPerfCascadePbPb = new AliAnalysisTaskCheckPerformanceCascadePbPb("TaskCheckPerformanceCascadePbPb");

   taskCheckPerfCascadePbPb-> SetAnalysisType               (type);
   taskCheckPerfCascadePbPb-> SetRelaunchV0CascVertexers    (krelaunchvertexers);     
   taskCheckPerfCascadePbPb-> SetQualityCutZprimVtxPos      (kTRUE);
   taskCheckPerfCascadePbPb-> SetRejectEventPileUp          (kFALSE);
   taskCheckPerfCascadePbPb-> SetQualityCutNoTPConlyPrimVtx (kTRUE);
   taskCheckPerfCascadePbPb-> SetQualityCutTPCrefit         (kTRUE);
   taskCheckPerfCascadePbPb-> SetQualityCutnTPCcls          (kTRUE);             
   taskCheckPerfCascadePbPb-> SetQualityCutMinnTPCcls       (minnTPCcls);    
   taskCheckPerfCascadePbPb-> SetExtraSelections            (kextrasel);
   taskCheckPerfCascadePbPb-> SetApplyAccCut                (kacccut);
   taskCheckPerfCascadePbPb-> SetCentralityLowLim           (centrlowlim);       // setting centrality selection vriables
   taskCheckPerfCascadePbPb-> SetCentralityUpLim            (centruplim);
   taskCheckPerfCascadePbPb-> SetCentralityEst              (centrest);
   taskCheckPerfCascadePbPb-> SetUseCleaning                (kusecleaning);
   taskCheckPerfCascadePbPb-> SetVertexRange                (vtxlim);
   taskCheckPerfCascadePbPb-> SetMinptCutOnDaughterTracks   (minptondaughtertracks); 
   taskCheckPerfCascadePbPb-> SetEtaCutOnDaughterTracks     (etacutondaughtertracks);
   taskCheckPerfCascadePbPb-> SelectCollisionCandidates();   
 
   mgr->AddTask(taskCheckPerfCascadePbPb);

   // Create ONLY the output containers for the data produced by the task.
   // Get and connect other common input/output containers via the manager as below
   //==============================================================================

   // User file name (if need be)

   TString outputFileName = AliAnalysisManager::GetCommonFileName();
   outputFileName += ":PWGLFStrangeness.outputCheckPerformanceCascadePbPb";
   
   Printf("AddTaskCheckPerformanceCascadePbPb - Set OutputFileName : \n %s\n", outputFileName.Data() );
   
   AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("clistCascPerf",
							     TList::Class(),
							     AliAnalysisManager::kOutputContainer,
							     outputFileName );

   AliAnalysisDataContainer *coutput2 = mgr->CreateContainer("cfcontPIDAsXiM",
                                                             AliCFContainer::Class(),
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName );

   AliAnalysisDataContainer *coutput3 = mgr->CreateContainer("cfcontPIDAsXiP",
                                                             AliCFContainer::Class(),
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName );

   AliAnalysisDataContainer *coutput4 = mgr->CreateContainer("cfcontPIDAsOmegaM",
                                                             AliCFContainer::Class(),
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName );

   AliAnalysisDataContainer *coutput5 = mgr->CreateContainer("cfcontPIDAsOmegaP",
                                                             AliCFContainer::Class(),
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName );

   AliAnalysisDataContainer *coutput6 = mgr->CreateContainer("cfcontAsCuts",
                                                             AliCFContainer::Class(),
                                                             AliAnalysisManager::kOutputContainer,
                                                             outputFileName );



   mgr->ConnectInput( taskCheckPerfCascadePbPb, 0, mgr->GetCommonInputContainer());
   mgr->ConnectOutput(taskCheckPerfCascadePbPb, 1, coutput1);
   mgr->ConnectOutput(taskCheckPerfCascadePbPb, 2, coutput2);
   mgr->ConnectOutput(taskCheckPerfCascadePbPb, 3, coutput3);
   mgr->ConnectOutput(taskCheckPerfCascadePbPb, 4, coutput4);
   mgr->ConnectOutput(taskCheckPerfCascadePbPb, 5, coutput5);
   mgr->ConnectOutput(taskCheckPerfCascadePbPb, 6, coutput6);
   
   return taskCheckPerfCascadePbPb;
}   
