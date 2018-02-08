/**
 * @file CrPsCmd3s1StartCreate.h
 * @ingroup Serv3
 * @ingroup procedures
 *
 * @brief Create one instance of the CrPsCmd3s1Start procedure
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Sep 6 2017 17:15:26
 *
 * @author Christian Reimers <christian.reimers@univie.ac.at>
 * @author Markus Rockenbauer <markus.rockenbauer@univie.ac.at>
 * 
 * last modification: 22.01.2018
 * 
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2018
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. 
 *
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMD3S1START_H_
#define CRPSCMD3S1START_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmd3s1Start_N1 (1)		/* The identifier of action node N1 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N2 (2)		/* The identifier of action node N2 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N3 (3)		/* The identifier of action node N3 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N4 (4)		/* The identifier of action node N4 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N6 (5)		/* The identifier of action node N6 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N7 (6)		/* The identifier of action node N7 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N8 (7)		/* The identifier of action node N8 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N9 (8)		/* The identifier of action node N9 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N10 (9)		/* The identifier of action node N10 in procedure CrPsCmd3s1Start */
#define CrPsCmd3s1Start_N11 (10)		/* The identifier of action node N11 in procedure CrPsCmd3s1Start */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmd3s1StartCreate(void* prData);

/**
 * Action for node N1.
 * <pre>
 * Set action outcome to 'failure'
 * with failure code VER_FULL_RDL
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 * <pre>
 * Retrieve a report of type (3,25)
 * or (3,26) from the OutFactory
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 *  Generate error report
 * OUTFACTORY_FAIL
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * Load the report in the OutLoader
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN4(FwPrDesc_t prDesc);

/**
 * Action for node N6.
 * <pre>
 * Set action
 * outcome to 'success'
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN6(FwPrDesc_t prDesc);

/**
 * Action for node N7.
 * <pre>
 * Set action outcome to 'failure'
 * with code VER_SID_IN_USE and load
 * SID in verFailData data pool item
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN7(FwPrDesc_t prDesc);

/**
 * Action for node N8.
 * <pre>
 * Set action outcome to 'failure'
 * with failure code VER_RDL_CONSTR and
 * load identifier of constraint in verFailData
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN8(FwPrDesc_t prDesc);

/**
 * Action for node N9.
 * <pre>
 * Set action outcome to 'failure'
 * with code VER_DUPL_DI and load
 * identiifer of duplicated DI in verFailData
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN9(FwPrDesc_t prDesc);

/**
 * Action for node N10.
 * <pre>
 * Set action outcome to 'failure'
 * with failure code VER_REP_CR_FD
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN10(FwPrDesc_t prDesc);

/**
 * Action for node N11.
 * <pre>
 * Set action outcome to 'failure'
 * with falure code VER_OUTLOADER_FD
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmd3s1StartN11(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N1.
 *  There is no free slot in the RDL 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to DECISION2.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG1E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N8.
 * <pre>
 *  One or more constraints listed 
 * in table 9.1 are not satisfied 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to DECISION3.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG2E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION3 to N7.
 * <pre>
 *  The SID in the command
 * is laready in use 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG3(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION3 to DECISION4.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG3E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION4 to N9.
 * <pre>
 *  The same data item identifier
 * appears twice in the definition
 * of the new report 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG4(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION4 to N2.
 * Else
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG4E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION5 to N3.
 * <pre>
 *  Factory fails to
 * return the report 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG5(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION5 to N4.
 *  Esle 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG5E(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION6 to N6.
 * <pre>
 * Load Operation
 * is successful  
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG6(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION6 to N11.
 *  Else 
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmd3s1StartG6E(FwPrDesc_t prDesc);

#endif /* CrPsCmd3s1StartCreate_H_ */
