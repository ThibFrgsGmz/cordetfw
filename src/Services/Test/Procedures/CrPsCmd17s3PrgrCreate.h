/**
 * @file CrPsCmd17s3PrgrCreate.h
 * This header file declares the function to create one instance of the CrPsCmd17s3Prgr procedure.
 * The procedure is configured with a set of function pointers representing the non-default
 * actions and guards of the procedure. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the procedure in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The procedure created bCrPsCmd17s3StartCreate.hy this file is shown in the figure below.
 * @image html CrPsCmd17s3Prgr.png
 *
 * @author FW Profile code generator version 5.01
 * @date Created on: May 23 2017 23:43:35
 * @author C. Reimers and M. Rockenbauer 13.06.2017
 * @copyright P&P Software GmbH, 2015 / Department of Astrophysics, University of Vienna, 2017
 */

/** Make sure to include this header file only once */
#ifndef CRPSCMD17S3PRGR_H_
#define CRPSCMD17S3PRGR_H_

/** FW Profile function definitions */
#include "FwPrConstants.h"

/** Action node identifiers */
#define CrPsCmd17s3Prgr_N1 (1)		/* The identifier of action node N1 in procedure CrPsCmd17s3Prgr */
#define CrPsCmd17s3Prgr_N2 (2)		/* The identifier of action node N2 in procedure CrPsCmd17s3Prgr */
#define CrPsCmd17s3Prgr_N3 (3)		/* The identifier of action node N3 in procedure CrPsCmd17s3Prgr */
#define CrPsCmd17s3Prgr_N4 (4)		/* The identifier of action node N4 in procedure CrPsCmd17s3Prgr */

/**
 * Create a new procedure descriptor.
 * This interface creates the procedure descriptor dynamically.
 * @param prData the pointer to the procedure data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the procedure data when the procedure is created is NULL).
 * @return the pointer to the procedure descriptor
 */
FwPrDesc_t CrPsCmd17s3PrgrCreate(void* prData);

/**
 * Action for node N1.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionPrgrN1(FwPrDesc_t prDesc);

/**
 * Action for node N2.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionPrgrN2(FwPrDesc_t prDesc);

/**
 * Action for node N3.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionPrgrN3(FwPrDesc_t prDesc);

/**
 * Action for node N4.
 *
 * @param smDesc the procedure descriptor
 */
void CrPsTestOnBoardConnectionPrgrN4(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N1.
 * <pre>
 *
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG11(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N2.
 * <pre>
 *
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG12(FwPrDesc_t prDesc);

/**
 * Guard on the Control Flow from DECISION1 to N3.
 * <pre>
 *
 * </pre>
 * @param smDesc the procedure descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwPrBool_t CrPsTestOnBoardConnectionPrgrG13(FwPrDesc_t prDesc);

#endif /* CrPsCmd17s3PrgrCreate_H_ */
