/**
 * @file
 *
 * Implementation of InManager State Machine.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
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

#include <stdlib.h>
/* Include configuration files */
#include "CrFwInLoaderUserPar.h"
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "CrFwTime.h"
#include "CrFwInLoader.h"
#include "CrFwRepInCmdOutcome.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "Pckt/CrFwPckt.h"
#include "Pckt/CrFwPcktQueue.h"
#include "InRegistry/CrFwInRegistry.h"
#include "InFactory/CrFwInFactory.h"
#include "InStream/CrFwInStream.h"
#include "InManager/CrFwInManager.h"
#include "InCmd/CrFwInCmd.h"
#include "OutStream/CrFwOutStream.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
/* Include FW Profile files */
#include "FwProfile/FwSmConstants.h"
#include "FwProfile/FwSmDCreate.h"
#include "FwProfile/FwSmConfig.h"
#include "FwProfile/FwSmCore.h"
#include "FwProfile/FwPrConstants.h"
#include "FwProfile/FwPrDCreate.h"
#include "FwProfile/FwPrConfig.h"
#include "FwProfile/FwPrCore.h"

/** The InLoader singleton */
static FwSmDesc_t inLoader = NULL;

/** The data structure for the InLoader */
static CrFwCmpData_t inLoaderData;

/** The component-specific data for the InLoader */
static CrFwInLoaderData_t inLoaderCmpSpecificData;

/** Pointer to function which checks the legality of the packet destination. */
static CrFwInLoaderGetReroutingDest_t getReroutingDest = CR_FW_INLOADER_DET_REROUTING_DEST

/** Pointer to function which selects the InManager. */
static CrFwInLoaderGetInManager_t getInManager = CR_FW_INLOADER_SEL_INMANAGER

/**
 * Implement the logic of the InLoader Execution Procedure (see figure below).
 * This function is executed every time the Execution Procedure of the InLoader
 * is executed.
 * @image html InLoaderExecution.png
 * @param execPr the Execution Procedure of the InManager
 */
static void InLoaderExecAction(FwPrDesc_t execPr);

/**
 * Load the command or report encapsulated in the argument packet into an
 * InManager.
 * This function implements the logic shown in the figure.
 * @image html InLoaderLoadCommandReport.png
 * @param pckt the packet to be loaded in the InManager
 */
static void InLoaderLoadCmdRep(CrFwPckt_t pckt);

/*-----------------------------------------------------------------------------------------*/
FwSmDesc_t CrFwInLoaderMake() {
	FwPrDesc_t resetPr, execPr, initPr;

	if (inLoader != NULL) {
		return inLoader;	/* The requested SM has already been created */
	}

	/* Create the requested SM as an extension of the base component SM */
	inLoader = FwSmCreateDer(CrFwBaseCmpMake());

	/* Create the Reset Procedure for the InLoader Component */
	resetPr = FwPrCreateDer(CrFwCmpGetResetProc());

	/* Create the Initialization Procedure for the InLoader Component */
	initPr = FwPrCreateDer(CrFwCmpGetInitProc());

	/* Create the Execution Procedure for the InLoader Component */
	execPr = FwPrCreateDer(CrFwBaseCmpGetDummyExecProc());
	FwPrOverrideAction(execPr, &CwFwBaseCmpDummyExecAction, &InLoaderExecAction);

	/* Initialize the data for the requested SM */
	inLoaderData.outcome = 1;
	inLoaderData.initProc = initPr;
	inLoaderData.resetProc = resetPr;
	inLoaderData.execProc = execPr;
	inLoaderData.instanceId = 0;
	inLoaderData.typeId = CR_FW_INLOADER_TYPE;
	inLoaderData.cmpSpecificData = &inLoaderCmpSpecificData;

	/* Attach the data to the InLoader state machine and to its procedures. */
	FwSmSetData(inLoader, &inLoaderData);
	FwPrSetData(inLoaderData.initProc, &inLoaderData);
	FwPrSetData(inLoaderData.resetProc, &inLoaderData);
	FwPrSetData(inLoaderData.execProc, &inLoaderData);

	/* Start the InLoader */
	FwSmStart(inLoader);

	return inLoader;
}

/*-----------------------------------------------------------------------------------------*/
void CrFwInLoaderSetInStream(FwSmDesc_t inStream) {
	inLoaderCmpSpecificData.inStream = inStream;
}

/*-----------------------------------------------------------------------------------------*/
static void InLoaderExecAction(FwPrDesc_t prDesc) {
	CrFwPckt_t pckt;
	CrFwDestSrc_t pcktDest, reroutingDest;
	FwSmDesc_t outStream;
	CRFW_UNUSED(prDesc);

	/* Retrieve packet from InStream */
	pckt = CrFwInStreamGetPckt(inLoaderCmpSpecificData.inStream);
	if (pckt == NULL)
		return;

	/* Get packet destination and check whether it is the host application */
	pcktDest = CrFwPcktGetDest(pckt);
	if (pcktDest == CR_FW_HOST_APP_ID) {
		InLoaderLoadCmdRep(pckt);
		return;
	}

	/* Check whether packet should be re-routed to another destination */
	reroutingDest = getReroutingDest(pcktDest);
	if (reroutingDest == 0) {	/* destination is invalid */
		CrFwRepErrInstanceIdAndDest(crInLoaderInvDest, inLoaderData.typeId, inLoaderData.instanceId,
		                            CrFwPcktGetCmdRepId(pckt), reroutingDest);
		CrFwPcktRelease(pckt);
		return;
	}

	/* Re-route packet and then release it */
	outStream = CrFwOutStreamGet(reroutingDest);
	CrFwOutStreamSend(outStream, pckt);
	CrFwPcktRelease(pckt);
	return;
}

/*-----------------------------------------------------------------------------------------*/
static void InLoaderLoadCmdRep(CrFwPckt_t pckt) {
	FwSmDesc_t inCmp;
	CrFwInstanceId_t instanceId = CrFwPcktGetCmdRepId(pckt);
	CrFwServType_t servType = CrFwPcktGetServType(pckt);
	CrFwServSubType_t servSubType = CrFwPcktGetServSubType(pckt);
	CrFwDiscriminant_t disc = CrFwPcktGetDiscriminant(pckt);
	CrFwCmdRepType_t cmdRepFlag = CrFwPcktGetCmdRepType(pckt);
	CrFwCmpData_t* inCmpData;
	CrFwInstanceId_t inManagerInstanceId;
	CrFwBool_t inManagerLoadOutcome;

	if (CrFwPcktGetCmdRepType(pckt) == crCmdType) {
		inCmp = CrFwInFactoryMakeInCmd(pckt);
		if (inCmp == NULL) {	/* InCmd had invalid type or no more resources are available */
			CrFwRepInCmdOutcome(crCmdAckAccFail, instanceId, servType, servSubType, disc, 0);
			CrFwPcktRelease(pckt);
			return;
		}
	} else {
		inCmp = CrFwInFactoryMakeInRep(pckt);
		if (inCmp == NULL) {	/* InRep had invalid type or no more resources are available */
			CrFwRepErrInstanceIdAndOutcome(crInLoaderAccFail, inLoaderData.typeId,
			                               inLoaderData.instanceId, instanceId, 0);
			CrFwPcktRelease(pckt);
			return;
		}
	}

	if (FwSmGetCurState(inCmp) != CR_FW_BASE_STATE_CONFIGURED) {	/* InRep/InCmd has failed its validity check */
		inCmpData = FwSmGetData(inCmp);
		if (cmdRepFlag == crRepType) {
			CrFwInFactoryReleaseInRep(inCmp);
			CrFwRepErrInstanceIdAndOutcome(crInLoaderAccFail, inLoaderData.typeId,
			                               inLoaderData.instanceId, instanceId, inCmpData->outcome);
			return;
		} else {
			CrFwInFactoryReleaseInCmd(inCmp);
			CrFwRepInCmdOutcome(crCmdAckAccFail, instanceId, servType, servSubType, disc, inCmpData->outcome);
			return;
		}
	}

	/* Select InManager */
	inManagerInstanceId = getInManager(servType, servSubType, disc, cmdRepFlag);

	/* Load InReport/InCommand in selected InManager */
	inManagerLoadOutcome = CrFwInManagerLoad(CrFwInManagerMake(inManagerInstanceId), inCmp);
	if (inManagerLoadOutcome == 0) {	/* Load operation has failed */
		if (cmdRepFlag == crRepType) {
			CrFwInFactoryReleaseInRep(inCmp);
			CrFwRepErrInstanceIdAndOutcome(crInLoaderAccFail, inLoaderData.typeId,
			                               inLoaderData.instanceId,instanceId, 0);
			return;
		} else {
			CrFwInFactoryReleaseInCmd(inCmp);
			CrFwRepInCmdOutcome(crCmdAckAccFail, instanceId, servType, servSubType, disc, 0);
			return;
		}
	} else 	/* Load operation was successful */
		if (cmdRepFlag == crCmdType)
			if (CrFwInCmdIsAcceptAck(inCmp) == 1)
				CrFwRepInCmdOutcome(crCmdAckAccSucc, instanceId, servType, servSubType, disc, 0);
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwInLoaderDefGetReroutingDestination(CrFwDestSrc_t pcktDest) {
	return pcktDest;
}

/*-----------------------------------------------------------------------------------------*/
CrFwDestSrc_t CrFwInLoaderDefNoRerouting(CrFwDestSrc_t pcktDest) {
	CRFW_UNUSED(pcktDest);
	return 0;
}

/*-----------------------------------------------------------------------------------------*/
CrFwInstanceId_t CrFwInLoaderDefGetInManager(CrFwServType_t servType, CrFwServSubType_t servSubType,
        CrFwDiscriminant_t discriminant, CrFwCmdRepType_t cmdRepFlag) {
	CRFW_UNUSED(servType);
	CRFW_UNUSED(servSubType);
	CRFW_UNUSED(discriminant);
	if (cmdRepFlag == crCmdType)
		return 0;
	else
		return 1;
}