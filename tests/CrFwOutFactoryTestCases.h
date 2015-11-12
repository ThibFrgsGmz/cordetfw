/**
 * @file
 * @ingroup CrTestSuiteGroup
 * Declaration of the test cases for the OutFactory Component (see <code>CrFwOutFactory.h</code>).
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

#ifndef CRFW_OUTFACTORY_TESTCASES_H_
#define CRFW_OUTFACTORY_TESTCASES_H_

#include "CrFwConstants.h"

/**
 * Test the creation and configuration of the OutFactory singleton component.
 * The following actions are performed in this test:
 * - Create the OutFactory singleton twice and check that the same component is returned
 *   in both cases.
 * - Initialize and configure OutFactory and check that it is in state CONFIGURED.
 * - Check the correctness of the OutFactory component type identifier and instance identifier.
 * - Check that the maximum number of OutComponents which can be generated by the OutFactory
 *   is correctly reported.
 * - Check that the number of allocated OutComponents is initially equal to zero
 * .
 * @verify Base SM Transition: IPS->CREATED
 * @verify Base SM Transition: CREATED->INITIALIZED
 * @verify Base SM Transition: INITIALIZED->CONFIGURED
 * @verify Initialization Procedure: Initialization Action Successful
 * @verify Initialization Procedure: Initialization Check Successful
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutFactoryTestCase1();

/**
 * Test the OutComponent creation service in non-nominal situations where the
 * creation fails.
 * The following actions are performed in this test:
 * - Attempt to retrieve an OutComponent with a service type which is in range (smaller
 *   than the highest service type defined in <code>CrFwOutFactoryUserPar.h</code>) but
 *   is not valid.
 * - Attempt to retrieve an OutComponent with a service type which is out-of-range (greater
 *   than the highest service type defined in <code>CrFwOutFactoryUserPar.h</code>).
 * - Attempt to retrieve an OutComponent with a valid service type but with a service sub-type
 *   which is in range (smaller than the highest service sub-type defined for that type
 *   in <code>CrFwOutFactoryUserPar.h</code>) but is not valid.
 * - Attempt to retrieve an OutComponent with a valid service type but with a service sub-type
 *   which is out-of-range (greater than the highest service sub-type defined for that type
 *   in <code>CrFwOutFactoryUserPar.h</code>).
 * - Attempt to retrieve an OutComponent with a valid service type and sub-type but with a
 *   discriminant which is in range (smaller than the highest discriminant defined for that
 *   type/sub-type in <code>CrFwOutFactoryUserPar.h</code>) but is not valid.
 * - Attempt to retrieve an OutComponent with a valid service type and sub-type but with a
 *   discriminant which is out-of-range (greater than the highest discriminant defined for that
 *   type/sub-type in <code>CrFwOutFactoryUserPar.h</code>).
 * - Create <code>#CR_FW_MAX_NOF_PCKTS</code> packets and then attempt to create
 *   an OutComponent (this should fail because, for each OutComponent, a packet is
 *   required and no more packets can be created).
 * - Create <code>#CR_FW_OUTFACTORY_MAX_NOF_OUTCMP</code> OutComponents and then
 *   attempt to create one more OutComponent (this should fail because at most
 *   <code>#CR_FW_OUTFACTORY_MAX_NOF_OUTCMP</code> OutComponents can be created.
 * .
 * @verify Application Error: crIllOutCmpKind
 * @verify Application Error: crOutCmpAllocationFail
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutFactoryTestCase2();

/**
 * Test the Reset and Shutdown functions of the OutFactory component.
 * The following actions are performed in this test:
 * - Initialize and reset the OutFactory and then allocate three OutComponents.
 * - Check that the OutFactory correctly sets the source of the OutComponents.
 * - Reset the OutFactory and check that no OutComponents are any longer allocated.
 * - Allocate three OutComponents from the OutFactory and check that the instance
 *   identifiers are re-initialized.
 * - Shutdown the OutFactory and check that no OutComponents are any longer allocated.
 * - Check the state of the OutFactory and then re-start it.
 * .
 * @verify Base SM Transition: CONFIGURED->FPS
 * @verify Base SM Transition: CONFIGURED->CONFIGURED
 * @verify Reset Procedure: Configuration Action Successful
 * @verify Reset Procedure: Configuration Check Successful
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutFactoryTestCase3();

/**
 * Test the OutComponent Creation and Release functions of the OutFactory component.
 * The following actions are performed in this test:
 * - Initialize and reset the OutFactory and then allocate three OutComponents;
 *   for one of the three components, override the length specified in
 *   the <code>::CR_FW_OUTCMP_INIT_KIND_DESC</code> initializer.
 * - Check the correctness of the instance identifiers of the OutComponents.
 * - Release the OutComponents and verify that they are no longer allocated.
 * - Attempt to release an OutComponent twice and check that application error
 *   <code>:.crOutCmpRelErr</code> is generated.
 * - Allocate a number of OutComponents identical to the number of distinct instance
 *   identifiers supported by the OutFactory and then allocate one more OutComponent
 *   and check that its instance identifier is identical to that of the first
 *   OutComponent to be allocated after the OutFactory is reset.
 * .
 * @verify Application Error: crOutCmpRelErr
 *
 * @return true if the test was successful, false otherwise.
 */
CrFwBool_t CrFwOutFactoryTestCase4();

#endif /* CRFW_OUTFACTORY_TESTCASES_H_ */
