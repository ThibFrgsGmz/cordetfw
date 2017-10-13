/**
 * @file
 * This header file declares the function to create one instance of the CrPsCmd3s10Start procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsCmd3s10Start.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:16:40
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMD3S10START_H_
#define CRPSCMD3S10START_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmd3s10Start_N1 (1)		/* The identifier of action node N1 in procedure CrPsCmd3s10Start */
#define CrPsCmd3s10Start_N2 (2)		/* The identifier of action node N2 in procedure CrPsCmd3s10Start */
#define CrPsCmd3s10Start_N3 (3)		/* The identifier of action node N3 in procedure CrPsCmd3s10Start */
#define CrPsCmd3s10Start_N4 (4)		/* The identifier of action node N4 in procedure CrPsCmd3s10Start */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmd3s10StartCreate(void* prData);

/**
 * Action for node N1.
 * <pre>
 * Determine the
 * identifier of the LPT Buffer 
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s10StartN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 * <pre>
 * Set action 
 * outcome to 'Failure'
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s10StartN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Set lptFailCode
 * to PART_NMB_ERR
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s10StartN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * <pre>
 * Set action
 * outcome to 'Success'
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s10StartN4(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N2.
 * <pre>
 * LPT State Machine associated
 * to LPT Buffer is not in 
 * state UP_TRANSFER 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s10StartG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to DECISION2.
 * Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s10StartG1E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N3.
 * Flag_1 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s10StartG2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N4.
 * Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s10StartG2E(FwPrDesc_t prDesc);

#endif /* CrPsCmd3s10StartCreate_H_ */