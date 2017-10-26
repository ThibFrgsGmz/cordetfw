/**
 * @file CrPsCmd3SidStartCreate.c
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:17:19
 */

#include "CrPsCmd3SidStartCreate.h"

/** CR Framework function definitions*/
#include "CrFwConstants.h"

/** FW Profile function definitions */
#include "FwPrDCreate.h"
#include "FwPrConfig.h"

/** CrPsCmd3SidStart function definitions */
#include <stdlib.h>
#include "CrPsDebug.h"

/** Guard on the Control Flow from DECISION1 to DECISION3. */
FwPrBool_t CrPsCmd3SidStartG1E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION3 to N4. */
FwPrBool_t CrPsCmd3SidStartG2E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/** Guard on the Control Flow from DECISION4 to N7. */
FwPrBool_t CrPsCmd3SidStartG3E(FwPrDesc_t prDesc)
{
	CRFW_UNUSED(prDesc);
	return 1;
}

/* ----------------------------------------------------------------------------------------------------------------- */
FwPrDesc_t CrPsCmd3SidStartCreate(void* prData)
{
	const FwPrCounterU2_t DECISION1 = 1;		/* The identifier of decision node DECISION1 in procedure CrPsCmd3SidStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION1 = 2;	/* The number of control flows out of decision node DECISION1 in procedure CrPsCmd3SidStart */
	const FwPrCounterU2_t DECISION3 = 2;		/* The identifier of decision node DECISION3 in procedure CrPsCmd3SidStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION3 = 2;	/* The number of control flows out of decision node DECISION3 in procedure CrPsCmd3SidStart */
	const FwPrCounterU2_t DECISION4 = 3;		/* The identifier of decision node DECISION4 in procedure CrPsCmd3SidStart */
	const FwPrCounterU2_t N_OUT_OF_DECISION4 = 2;	/* The number of control flows out of decision node DECISION4 in procedure CrPsCmd3SidStart */

	/** Create the procedure */
	FwPrDesc_t prDesc = FwPrCreate(
		6,	/* N_ANODES - The number of action nodes */
		3,	/* N_DNODES - The number of decision nodes */
		13,	/* N_FLOWS - The number of control flows */
		6,	/* N_ACTIONS - The number of actions */
		6	/* N_GUARDS - The number of guards */
	);

	/** Configure the procedure */
	FwPrSetData(prDesc, prData);
	FwPrAddActionNode(prDesc, CrPsCmd3SidStart_N4, &CrPsCmd3SidStartN4);
	FwPrAddActionNode(prDesc, CrPsCmd3SidStart_N1, &CrPsCmd3SidStartN1);
	FwPrAddDecisionNode(prDesc, DECISION1, N_OUT_OF_DECISION1);
	FwPrAddActionNode(prDesc, CrPsCmd3SidStart_N2, &CrPsCmd3SidStartN2);
	FwPrAddActionNode(prDesc, CrPsCmd3SidStart_N3, &CrPsCmd3SidStartN3);
	FwPrAddDecisionNode(prDesc, DECISION3, N_OUT_OF_DECISION3);
	FwPrAddDecisionNode(prDesc, DECISION4, N_OUT_OF_DECISION4);
	FwPrAddActionNode(prDesc, CrPsCmd3SidStart_N7, &CrPsCmd3SidStartN7);
	FwPrAddActionNode(prDesc, CrPsCmd3SidStart_N8, &CrPsCmd3SidStartN8);
	FwPrAddFlowIniToAct(prDesc, CrPsCmd3SidStart_N1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3SidStart_N4, DECISION1, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3SidStart_N1, DECISION1, NULL);
	FwPrAddFlowDecToAct(prDesc, DECISION1, CrPsCmd3SidStart_N2, &CrPsCmd3SidStartG1);
	FwPrAddFlowDecToDec(prDesc, DECISION1, DECISION3, &CrPsCmd3SidStartG1E);
	FwPrAddFlowActToAct(prDesc, CrPsCmd3SidStart_N2, CrPsCmd3SidStart_N3, NULL);
	FwPrAddFlowActToDec(prDesc, CrPsCmd3SidStart_N3, DECISION3, NULL);
	FwPrAddFlowDecToDec(prDesc, DECISION3, DECISION4, &CrPsCmd3SidStartG2);
	FwPrAddFlowDecToAct(prDesc, DECISION3, CrPsCmd3SidStart_N4, &CrPsCmd3SidStartG2E);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd3SidStart_N8, &CrPsCmd3SidStartG3);
	FwPrAddFlowDecToAct(prDesc, DECISION4, CrPsCmd3SidStart_N7, &CrPsCmd3SidStartG3E);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3SidStart_N7, NULL);
	FwPrAddFlowActToFin(prDesc, CrPsCmd3SidStart_N8, NULL);

	return prDesc;
}
