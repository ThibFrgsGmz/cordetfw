/**
 * @file CrPsTestOnBoardConnectionRep.c
 *
 * Implementation of the Perform Connection Test out-going command packet.
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#include "CrPsTestOnBoardConnectionRep.h"

/*#include "FwProfile/FwSmConfig.h"*/
#include "Pckt/CrFwPckt.h"
#include "OutFactory/CrFwOutFactory.h"
#include "OutCmp/CrFwOutCmp.h"
#include "OutLoader/CrFwOutLoader.h"
#include "CrFwCmpData.h"

#include "Services/General/CrPsConstants.h"

#include <stdio.h>
#include "CrPsDebug.h"

/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestOnBoardConnectionRepEnableCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* Report is always enabled */

  DEBUGP_17("CrPsTestOnBoardConnectionRepEnableCheck()\n");

  /* CrFwBool anschaun da gibts ev. auch eine TRUE Variable */
  return 1; /* always True */
}

/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestOnBoardConnectionRepReadyCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* Report is always ready */

  DEBUGP_17("CrPsTestOnBoardConnectionRepReadyCheck()\n");

  return 1; /* always True */
}

/* ------------------------------------------------------------------------------------ */
CrFwBool_t CrPsTestOnBoardConnectionRepRepeatCheck(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* Report is never repeated */

  DEBUGP_17("CrPsTestOnBoardConnectionRepRepeatCheck()\n");

  return 0; /* always False */
}

/* ------------------------------------------------------------------------------------ */
void CrPsTestOnBoardConnectionRepUpdateAction(FwSmDesc_t smDesc)
{
  CRFW_UNUSED(smDesc);
  /* No action */

  DEBUGP_17("CrPsTestOnBoardConnectionRepUpdateAction()\n");

  return;
}
