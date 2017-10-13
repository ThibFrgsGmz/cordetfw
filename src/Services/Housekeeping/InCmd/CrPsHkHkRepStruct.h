/**
 * @file CrPsHkHkRepStruct.h
 *
 * Command (3,9) to Report Structure of a Housekeeping Report
 *
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

#ifndef CRPS_HK_HKREP_STRUCT_H
#define CRPS_HK_HKREP_STRUCT_H

#include "CrFwConstants.h"

/**
 * ReadyCheck of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Return “command is ready"
 * @param smDesc the state machine descriptor
 * @return always TRUE
 */
CrFwBool_t CrPsHkHkRepStructReadyCheck(FwSmDesc_t smDesc);

/**
 * Start action of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Run the procedure Start Action of Multi-SID Command of figure 9.3
 * @param smDesc the state machine descriptor
 */
void CrPsHkHkRepStructStartAction(FwSmDesc_t smDesc);

/**
 * Progress action of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Run the procedure Progress Action of Report Housekeeping Structure of figure 9.4
 * @param smDesc the state machine descriptor
 */
void CrPsHkHkRepStructProgressAction(FwSmDesc_t smDesc);

/**
 * Termination Action of the Command (3,9) to Report Structure of a Housekeeping Report in-coming command packet.
 * Set action outcome to ’success’ if all valid SIDs in the command were successfully processed by the progress action; 
 * set it to ’failure’ otherwise
 * @param smDesc the state machine descriptor
 */
void CrPsHkHkRepStructTerminationAction(FwSmDesc_t smDesc);

/**
 * Abort Action of the Command (3,9) to Report Structure of a Housekeeping Reportin-coming command packet.
 * Do nothing
 * @param smDesc the state machine descriptor
 */
void CrPsHkHkRepStructAbortAction(FwSmDesc_t smDesc);



#endif /* CRPS_HK_HKREP_STRUCT_H */
