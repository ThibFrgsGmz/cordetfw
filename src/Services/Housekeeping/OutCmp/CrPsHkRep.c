/**
 * @file CrPsHkRep.c
 * @ingroup CrIaServices
 * @authors FW Profile code generator, P&P Software GmbH, 2015; Institute for Astrophysics, 2015-2016
 *
 * @brief Implementation of the Periodic Housekeeping Report (3,25) out-going report packet.
 *
 * @copyright
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * SERVICE 3,25 and 3,26
 */

#include "CrPsHkRep.h"

/* CrFramework includes */
#include "OutCmp/CrFwOutCmp.h"
#include "CrFwCmpData.h"
#include "Pckt/CrFwPckt.h"

/* FwProfile includes */
#include "FwPrConfig.h"
#include "FwPrCore.h"
#include "FwSmConfig.h"

#include <CrPsUserConstants.h>
#include <CrPsUtilities.h>
#include <DataPool/CrPsDp.h>
#include <DataPool/CrPsDpServHk.h>
#include <DataPool/CrPsDpServHk.h>
#include <Services/General/CrPsConstants.h>
#include <Services/General/CrPsPktServHk.h> 
#include <Services/General/CrPsPktServHkSupp.h> 
#include <Services/General/CrPsPktUtil.h> 
#include <CrPsDebug.h>

#include <stdlib.h>
#include <stdio.h>

uint32_t SampleBuffer[HK_MAX_REP][HK_MAX_N_REP][HK_MAX_N_GR][HK_N_SAMP_BUF];


CrFwBool_t CrPsHkRepEnableCheck(FwSmDesc_t smDesc)
{
  unsigned char sid, rdlSid, rdlSlot;
  CrFwBool_t rdlEnabled;

  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;

  /* The enable status is read from the isEnabled field of the Report Definition corresponding to the report’s SID */

  DEBUGP_3("CrPsHkRepEnableCheck: TBD \n");

  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Get the SID: discriminant for HK is the SID */
  sid = (unsigned char) disc;
  printf("CrPsHkRepEnableCheck: SID = %d \n", sid);

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);
      
      if (sid == rdlSid)
        break;
    }

  /* TODO: sid not found in list */
  if (rdlSlot == HK_N_REP_DEF)
    {
      DEBUGP("SID %d not found!\n", sid);
      /*SendTcStartRepFail(pckt, ACK_SID_NOT_USED, 0, (unsigned short)sid);*/ /* TODO: send TM(1,2)? */
      return 0;
    }

  /* Read the Enable status */
  rdlEnabled = getDpisEnabledItem(rdlSlot);
  printf("isEnabled in RDL[%d] = %d\n", rdlSlot, rdlEnabled);

  return rdlEnabled;
}

CrFwBool_t CrPsHkRepReadyCheck(FwSmDesc_t smDesc)
{
  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;
  prDataHkRepReadyCheck_t prData;
  unsigned char sid;

  CRFW_UNUSED(smDesc);

  /* Run the procedure Ready Check of HkRep Report of figure 9.5 */

  DEBUGP_3("CrPsHkRepReadyCheck: TBD \n");

  cmpData         = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt            = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Get the SID: discriminant for HK is the SID */
  sid = (unsigned char) disc;
  printf("CrPsHkRepReadyCheck: SID = %d \n", sid);

  /* Set prData of procedure   */
  /* initial setting of prData */
  prData.smDesc = smDesc;
  prData.sid = sid;
  FwPrSetData(prDescHkRepReadyCheck, &prData);

  FwPrExecute(prDescHkRepReadyCheck);

  cmpData = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  printf("CrPsHkRepReadyCheck: outcome = %d \n", cmpData->outcome);

  return cmpData->outcome;
}

void CrPsHkRepUpdateAction(FwSmDesc_t smDesc)
{
  unsigned char sid, rdlSid, rdlSlot;

  CrFwCmpData_t      *cmpData;
  CrFwInCmdData_t    *cmpSpecificData;
  CrFwPckt_t          pckt;
  CrFwDiscriminant_t  disc;

  uint32_t i, j, k;

  uint32_t N1, NFA, N2;
  uint16_t N1ParamId;
  uint32_t SCSampleRepNum;
  uint16_t N2ParamId;  
  size_t size;
  uint8_t N1ParamCharValue, N2ParamCharValue;
  uint16_t N1ParamShortValue, N2ParamShortValue;
  uint32_t N1ParamIntValue, N2ParamIntValue;
  uint32_t pos_data;
  unsigned int offset;

  /* Load the value of the simply-commutated data items from the data pool 
   * and that of the super-commutated data items from the Sampling Buffer 
   * associated to the report’s SID according to the Report Definition. */

  DEBUGP_3("CrPsHkRepUpdateAction: TBD \n");

  /* Get packet and discriminant */
  cmpData	        = (CrFwCmpData_t   *) FwSmGetData(smDesc);
  cmpSpecificData = (CrFwInCmdData_t *) cmpData->cmpSpecificData;
  pckt		        = cmpSpecificData->pckt;
  disc            = CrFwPcktGetDiscriminant(pckt);

  /* Set SID equal to discriminant */
  sid = (unsigned char) disc;

  /* look for the slot */
  for (rdlSlot = 0; rdlSlot < HK_N_REP_DEF; rdlSlot++)
    {

      rdlSid = getDpsidItem(rdlSlot);
      printf("SID in RDL[%d] = %d\n", rdlSlot, rdlSid);

      if (sid == rdlSid)
        break;
    }

  /* Set initial offset for first data value in packet */
  pos_data = sizeof(TmHeader_t) + 1; /* SID = disc (uchar) is just taken in data field */

  /* Get N1 (nSimple) from data pool, the number of simple commutated data items */
  N1 = getDpnSimpleItem(rdlSlot);

  if (N1!=0)
    {

      /* Get N1 parameter IDs and put the corresponding values in the out-going packet */ 
      for (i=0; i<N1; i++)
        {
          /* Get value for N1ParamId from data pool */ 
          N1ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + i);

          /* Set value in out-going packet */
          /* TODO: at which position in packet ? */
          size = getDpSize(N1ParamId);
          switch (size)
          {
            case 1:
              getDpValue(N1ParamId, &N1ParamCharValue);
              setPcktChar(pckt, pos_data, N1ParamCharValue);
              pos_data += 1;
              break;
            case 2:
              getDpValue(N1ParamId, &N1ParamShortValue);
              setPcktShort(pckt, pos_data, N1ParamShortValue);
              pos_data += 2;
              break;
            case 4:
              getDpValue(N1ParamId, &N1ParamIntValue);
              setPcktInt(pckt, pos_data, N1ParamIntValue);
              pos_data += 4;
              break;
            default:
              break;
          }
        }

    }

  NFA = getNFA(rdlSlot);
  
  if (NFA!=0)
    {
      offset = 0;

      for (k=0; k<NFA; k++)
        {
          /* Get sample repetition number (rep[1..nGroup]) */
          SCSampleRepNum = getDplstSampleRepItem(rdlSlot*HK_MAX_N_GR + k);

          /* Get N2 (nRep[1..nGroup]) */
          N2 = getDplstNSampRepItem(rdlSlot*HK_MAX_N_GR + k);

          for (i=0; i<SCSampleRepNum; i++)
            {
              for (j=0; j< N2; j++)
                {
                  N2ParamId = getDplstIdItem(rdlSlot*HK_MAX_N_ITEMS + N1 + offset + j);

                  /* Set value in out-going packet */
                  /* TODO: at which position in packet ? */
                  size = getDpSize(N2ParamId);
                  switch (size)
                  {
                    case 1:
                      /* Retrieve the i-th value of the j-th data item in the k-th group in the sampling buffer of ID l */
                      N2ParamCharValue = (uint8_t)getDpBufferElement(i, j, k, (uint32_t)getDpsampleBufIdItem(rdlSlot));
                      setPcktChar(pckt, pos_data, N2ParamCharValue);
                      pos_data += 1;
                      break;
                    case 2:
                      /* Retrieve the i-th value of the j-th data item in the k-th group in the sampling buffer of ID l */
                      N2ParamShortValue = (uint16_t)getDpBufferElement(i, j, k, (uint32_t)getDpsampleBufIdItem(rdlSlot));
                      setPcktShort(pckt, pos_data, N2ParamShortValue);
                      pos_data += 2;
                      break;
                    case 4:
                      /* Retrieve the i-th value of the j-th data item in the k-th group in the sampling buffer of ID l */
                      N2ParamIntValue = (uint32_t)getDpBufferElement(i, j, k, (uint32_t)getDpsampleBufIdItem(rdlSlot));
                      setPcktInt(pckt, pos_data, N2ParamIntValue);
                      pos_data += 4;
                      break;
                    default:
                      break;
                  }
                }
            }

          /* update offset */
          offset += N2;
        }

    }

  cmpData->outcome = 1;

  return;
}