/**
 * @file CrPsCmdPrgrFailCreate.h
 * @ingroup Serv1
 * @ingroup procedures
 *
 * @brief Create one instance of the CrPsCmdPrgrFail procedure
 *
 * This header file declares the function to create one instance of the CrPsCmdPrgrFail procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsCmdPrgrFail.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: Jul 11 2017 17:58:12
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
#ifndef CRPSCMDPRGRFAIL_H_
#define CRPSCMDPRGRFAIL_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmdPrgrFail_N2 (1)		/* The identifier of action node N2 in procedure CrPsCmdPrgrFail */
#define CrPsCmdPrgrFail_N3 (2)		/* The identifier of action node N3 in procedure CrPsCmdPrgrFail */
#define CrPsCmdPrgrFail_N4 (3)		/* The identifier of action node N4 in procedure CrPsCmdPrgrFail */
#define CrPsCmdPrgrFail_N5 (4)		/* The identifier of action node N5 in procedure CrPsCmdPrgrFail */
#define CrPsCmdPrgrFail_N6 (5)		/* The identifier of action node N6 in procedure CrPsCmdPrgrFail */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmdPrgrFailCreate(void* prData);

/**
 * Action for node N2.
 * <pre>
 * Retrieve an OutComponent of
 * type (1,6) from the OutFactory
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdPrgrFailN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 * <pre>
 * Generate error report
 * OUTFACTORY_FAIL
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdPrgrFailN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 * <pre>
 * Configure report and
 * load it in the OutLoader
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdPrgrFailN4(FwPrDesc_t prDesc);

/**
 * Action for node N5.
 * <pre>
 * Increment data pool
 * variable nOfPrgrFailed
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdPrgrFailN5(FwPrDesc_t prDesc);

/**
 * Action for node N6.
 * <pre>
 * Update data pool variable
 * pcktIdPrgrFailed, failCodePrgrFailed,
 * and prgrStepFailed
 * </pre>
 * @param smDesc the procedure descriptor
 */
void CrPsCmdPrgrFailN6(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N3.
 * <pre>
 *  OutFactory fails to
 * generate OutComponent 
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsCmdPrgrFailG1(FwPrDesc_t prDesc);


#endif /* CrPsCmdPrgrFailCreate_H_ */
