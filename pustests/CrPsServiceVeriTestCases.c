/**
 * @file
 *
 * Implementation of test cases for Service Components.
 *
 * @author Christian Reimers <christian.reimersy@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * @copyright Department of Astrophysics, University of Vienna, 2017, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include "CrFwRepErrStub.h"
#include "CrFwInStreamSocket.h"
#include "CrFwClientSocket.h"
#include "CrFwServerSocket.h"
#include "CrFwOutStreamSocket.h"
#include "CrFwInStreamTestCases.h"
#include "CrFwRepInCmdOutcomeStub.h"
#include "CrFwInStreamStub.h"
/* Include FW Profile files */
#include "FwSmConstants.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwPrConstants.h"
/* Include configuration files */
#include "CrFwInStreamUserPar.h" /* TODO: CrPsInStreamUserPar.h" */
#include "CrFwOutRegistryUserPar.h" /* TODO: CrPsOutRegistryUserPar.h */
#include "CrFwOutFactoryUserPar.h"
/* Include framework files */
#include "CrFwCmpData.h"
#include "OutRegistry/CrFwOutRegistry.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "Pckt/CrFwPckt.h"
#include "InCmd/CrFwInCmd.h"
#include "InFactory/CrFwInFactory.h"
#include "OutFactory/CrFwOutFactory.h"
#include "CrFwTime.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"

#include <CrPsUtilities.h>
#include <Services/General/CrPsConstants.h>
#include <CrPsPkt.h>
#include "DataPool/CrPsDpServReqVerif.h"

/* Include system files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "CrPsDebug.h"

/* ---------------------------------------------------------------------------------------------*/
CrFwBool_t CrPsServVeriTestCase1()
{
  /* Check Service 1 */
  unsigned short i;
  FwSmDesc_t inFactory, outFactory, outManager, inCmd, outCmp, outCmpArr[CR_FW_OUTFACTORY_MAX_NOF_OUTCMP], inRep, inManager;
  CrFwPckt_t pckt, pckt2;
  prData_t prData;
  CrFwCmpData_t* outManagerData;
  CrFwOutManagerData_t* outManagerCSData;
  unsigned short ACK_WRONG_CHKSM = 1002, pcktID;

  CrPsInit();

  /* Instantiate the OutFactory, InFactory, OutManager */
  DEBUGP_TS1("Instantiate the OutFactory, InFactory, OutManager  \n");
  outFactory = CrFwOutFactoryMake();
  if (outFactory == NULL)
    return 0;
  if (FwSmCheckRec(outFactory) != smSuccess)
    return 0;

  inFactory = CrFwInFactoryMake();
  if (inFactory == NULL)
    return 0;
  if (FwSmCheckRec(inFactory) != smSuccess)
    return 0;

  outManager = CrFwOutManagerMake(0);
  if (outManager == NULL)
    return 0;
  if (FwSmCheckRec(outManager) != smSuccess)
    return 0;
  
  inManager = CrFwInManagerMake(0);
  if (inManager == NULL)
    return 0;
  if (FwSmCheckRec(inManager) != smSuccess)
    return 0;
  
  /* Initialize and Configure OutFactory and check success */
  DEBUGP_TS1("Initialize and Configure OutFactory and check success \n");
  CrFwCmpInit(outFactory);
  CrFwCmpReset(outFactory);
  if (!CrFwCmpIsInConfigured(outFactory))
    return 0;

    /* Initialize and Configure InFactory and check success */
  DEBUGP_TS1("Initialize and Configure InFactory and check success \n");
  CrFwCmpInit(inFactory);
  CrFwCmpReset(inFactory);
  if (!CrFwCmpIsInConfigured(inFactory))
    return 0;

  /* Initialize and Configure OutManager and check success */
  DEBUGP_TS1("Initialize and Configure OutManager and check success  \n");
  CrFwCmpInit(outManager);
  CrFwCmpReset(outManager);
  if (!CrFwCmpIsInConfigured(outManager))
    return 0;

  /* Initialize and Configure InManager and check success */
  DEBUGP_TS1("Initialize and Configure InManager and check success  \n");
  CrFwCmpInit(inManager);
  CrFwCmpReset(inManager);
  if (!CrFwCmpIsInConfigured(inManager))
    return 0; 

  /* Check if number of Allocated Packets = 0*/
  DEBUGP_TS1("Check if no packets are allocated yet \n");
  if (CrFwPcktGetNOfAllocated() != 0)
    return 0;

  /* Allocate a 17.1 Packet */
  DEBUGP_TS1("Allocating a 17.1 Packet \n");
  pckt = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt,17);
  CrFwPcktSetServSubType(pckt,1);
  CrFwPcktSetDiscriminant(pckt,0);
  CrFwPcktSetCmdRepId(pckt,0);
  CrFwPcktSetSrc(pckt,0);
  CrFwPcktSetDest(pckt,0);
  CrFwPcktSetGroup(pckt,1);
  CrFwPcktSetAckLevel(pckt,1,1,1,1);  /* all acknowledgement of success */
  CrFwPcktSetSeqCnt(pckt,2);

  /*Getting the Packet ID so that we can check that in the datapool later*/
  DEBUGP_TS1("Getting the Packet ID so that we can check that in the datapool later\n");
  pcktID = getTmHeaderAPID(pckt);

  /* Check if number of Allocated Packets now is 1*/
  DEBUGP_TS1("Check if one packet is allocated \n");
  if (CrFwPcktGetNOfAllocated() != 1)
    return 0;

  /* Check if number of Allocated InCommands = 0*/
  DEBUGP_TS1("Check if no inCommands are allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /*Creating an InCommand out of the 17.1 packet*/
  DEBUGP_TS1("Create an InCommand out of the 17.1 packet \n");
  inCmd = CrFwInFactoryMakeInCmd(pckt);

  /*Check if number of Allocated InCommands is now 1*/
  DEBUGP_TS1("Check if one InCommand is allocated \n");
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 1)
    return 0;

  /* Check the type identifier */
  DEBUGP_TS1("Check the type identifier (CR_FW_INCOMMAND_TYPE) \n");
  if (CrFwCmpGetTypeId(inCmd) != CR_FW_INCOMMAND_TYPE)
    return 0;

  /* Check type and sub-type of the InCommand*/
  DEBUGP_TS1("Check the type and subtype of the InCommand\n");
  if (CrFwInCmdGetServType(inCmd) != 17)
    return 0;
  if (CrFwInCmdGetServSubType(inCmd) != 1)
    return 0;

  /*check that the InCommand is in ACCEPTED state*/
  DEBUGP_TS1("check that the InCommand is in ACCEPTED state  \n");
  if (!CrFwInCmdIsInAccepted(inCmd))
    return 0;

  /* Check if number of Allocated OutComponents = 0*/
  DEBUGP_TS1("Check if no OutComponents are allocated \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Successful Acceptance Verification Report*/
  /*Standard Check Service (1,1)*/
  DEBUGP_TS1("Standard Check Service (1,1) \n");
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_ACC_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 1*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 1 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 1)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.1 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.1 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 1)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1.2) are initially 0 */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.2) are initially 0   \n");
  if (getDpfailCodeAccFailed() != 0)
    return 0;
  if (getDpnOfAccFailed() != 0)
    return 0;
  if (getDppcktIdAccFailed() != 0)
    return 0;

  /*Failed Acceptance Verificatin Report*/
  /*Standard Check Service (1,2)*/
  DEBUGP_TS1("Standard Check Service (1,2) \n");
  SendReqVerifAccFailRep(inCmd, CRPS_REQVERIF_ACC_FAIL);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 2*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 2 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 2)
    return 0;

  /* Check that all DataPool Variables concerning (1.2) are updated */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.2) are updated   \n");
  if (getDpfailCodeAccFailed() != 2)
    return 0;
  if (getDpnOfAccFailed() != 1)
    return 0;
  if (getDppcktIdAccFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.2 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.2 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 2)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /*Successful Start of Execution Verification Report*/
  /*Standard Check Service (1,3)*/
  DEBUGP_TS1("Standard Check Service (1,3) \n");
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_START_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 3*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 3 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 3)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.3 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.3 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 3)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1.4) are initially 0 */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.4) are initially 0   \n");
  if (getDpfailCodeStartFailed() != 0)
    return 0;
  if (getDpnOfStartFailed() != 0)
    return 0;
  if (getDppcktIdStartFailed() != 0)
    return 0;

 /*Failed Start of Execution Verification Report*/
 /*Standard Check Service (1,4)*/
  DEBUGP_TS1("Standard Check Service (1,4) \n");
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_START_FAIL, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 4*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 4 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 4)
    return 0;

  /* Check that all DataPool Variables concerning (1.4) are updated */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.4) are updated   \n");
  if (getDpfailCodeStartFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfStartFailed() != 1)
    return 0;
  if (getDppcktIdStartFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.4 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.4 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 4)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;
 
 /* Successful Progress of Execution Verification Report*/
 /*Standard Check Service (1,5)*/
  DEBUGP_TS1("Standard Check Service (1,5 \n");
  SendReqVerifPrgrSuccRep(inCmd, CRPS_REQVERIF_PROG_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 5*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 5 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 5)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.5 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.5 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 5)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1.6) are initially 0 */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.6) are initially 0   \n");
  if (getDpfailCodePrgrFailed() != 0)
    return 0;
  if (getDpnOfPrgrFailed() != 0)
    return 0;
  if (getDppcktIdPrgrFailed() != 0)
    return 0;
  if (getDpstepPrgrFailed() != 0)
    return 0;

  /*Failed Progress of Execution Verification Report*/
  /*Standard Check Service (1,6)*/
  DEBUGP_TS1("Standard Check Service (1,6) \n");
  SendReqVerifPrgrFailRep(inCmd, CRPS_REQVERIF_PROG_FAIL, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 6*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 6 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 6)
    return 0;

  /* Check that all DataPool Variables concerning (1.6) are updated */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.6) are updated   \n");
  if (getDpfailCodePrgrFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfPrgrFailed() != 1)
    return 0;
  if (getDppcktIdPrgrFailed() != pcktID)
    return 0;
  if (getDpstepPrgrFailed() != 6)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.6 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.6 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 6)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /*  Successful Completion of Execution Verification Report*/
  /*Standard Check Service (1,7)*/
  DEBUGP_TS1("Standard Check Service (1,7) \n");
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_TERM_SUCC);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 7*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 7 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 7)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.7 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.7 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 7)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1.8) are initially 0 */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.8) are initially 0   \n");
  if (getDpfailCodeTermFailed() != 0)
    return 0;
  if (getDpnOfTermFailed() != 0)
    return 0;
  if (getDppcktIdTermFailed() != 0)
    return 0;

  /*Failed Completion of Execution Verification Report*/
  /*Standard Check Service (1,8)*/
  DEBUGP_TS1("Standard Check Service (1,8) \n");
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_TERM_FAIL, ACK_WRONG_CHKSM);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 8*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 8 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 8)
    return 0;

  /* Check that all DataPool Variables concerning (1.8) are updated */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.8) are updated   \n");
  if (getDpfailCodeTermFailed() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfTermFailed() != 1)
    return 0;
  if (getDppcktIdTermFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.8 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.8 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 8)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check that all DataPool Variables concerning (1.10) are initially 0 */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.10) are initially 0   \n");
  if (getDpinvDestRerouting() != 0)
    return 0;
  if (getDpnOfReroutingFailed() != 0)
    return 0;
  if (getDppcktIdReroutingFailed() != 0)
    return 0;

  /*Failed Rerouting Verification Report*/
  /*Standard Check Service (1,10)*/
  DEBUGP_TS1("Standard Check Service (1,10) \n");
  prData.smDesc = inCmd;
  prData.ushortParam1 = ACK_WRONG_CHKSM;

  FwPrSetData(prDescServReqVerifPcktReroutFail, &prData);
  FwPrRun(prDescServReqVerifPcktReroutFail);

  /* Check if number of Allocated OutComponents = 1*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 1 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 1)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager = 9*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager = 9 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /* Check that all DataPool Variables concerning (1.10) are updated */
  DEBUGP_TS1("Check that all DataPool Variables concerning (1.10) are updated   \n");
  if (getDpinvDestRerouting() != ACK_WRONG_CHKSM)
    return 0;
  if (getDpnOfReroutingFailed() != 1)
    return 0;
  if (getDppcktIdReroutingFailed() != pcktID)
    return 0;

  /* Get the Data from the out Manager */
  DEBUGP_TS1("Get the Information from the OutManager \n");
  outManagerData = (CrFwCmpData_t*)FwSmGetData(outManager);
  outManagerCSData = (CrFwOutManagerData_t*)outManagerData->cmpSpecificData;
  outCmp = outManagerCSData->pocl[CrFwOutManagerGetNOfLoadedOutCmp(outManager)-1];
  
  /* Check if there is a 1.10 Report waitig in the OutManager (loaded) */
  DEBUGP_TS1("Check if there is a 1.10 Report waitig in the OutManager (loaded) \n"); 
  if (CrFwCmpGetTypeId(outCmp) != CR_FW_OUTCMP_TYPE)
    return 0;
  if (CrFwOutCmpGetServType(outCmp) != 1)
    return 0;
  if (CrFwOutCmpGetServSubType(outCmp) != 10)
    return 0;

  /*Checking OutComponent Desicions of the Guards (1.2 and 1.10)*/
  /*Extended Check Service (1,2) for an OutComponent ( no 1.2 should be created!)*/
  DEBUGP_TS1("Extended Check Service (1,2) for an OutComponent ( no 1.2 should be created!)\n");
  SendReqVerifAccFailRep(outCmp, CRPS_REQVERIF_ACC_FAIL);

  /* Check if number of loaded OutComponents in the OutManager stays at 9*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager stays at 9 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /*Extended Check Service (1,10) for an OutComponent ( no 1.10 should be created!)*/
  DEBUGP_TS1("Extended Check Service (1,10) for an OutComponent ( no 1.10 should be created!)\n");
  prData.smDesc = outCmp;
  prData.ushortParam1 = ACK_WRONG_CHKSM;

  FwPrSetData(prDescServReqVerifPcktReroutFail, &prData);
  FwPrRun(prDescServReqVerifPcktReroutFail);

  /* Check if number of loaded OutComponents in the OutManager stays at 9*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager stays at 9 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /*Release the OutComponent*/
  DEBUGP_TS1("Release the OutComponent\n");
  CrFwOutFactoryReleaseOutCmp(outCmp);

  /* Check if number of Allocated OutComponents now is 0 */
  DEBUGP_TS1("Check if number of Allocated OutComponents now is 0  \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /*Checking REPORT Desicions of the Guards (1.2 and 1.10)*/
  /* allocate an 17.2 in Report */
  DEBUGP_TS1("allocate an 17.2 in Report \n"); 
  pckt2 = CrFwPcktMake(100);
  CrFwPcktSetServType(pckt2,17);
  CrFwPcktSetServSubType(pckt2,2);
  CrFwPcktSetDiscriminant(pckt2,0);
  CrFwPcktSetAckLevel(pckt2, 0,0,0,0);
  CrFwPcktSetSrc(pckt2,0);
  CrFwPcktSetDest(pckt2,0);

  /* Check if number of Allocated Packets now is 2*/
  DEBUGP_TS1("Check if number of Allocated Packets now is 2 \n");
  if (CrFwPcktGetNOfAllocated() != 2)
    return 0;

  /* Check if number of Allocated InReports now is 0 */
  DEBUGP_TS1("Check if number of Allocated InReports now is 0  \n");
  if (CrFwInFactoryGetNOfAllocatedInRep() != 0)
    return 0;

  /*Create an InReport from pckt2 (17.2)*/
  DEBUGP_TS1("Create an InReport from pckt2 (17.2) \n");
  inRep = CrFwInFactoryMakeInRep(pckt2);

  /* Check if number of Allocated InReports now is 1 */
  DEBUGP_TS1("Check if number of Allocated InReports now is 1  \n");
  if (CrFwInFactoryGetNOfAllocatedInRep() != 1)
    return 0;

  /*Extended Check Service (1,2) for an InReport ( no 1.2 should be created!)*/
  DEBUGP_TS1("Extended Check Service (1,2) for an InReport ( no 1.2 should be created!)\n");
  SendReqVerifAccFailRep(inRep, CRPS_REQVERIF_ACC_FAIL);

  /* Check if number of Allocated OutComponents = 0*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 0 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager stays at 9*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager stays at 9 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;

  /*Extended Check Service (1,10) for an InReport ( no 1.10 should be created!)*/
  DEBUGP_TS1("Extended Check Service (1,10) for an InReport ( no 1.10 should be created!)\n");
  prData.smDesc = inRep;
  prData.ushortParam1 = ACK_WRONG_CHKSM;

  FwPrSetData(prDescServReqVerifPcktReroutFail, &prData);
  FwPrRun(prDescServReqVerifPcktReroutFail);

  /* Check if number of Allocated OutComponents = 0*/
  DEBUGP_TS1("Check if number of Allocated OutComponents = 0 \n");
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Check if number of loaded OutComponents in the OutManager stays at 9*/
  DEBUGP_TS1("Check if number of loaded OutComponents in the OutManager stays at 9 \n");
  if (CrFwOutManagerGetNOfLoadedOutCmp(outManager) != 9)
    return 0;


  /*Fill the outfactory so that an Error could occur (leave no free slot)*/
  DEBUGP_TS1("Fill the outfactory so that an Error could occur (leave no free slot) \n");
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    outCmpArr[i] = CrFwOutFactoryMakeOutCmp(17,2,0,0);
  }

  /* Check if no Application Error has occured*/
  DEBUGP_TS1("Check if no Application Error has occured\n");
  if (CrFwGetAppErrCode() != 0)
    return 0;

/*Extended Check Service (1,1) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,1) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_ACC_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;
  
  /*Extended Check Service (1,2) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,2) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifAccFailRep(inCmd, CRPS_REQVERIF_ACC_FAIL);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;
 
  /*Extended Check Service (1,3) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,3) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_START_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;
 
  /*Extended Check Service (1,4) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,4) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_START_FAIL, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,5) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,5) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifPrgrSuccRep(inCmd, CRPS_REQVERIF_PROG_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,6) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,6) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifPrgrFailRep(inCmd, CRPS_REQVERIF_PROG_FAIL, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,7) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,7) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifAccSuccRep(inCmd, CRPS_REQVERIF_TERM_SUCC);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,8) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,8) no free slots i the OutFactory! Application Error should be 10 \n");
  SendReqVerifCmdFailRep(inCmd, CRPS_REQVERIF_TERM_FAIL, ACK_WRONG_CHKSM);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /*Extended Check Service (1,10) no free slots i the OutFactory! Application Error should be 10*/
  DEBUGP_TS1("Extended Check Service (1,10) no free slots i the OutFactory! Application Error should be 10 \n");
  prData.smDesc = inCmd;
  prData.ushortParam1 = ACK_WRONG_CHKSM;

  FwPrSetData(prDescServReqVerifPcktReroutFail, &prData);
  FwPrRun(prDescServReqVerifPcktReroutFail);

  /* Check if Application Error 10 has occured (An OutComponent allocation request has failed)*/
  DEBUGP_TS1("Check if Application Error 10 has occured (An OutComponent allocation request has failed)\n");
  if (CrFwGetAppErrCode() != 10)
    return 0;

  /* Release all outcomponents, that have been created to fill the outfactory */
  DEBUGP_TS1("Release all outcomponents, that have been created to fill the outfactory \n");
  for (i=0;i<=CR_FW_OUTFACTORY_MAX_NOF_OUTCMP-1;i++)
  {
    CrFwOutFactoryReleaseOutCmp(outCmpArr[i]);
  }

  /* Set the Application Error to 0 and check it*/
  DEBUGP_TS1("Set the Application Error to 0 and check it\n");
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwGetAppErrCode() != 0)
    return 0;

  /* Reset OutManager and check that all OutComponents are unloaded and released */
  DEBUGP_TS1("Reset OutManager and check that all OutComponents are unloaded and released \n");
  CrFwCmpReset(outManager);
  CrFwSetAppErrCode(crNoAppErr);
  if (CrFwOutManagerGetNOfPendingOutCmp(outManager) != 0)
    return 0;

  /* Reset InManager and check that all InComponents are unloaded and released */
  DEBUGP_TS1("Reset InManager and check that all InComponents are unloaded and released \n");
  CrFwCmpReset(inManager);
  if (CrFwOutManagerGetNOfPendingOutCmp(inManager) != 0)
    return 0;
    
  /* Reset the OutFactory and check that no OutComponents are allocated */
  DEBUGP_TS1("Reset the OutFactory and check that no OutComponents are allocated \n");
  CrFwCmpReset(outFactory);  
  if (CrFwOutFactoryGetNOfAllocatedOutCmp() != 0)
    return 0;

  /* Reset the InFactory and check that no InCommands are allocated */
  DEBUGP_TS1("Reset the InFactory and check that no InCommands are allocated \n");
  CrFwCmpReset(inFactory);
  if (CrFwInFactoryGetNOfAllocatedInCmd() != 0)
    return 0;

  /* Check application errors */
  DEBUGP_TS1("Check application errors \n");
  if (CrFwGetAppErrCode() != crNoAppErr)
    return 0;



  DEBUGP_TS1("==============================\n");
  DEBUGP_TS1("==============================\n");
  DEBUGP_TS1("==============================\n");
  DEBUGP_TS1("==============================\n");

  DEBUGP_TS1("getDpfailCodeAccFailed : %d \n",getDpfailCodeAccFailed());
  DEBUGP_TS1("getDpnOfAccFailed : %d \n",getDpnOfAccFailed());
  DEBUGP_TS1("getDppcktIdAccFailed : %d \n",getDppcktIdAccFailed());

  DEBUGP_TS1("getDpfailCodeStartFailed : %d \n",getDpfailCodeStartFailed());
  DEBUGP_TS1("getDpnOfStartFailed : %d \n",getDpnOfStartFailed());
  DEBUGP_TS1("getDppcktIdStartFailed : %d \n",getDppcktIdStartFailed());

  DEBUGP_TS1("getDpfailCodePrgrFailed : %d \n",getDpfailCodePrgrFailed());
  DEBUGP_TS1("getDpnOfPrgrFailed : %d \n",getDpnOfPrgrFailed());
  DEBUGP_TS1("getDppcktIdPrgrFailed : %d \n",getDppcktIdPrgrFailed());
  DEBUGP_TS1("getDpstepPrgrFailed : %d \n",getDpstepPrgrFailed());

  DEBUGP_TS1("getDpfailCodeTermFailed : %d \n",getDpfailCodeTermFailed());
  DEBUGP_TS1("getDpnOfTermFailed : %d \n",getDpnOfTermFailed());
  DEBUGP_TS1("getDppcktIdTermFailed : %d \n",getDppcktIdTermFailed());

  DEBUGP_TS1("getDpinvDestRerouting : %d \n",getDpinvDestRerouting());
  DEBUGP_TS1("getDpnOfReroutingFailed : %d \n",getDpnOfReroutingFailed());
  DEBUGP_TS1("getDppcktIdReroutingFailed : %d \n",getDppcktIdReroutingFailed());

  DEBUGP_TS1("==============================\n");
  DEBUGP_TS1("==============================\n");
  DEBUGP_TS1("==============================\n");
  DEBUGP_TS1("==============================\n");





  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsServVeriTestCase2()
{




  return 1;
}

/* ---------------------------------------------------------------------------------------------*/

CrFwBool_t CrPsServVeriTestCase3()
{
  return 1;

}

/* ---------------------------------------------------------------------------------------------*/