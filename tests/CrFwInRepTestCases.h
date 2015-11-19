/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the InReport Component (see <code>CrFwInRep.h</code>).
 *
 * @author Vaclav Cechticky <vaclav.cechticky@pnp-software.com>
 * @author Alessandro Pasetti <pasetti@pnp-software.com>
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 *
 * This file is part of CORDET Framework.
 *
 * CORDET Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CORDET Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CORDET Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For information on alternative licensing, please contact P&P Software GmbH.
 */

#ifndef CRFW_INREP_TESTCASES_H_
#define CRFW_INREP_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Check the configuration of a newly created InReport.
 * The following actions are performed in this test:
 * - The InFactory is reset and then two InReports are retrieved from the InFactory
 *   and it is checked that their instance identifier and type identifier are correct.
 * - It is checked that the InReports are initially in state CONFIGURED.
 * - It is checked that the InReport is correctly configured.
 * - It is checked that the service type and sub-type and the discriminant value of the
 *   InReport are correct.
 * - It is checked that the InReport source, group and sequence counter are correctly set.
 * - It is checked that the acknowledge levels of the InReports are correct.
 * - It is checked that the progress step is equal to zero.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRepTestCase1();

/**
 * Check the failure of the Validity Check of an InReport.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InReport (see <code>CrFwInRepSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InReport is configured to return: "not valid" and it is checked that
 *   that the InReport is returned by the InFactory in state INITIALIZED.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRepTestCase2();

/**
 * Check the update action of an InReport.
 * The following actions are performed in this test:
 * - The InFactory is reset and then one Sample1 InReport (see <code>CrFwInRepSample1.h</code>) is
 *   retrieved from the InFactory.
 * - The validity check of the InReport is configured to return: "valid".
 * - The InReport is executed and it is checked that the Update Action has been executed once.
 * - The InReport is executed again and it is checked that the Update Action is not executed.
 * .
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwInRepTestCase3();


#endif /* CRFW_INREP_TESTCASES_H_ */