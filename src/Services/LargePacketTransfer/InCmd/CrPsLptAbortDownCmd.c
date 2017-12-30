/**
 * \file
 *
 * Implementation of TC(13,130) LptAbortDownCmd.
 *
 * \note This file was generated on 2017-11-22 12:47:44
 * \author PnP Generator
 * \copyright (c) Copyright
 */

#include "CrPsLptAbortDownCmd.h"

#include <CrFwCmpData.h>
#include <FwSmConfig.h>

#include <CrPsUtilitiesServLpt.h>
#include <CrPsUserConstants.h>
#include <Services/General/CrPsPktServLpt.h>
#include <Services/LargePacketTransfer/StateMachines/CrPsLptCreate.h>


/**
 * Start action of TC(13,130) LptAbortDownCmd.
 * Determine the identifier of the LPT Buffer for the up-transfer by
 * computing: (x MOD LPT_N_BUF) where `x' is the Large Message Transaction
 * Identifier. Set action outcome to 'success' if the LPT State Machine is in
 * state DOWN_TRANSFER; otherwise set the action outcome to `failure'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdStartAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t        *inData;
  CrFwInCmdData_t      *cmpSpecificData;
  CrFwPckt_t            inPckt;
  CrPsTid_t Tid;
  unsigned int LptBufferId;
  unsigned short sm_state;

  CRFW_UNUSED(smDesc);

  /* Get inPckt */
  inData = (CrFwCmpData_t*) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) inData->cmpSpecificData;
  inPckt            = cmpSpecificData->pckt;

  /* Determine the identifier of the LPT Buffer */
  Tid = getLptStartDownCmdTid(inPckt);
  LptBufferId = Tid % LPT_N_BUF;

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  sm_state = FwSmGetCurState(smDescLpt);
  if (sm_state == CrPsLpt_DOWN_TRANSFER)
    {
      inData->outcome = 1;
    }
  else
    {
      inData->outcome = 0;
    }

  return;
}

/**
 * Progress action of TC(13,130) LptAbortDownCmd.
 * Send command Abort to the LPT State Machine
 * \param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdProgressAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  CRFW_UNUSED(smDesc);

  FwSmMakeTrans(smDescLpt, Abort);

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}

/**
 * Termination action of TC(13,130) LptAbortDownCmd.
 * Set action outcome to 'success'
 * \param smDesc The state machine descriptor.
 */
void CrPsLptAbortDownCmdTerminationAction(FwSmDesc_t smDesc)
{
  CrFwCmpData_t *inData;

  /* Set action outcome to 'success' */

  /* Get in data */
  inData = (CrFwCmpData_t*)FwSmGetData(smDesc);

  inData->outcome = 1;

  return;
}