/**
 * \file
 *
 * Interface for accessing data pool items.
 *
 * \note This file was generated on 2017-09-25 14:26:59
 * \author PnP Generator
 * \copyright (c) Copyright
 */
#ifndef CRPSDPSERVTEST_H_
#define CRPSDPSERVTEST_H_

#include "CrPsDpTypes.h"

/**
 * Type description
 */
typedef struct {
  /**
   * Time-out for the Are-You-Alive Test initiated in response to an
   * Is-Application-Process-Alive Test
   */
  uint32_t AreYouAliveTimeOut;
  /**
   * List of identifiers of target applications for an On-Board-Connection
   * Test
   */
  uint16_t OnBoardConnectDestLst[10];
} DpServTestParams_t;

/**
 * Type description
 */
typedef struct {
  /**
   * Source of the latest (17,2) report received in response to a (17,1)
   * command triggered by a (17,3) command
   */
  uint16_t AreYouAliveSrc;
  /**
   * Destination of the (17,1) triggered by a (17,3) command
   */
  uint16_t OnBoardConnectDest;
} DpServTestVars_t;

extern DpServTestParams_t dpServTestParams;
extern DpServTestVars_t dpServTestVars;

/**
 * Initialises ServTest
 */
void initDpServTest(void);

/**
 * Gets the value of the datapool item AreYouAliveTimeOut
 * \return The value of datapool item AreYouAliveTimeOut
 */
static inline uint32_t getDpAreYouAliveTimeOut()
{
  return dpServTestParams.AreYouAliveTimeOut;
}

/**
 * Sets the value of the datapool item AreYouAliveTimeOut
 * \param AreYouAliveTimeOut The value to be stored into the datapool item
 * AreYouAliveTimeOut.
 */
static inline void setDpAreYouAliveTimeOut(uint32_t AreYouAliveTimeOut)
{
  dpServTestParams.AreYouAliveTimeOut = AreYouAliveTimeOut;
}

/**
 * Gets the datapool array OnBoardConnectDestLst
 * \return The datapool array OnBoardConnectDestLst
 */
static inline uint16_t* getDpOnBoardConnectDestLstArray()
{
  return &dpServTestParams.OnBoardConnectDestLst[0];
}

/**
 * Gets the value of the i-th element in the datapool array
 * OnBoardConnectDestLst
 * \param i Index variable
 * \return The i-th element in the datapool array OnBoardConnectDestLst
 */
static inline uint16_t getDpOnBoardConnectDestLstItem(int i)
{
  return dpServTestParams.OnBoardConnectDestLst[i];
}

/**
 * Sets the value of the i-th element in the datapool array
 * OnBoardConnectDestLst
 * \param i Index variable
 * \param OnBoardConnectDestLst The value to be stored into the i-th element
 * of datapool array OnBoardConnectDestLst.
 */
static inline void setDpOnBoardConnectDestLstItem(int i, uint16_t OnBoardConnectDestLst)
{
  dpServTestParams.OnBoardConnectDestLst[i] = OnBoardConnectDestLst;
}

/**
 * Gets the value of the datapool item AreYouAliveSrc
 * \return The value of datapool item AreYouAliveSrc
 */
static inline uint16_t getDpAreYouAliveSrc()
{
  return dpServTestVars.AreYouAliveSrc;
}

/**
 * Sets the value of the datapool item AreYouAliveSrc
 * \param AreYouAliveSrc The value to be stored into the datapool item
 * AreYouAliveSrc.
 */
static inline void setDpAreYouAliveSrc(uint16_t AreYouAliveSrc)
{
  dpServTestVars.AreYouAliveSrc = AreYouAliveSrc;
}

/**
 * Gets the value of the datapool item OnBoardConnectDest
 * \return The value of datapool item OnBoardConnectDest
 */
static inline uint16_t getDpOnBoardConnectDest()
{
  return dpServTestVars.OnBoardConnectDest;
}

/**
 * Sets the value of the datapool item OnBoardConnectDest
 * \param OnBoardConnectDest The value to be stored into the datapool item
 * OnBoardConnectDest.
 */
static inline void setDpOnBoardConnectDest(uint16_t OnBoardConnectDest)
{
  dpServTestVars.OnBoardConnectDest = OnBoardConnectDest;
}


/*----------------------------------------------------------------------------*/
#endif /* CRPSDPSERVTEST_H */