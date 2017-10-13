/**
 * @file CrPsCmd17s3StartCreate.h
 * This header file declares the function to create one instance of the CrPsCmd17s3Start procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created by this file is shown in the figure below.
 * @image html CrPsCmd17s3Start.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: May 23 2017 23:40:11
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMD17S3START_H_
#define CRPSCMD17S3START_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "OutCmp/CrFwOutCmp.h" /* needed for definition of: FwSmDesc_t */

/** Action node identifiers */
#define CrPsCmd17s3Start_N1 (1)		/* The identifier of action node N1 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N2 (2)		/* The identifier of action node N2 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N3 (3)		/* The identifier of action node N3 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N4 (4)		/* The identifier of action node N4 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N5 (5)		/* The identifier of action node N5 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N7 (6)		/* The identifier of action node N7 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N8 (7)		/* The identifier of action node N8 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N9 (8)		/* The identifier of action node N9 in procedure CrPsCmd17s3Start */
#define CrPsCmd17s3Start_N10 (9)		/* The identifier of action node N10 in procedure CrPsCmd17s3Start */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmd17s3StartCreate(void* prData);

/**
 * Action for node N1.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN4(FwPrDesc_t prDesc);

/**
 * Action for node N5.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN5(FwPrDesc_t prDesc);

/**
 * Action for node N7.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN7(FwPrDesc_t prDesc);

/**
 * Action for node N8.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN8(FwPrDesc_t prDesc);

/**
 * Action for node N9.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN9(FwPrDesc_t prDesc);

/**
 * Action for node N10.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionStartN10(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N1.
 * <pre>
 *
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsTestOnBoardConnectionStartG1(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION2 to N3.
 * <pre>
 *
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsTestOnBoardConnectionStartG2(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION3 to N4.
 * <pre>
 *
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsTestOnBoardConnectionStartG3(FwPrDesc_t prDesc);

#endif /* CRPSCMD17S3START_H_ */