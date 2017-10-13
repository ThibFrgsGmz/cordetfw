/**
 * @file
 * @ingroup CrTestSuiteGroup
 * The CORDET Framework defines an interface for reporting the outcome of an
 * InCommand (see <code>CrFwRepInCmdOutcome.h</code>).
 * A stub implementation for this interface is provided in <code>CrFwRepInCmdOutcomeStub.c</code>.
 * The present module defines the public functions which are implemented by
 * <code>CrFwRepInCmdOutcome.c</code> but which are not declared in <code>CrFwRepInCmdOutcome.h</code>.
 * Thus, the complete interface of the InCommand outcome reporting stub of
 * <code>CrFwRepInCmdOutcomeStub.c</code> is provided in:
 * - <code>CrFwRepInCmdOutcome.h</code> (interface defined at framework level)
 * - this module (interface defined for testing purposes)
 * .
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

#ifndef CRFW_INREPINCMDOUTCOMESTUB_H_
#define CRFW_INREPINCMDOUTCOMESTUB_H_

/* Include Framework Files */
#include "CrFwConstants.h"
#include "CrFwRepInCmdOutcome.h"
/* Include Configuration Files */
#include "CrFwUserConstants.h"

/**
 * Return the position in the InCommand Outcome Report array at which the next
 * outcome report will be written.
 * @return the position in the InCommand Outcome Report array at which the next
 * outcome report will be written
 */
CrFwCounterU2_t CrFwRepInCmdOutcomeStubGetPos();

/**
 * Reset the InCommand Outcome Reporting interface.
 * This effectively deletes all outcome reports created since the last reset.
 */
void CrFwRepInCmdOutcomeStubReset();

/**
 * Return the outcome of the InCommand Outcome Report at position
 * <code>repPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the InCommand Outcome Reporting interface.
 * @param repPos the position in the InCommand Outcome Report array
 * @return the outcome
 */
CrFwRepInCmdOutcome_t CrFwRepInCmdOutcomeStubGetOutcome(CrFwCounterU2_t repPos);

/**
 * Return the failure code of the InCommand Outcome Report at position
 * <code>repPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the InCommand Outcome Reporting interface.
 * @param repPos the position in the InCommand Outcome Report array
 * @return the failure code
 */
CrFwOutcome_t CrFwRepInCmdOutcomeStubGetFailCode(CrFwCounterU2_t repPos);

/**
 * Return the instance identifier of the InCommand Outcome Report at position
 * <code>repPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the InCommand Outcome Reporting interface.
 * @param repPos the position in the InCommand Outcome Report array
 * @return the instance identifier
 */
CrFwInstanceId_t CrFwRepInCmdOutcomeStubGetInstanceId(CrFwCounterU2_t repPos);

/**
 * Return the service type of the InCommand Outcome Report at position
 * <code>repPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the InCommand Outcome Reporting interface.
 * @param repPos the position in the InCommand Outcome Report array
 * @return the service type
 */
CrFwServType_t CrFwRepInCmdOutcomeStubGetServType(CrFwCounterU2_t repPos);

/**
 * Return the service sub-type of the InCommand Outcome Report at position
 * <code>repPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the InCommand Outcome Reporting interface.
 * @param repPos the position in the InCommand Outcome Report array
 * @return the service sub-type
 */
CrFwServSubType_t CrFwRepInCmdOutcomeStubGetServSubType(CrFwCounterU2_t repPos);

/**
 * Return the discriminant of the InCommand Outcome Report at position
 * <code>repPos</code>.
 * This function is provided for convenience during testing.
 * It is not part of the InCommand Outcome Reporting interface.
 * @param repPos the position in the InCommand Outcome Report array
 * @return the service type
 */
CrFwDiscriminant_t CrFwRepInCmdOutcomeStubGetDiscriminant(CrFwCounterU2_t repPos);

#endif /* CRFW_INREPINCMDOUTCOMESTUB_H_ */