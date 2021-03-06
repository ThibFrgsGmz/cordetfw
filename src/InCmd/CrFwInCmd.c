/**
 * @file
 * @ingroup inCmdGroup
 * Implementation of OutComponent component.
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of the CORDET Framework.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#include <stdlib.h>
/* Include configuration files */
#include "CrFwCmpData.h"
/* Include framework files */
#include "CrFwConstants.h"
#include "CrFwRepErr.h"
#include "UtilityFunctions/CrFwUtilityFunctions.h"
#include "OutStream/CrFwOutStream.h"
#include "OutCmp/CrFwOutCmp.h"
#include "BaseCmp/CrFwBaseCmp.h"
#include "BaseCmp/CrFwInitProc.h"
#include "BaseCmp/CrFwResetProc.h"
#include "BaseCmp/CrFwDummyExecProc.h"
#include "OutFactory/CrFwOutFactory.h"
#include "Pckt/CrFwPckt.h"
#include "CrFwRepInCmdOutcome.h"
/* Include FW Profile files */
#include "FwPrConfig.h"
#include "FwPrDCreate.h"
#include "FwSmConfig.h"
#include "FwSmDCreate.h"
#include "FwPrCore.h"

/** Base OutComponent from which all other InCommands are derived. */
static FwSmDesc_t baseInCmdSmDesc = NULL;

/**
 * Entry action in state ABORTED.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void DoAbortAction(FwSmDesc_t smDesc);

/**
 * Entry and do action in state PROGRESS.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void DoProgressAction(FwSmDesc_t smDesc);

/**
 * Transition action on the transition from ACCEPTED to CPS1.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void DoStartAction(FwSmDesc_t smDesc);

/**
 * Transition action on the transition from PROGRESS to CPS2.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void DoTerminationAction(FwSmDesc_t smDesc);

/**
 * Transition action on the transition from CPS1 to ABORTED which
 * reports the failure of the Start Action.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void ReportStartFailed(FwSmDesc_t smDesc);

/**
 * Transition action on the transition from CPS2 to ABORTED which
 * reports the failure of the Termination Action.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void ReportTerminationFailed(FwSmDesc_t smDesc);

/**
 * Transition action on the transition from CPS1 to PROGRESS.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void ReportStartSuccess(FwSmDesc_t smDesc);

/**
 * Transition action on the transition from CPS2 to TERMINATED.
 * @param smDesc the descriptor of the InCommand state machine
 */
static void ReportTerminationSuccess(FwSmDesc_t smDesc);

/**
 * Guard on the transition from ACCEPTED to CPS1.
 * @param smDesc the descriptor of the InCommand state machine
 * @return the value of the Ready Check Operation of the InCommand
 */
static FwSmBool_t IsReady(FwSmDesc_t smDesc);

/**
 * Guard on the transition from CPS2 to TERMINATED.
 * @param smDesc the descriptor of the InCommand state machine
 * @return 1 if the outcome of the termination action was "success"
 */
static FwSmBool_t IsTerminationSuccess(FwSmDesc_t smDesc);

/* --------------------------------------------------------------------------------- */
FwSmDesc_t CrFwInCmdMakeBase() {
	FwSmCounterS1_t nOfStates = 4;				/* Number of states */
	FwSmCounterS1_t nOfChoicePseudoStates = 2;	/* Number of choice pseudo-states */
	FwSmCounterS1_t nOfTrans = 7;				/* Number of transitions */
	FwSmCounterS1_t nOfActions = 9;				/* Number of actions */
	FwSmCounterS1_t nOfGuards = 4;				/* Number of guards */
	FwSmCounterS1_t CPS_1 = 1;					/* Identifier of first choice pseudo-state */
	FwSmCounterS1_t CPS_2 = 2;					/* Identifier of second choice pseudo-state */
	FwSmDesc_t esm;

	if (baseInCmdSmDesc != NULL)
		return baseInCmdSmDesc;

	/* Create and configure the base InCommand */

	/* Extend the Base Component */
	baseInCmdSmDesc = FwSmCreateDer(CrFwBaseCmpMake());
	/* Create the InCommand SM and then embed it in state CONFIGURED of the Base Component */
	esm = FwSmCreate(nOfStates, nOfChoicePseudoStates, nOfTrans, nOfActions, nOfGuards);
	FwSmAddState(esm, CR_FW_INCMD_STATE_ACCEPTED, 1, NULL, NULL, NULL, NULL);
	FwSmAddState(esm, CR_FW_INCMD_STATE_PROGRESS, 1, &DoProgressAction, NULL, &DoProgressAction, NULL);
	FwSmAddState(esm, CR_FW_INCMD_STATE_TERMINATED, 0, NULL, NULL, NULL, NULL);
	FwSmAddState(esm, CR_FW_INCMD_STATE_ABORTED, 0, &DoAbortAction, NULL, NULL, NULL);
	FwSmAddChoicePseudoState(esm, CPS_1, 2);
	FwSmAddChoicePseudoState(esm, CPS_2, 2);
	FwSmAddTransIpsToSta(esm, CR_FW_INCMD_STATE_ACCEPTED, NULL);
	FwSmAddTransStaToCps(esm, FW_TR_EXECUTE, CR_FW_INCMD_STATE_ACCEPTED, CPS_1,
	                     &DoStartAction, &IsReady);
	FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_INCMD_STATE_PROGRESS, &ReportStartSuccess, &CrFwIsSmOutcomeOne);
	FwSmAddTransCpsToSta(esm, CPS_1, CR_FW_INCMD_STATE_ABORTED, &ReportStartFailed, NULL);	/* Else Guard */
	FwSmAddTransStaToCps(esm, CR_FW_INCMD_TR_TERMINATE, CR_FW_INCMD_STATE_PROGRESS, CPS_2,
	                     &DoTerminationAction, &CrFwInCmdIsProgressActionCompleted);
	FwSmAddTransCpsToSta(esm, CPS_2, CR_FW_INCMD_STATE_TERMINATED, &ReportTerminationSuccess, &IsTerminationSuccess);
	FwSmAddTransCpsToSta(esm, CPS_2, CR_FW_INCMD_STATE_ABORTED, &ReportTerminationFailed, NULL);	/* Else Guard */

	FwSmEmbed(baseInCmdSmDesc, CR_FW_BASE_STATE_CONFIGURED, esm);
	return baseInCmdSmDesc;
}

/* --------------------------------------------------------------------------------- */
void CrFwInCmdTerminate(FwSmDesc_t smDesc) {
	FwSmMakeTrans(smDesc, CR_FW_INCMD_TR_TERMINATE);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsInAccepted(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_INCMD_STATE_ACCEPTED);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsInProgress(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_INCMD_STATE_PROGRESS);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsInTerminated(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_INCMD_STATE_TERMINATED);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsInAborted(FwSmDesc_t smDesc) {
	return (FwSmGetCurStateEmb(smDesc) == CR_FW_INCMD_STATE_ABORTED);
}

/* --------------------------------------------------------------------------------- */
void CrFwInCmdConfigCheck(FwPrDesc_t prDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(prDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	if (cmpSpecificData->isValid(prDesc) == 1)
		cmpData->outcome = 1;
	else
		cmpData->outcome = 0;
}

/* --------------------------------------------------------------------------------- */
CrFwProgressStepId_t CrFwInCmdGetProgressStepId(FwSmDesc_t smDesc) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    return cmpSpecificData->progressStepId;
}

/* --------------------------------------------------------------------------------- */
void CrFwInCmdSetProgressStepId(FwSmDesc_t smDesc, CrFwProgressStepId_t stepId) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    cmpSpecificData->progressStepId = stepId;
}

/* --------------------------------------------------------------------------------- */
CrFwPckt_t CrFwInCmdGetPcktFromPrDesc(FwPrDesc_t prDesc) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwPrGetData(prDesc);
    CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    return cmpSpecificData->pckt;
}

/* --------------------------------------------------------------------------------- */
FwSmBool_t IsTerminationSuccess(FwSmDesc_t smDesc) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    if (cmpData->outcome == 1)
        return 1;
    return 0;
}

/* --------------------------------------------------------------------------------- */
FwSmBool_t IsReady(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return cmpSpecificData->isReady(smDesc);
}

/* --------------------------------------------------------------------------------- */
void ReportTerminationFailed(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	CrFwRepInCmdOutcome(crCmdAckTrmFail, cmpData->instanceId,
	                    CrFwPcktGetServType(cmpSpecificData->pckt),
	                    CrFwPcktGetServSubType(cmpSpecificData->pckt),
	                    CrFwPcktGetDiscriminant(cmpSpecificData->pckt),
	                    cmpData->outcome, smDesc);
}

/* --------------------------------------------------------------------------------- */
void ReportStartFailed(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	CrFwRepInCmdOutcome(crCmdAckStrFail, cmpData->instanceId,
	                    CrFwPcktGetServType(cmpSpecificData->pckt),
	                    CrFwPcktGetServSubType(cmpSpecificData->pckt),
	                    CrFwPcktGetDiscriminant(cmpSpecificData->pckt),
	                    cmpData->outcome, smDesc);
}

/* --------------------------------------------------------------------------------- */
void ReportStartSuccess(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	if (CrFwPcktIsStartAck(cmpSpecificData->pckt) == 1)
		CrFwRepInCmdOutcome(crCmdAckStrSucc, cmpData->instanceId,
		                    CrFwPcktGetServType(cmpSpecificData->pckt),
		                    CrFwPcktGetServSubType(cmpSpecificData->pckt),
		                    CrFwPcktGetDiscriminant(cmpSpecificData->pckt),
		                    cmpData->outcome, smDesc);
}

/* --------------------------------------------------------------------------------- */
void ReportTerminationSuccess(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	if (CrFwPcktIsTermAck(cmpSpecificData->pckt) == 1)
		CrFwRepInCmdOutcome(crCmdAckTrmSucc, cmpData->instanceId,
		                    CrFwPcktGetServType(cmpSpecificData->pckt),
		                    CrFwPcktGetServSubType(cmpSpecificData->pckt),
		                    CrFwPcktGetDiscriminant(cmpSpecificData->pckt),
		                    cmpData->outcome, smDesc);
}

/* --------------------------------------------------------------------------------- */
static void DoAbortAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	cmpSpecificData->abortAction(smDesc);
}

/* --------------------------------------------------------------------------------- */
static void DoProgressAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	CrFwProgressStepId_t prevStep;

	prevStep = cmpSpecificData->progressStepId;
	cmpSpecificData->progressAction(smDesc);
	if (cmpData->outcome != 1) {
		CrFwRepInCmdOutcome(crCmdAckPrgFail, cmpData->instanceId,
		                        CrFwPcktGetServType(cmpSpecificData->pckt),
		                        CrFwPcktGetServSubType(cmpSpecificData->pckt),
		                        CrFwPcktGetDiscriminant(cmpSpecificData->pckt),
		                        cmpData->outcome, smDesc);
		cmpSpecificData->nOfProgressFailure++;  /* Increment counter of progress failures */
		return;     /* Execution step has failed */
	}

    if (cmpSpecificData->progressStepId != prevStep)
        if (CrFwPcktIsProgressAck(cmpSpecificData->pckt) == 1) {
             CrFwRepInCmdOutcome(crCmdAckPrgSucc, cmpData->instanceId,
                                CrFwPcktGetServType(cmpSpecificData->pckt),
                                CrFwPcktGetServSubType(cmpSpecificData->pckt),
                                CrFwPcktGetDiscriminant(cmpSpecificData->pckt),
                                cmpData->outcome, smDesc);
             return; /* Progress step has succeeded */
        }
}

/* --------------------------------------------------------------------------------- */
static void DoStartAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	cmpSpecificData->startAction(smDesc);
}

/* --------------------------------------------------------------------------------- */
static void DoTerminationAction(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);

	cmpSpecificData->terminationAction(smDesc);
}

/* --------------------------------------------------------------------------------- */
CrFwDestSrc_t CrFwInCmdGetSrc(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetSrc(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwGroup_t CrFwInCmdGetGroup(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetGroup(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwServType_t CrFwInCmdGetServType(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetServType(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwServType_t CrFwInCmdGetServSubType(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetServSubType(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwDiscriminant_t CrFwInCmdGetDiscriminant(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetDiscriminant(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsAcceptAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsAcceptAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsStartAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsStartAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsProgressAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsProgressAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsTermAck(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktIsTermAck(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwSeqCnt_t CrFwInCmdGetSeqCnt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetSeqCnt(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPckt_t CrFwInCmdGetParStart(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetParStart(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPcktLength_t CrFwInCmdGetParLength(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return CrFwPcktGetParLength(cmpSpecificData->pckt);
}

/* --------------------------------------------------------------------------------- */
CrFwPckt_t CrFwInCmdGetPckt(FwSmDesc_t smDesc) {
	CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
	CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
	return cmpSpecificData->pckt;
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdIsProgressActionCompleted(FwSmDesc_t smDesc) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    return cmpSpecificData->isProgressActionCompleted;
}

/* --------------------------------------------------------------------------------- */
void CrFwInCmdSetProgressActionCompleted(FwSmDesc_t smDesc, CrFwBool_t progressActionCompleted) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    cmpSpecificData->isProgressActionCompleted = progressActionCompleted;
}

/* --------------------------------------------------------------------------------- */
CrFwProgressStepId_t CrFwInCmdGetNOfProgressFailure(FwSmDesc_t smDesc) {
    CrFwCmpData_t* cmpData = (CrFwCmpData_t*)FwSmGetData(smDesc);
    CrFwInCmdData_t* cmpSpecificData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    return cmpSpecificData->nOfProgressFailure;
}

/* --------------------------------------------------------------------------------- */
CrFwBool_t CrFwInCmdDefValidityCheck(FwPrDesc_t prDesc) {
    CrFwCmpData_t* cmpData = FwPrGetData(prDesc);
    CrFwInCmdData_t* inCmdData = (CrFwInCmdData_t*)(cmpData->cmpSpecificData);
    CrFwPckt_t pckt = inCmdData->pckt;
    return (CrFwPcktGetCrc(pckt) == CrFwPcktComputeCrc(pckt));
}

