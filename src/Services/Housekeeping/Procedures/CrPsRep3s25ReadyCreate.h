/**
 * @file
 * This header file declares the function to create one instance of the CrPsRep3s25Ready procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsRep3s25Ready.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jan 3 2018 14:31:12
 */

/** Make sure to include this header file only once */
#ifndef CRPSREP3S25READY_H_
#define CRPSREP3S25READY_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsRep3s25Ready_N1 (1)		/* The identifier of action node N1 in procedure CrPsRep3s25Ready */
#define CrPsRep3s25Ready_N2 (2)		/* The identifier of action node N2 in procedure CrPsRep3s25Ready */
#define CrPsRep3s25Ready_N3 (3)		/* The identifier of action node N3 in procedure CrPsRep3s25Ready */
#define CrPsRep3s25Ready_N4 (4)		/* The identifier of action node N4 in procedure CrPsRep3s25Ready */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsRep3s25ReadyCreate(void* prData);

/**
 * Action for node N1.
 * Set Cycle Counter to zero
 * @param smDesc the procedure descriptor
 */
void CrPsRep3s25ReadyN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 * <pre>
 * Ready Check
 * returns 'Ready'
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsRep3s25ReadyN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Ready Check
 * returns 'Not Ready'
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsRep3s25ReadyN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * Increment Cycle Counter
 * @param smDesc the procedure descriptor
 */
void CrPsRep3s25ReadyN4(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N3.
 *  Flag_1 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsRep3s25ReadyG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N2.
 *  ! Flag_1 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsRep3s25ReadyG1E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from N4 to DECISION2.
 *  Next Execution 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsRep3s25ReadyG2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N1.
 *  (Cycle Counter == Period) && (SID is Defined) 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrIaReadyChk3s25ReadyGoToRst(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to Final Node.
 *  SID is not defined 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsRep3s25ReadyGoToFin(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to DECISION1.
 *  (Cycle Counter != Period) && (SID is Defined) 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrIaReadyChk3s25ReadyGoToDec(FwPrDesc_t prDesc);

#endif /* CrPsRep3s25ReadyCreate_H_ */
