/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file rtm-defs.h
 * \brief OpenRTM-aist-Cでの共通define用ファイル
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_RTMDEFS_H
#define RTM_RTMDEFS_H

#include <rtm/typedefs.h>

/*!
 * \enum ECMode_t
 * \brief CORBA_ORB running Mode (Manager)
 */
typedef enum {
  RTC_MGR_NON_BLOCKING=0,
  RTC_MGR_BLOCKING
} ECMode_t;

#endif /* RTM_RTMDEFS_H */
