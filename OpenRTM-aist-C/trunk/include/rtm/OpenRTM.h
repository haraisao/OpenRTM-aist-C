/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file OpenRTM.h
 * \brief OpenRTM-aist-Cのメインヘッダファイル
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_RTM_H
#define RTM_RTM_H

#include <stdio.h>
#include <stdint.h>

#include <rtm/rtm-defs.h>
#include <rtm/OpenRTM-aist.h>
#include <rtm/OpenRTM-aist-decls.h>

#include <rtm/Properties.h>
#include <rtm/NVUtil.h>

#include <rtm/Manager.h>
#include <rtm/RTObject.h>
#include <rtm/NamingManager.h>

#include <rtm/RTComp.h>
#include <rtm/Port.h>
#include <rtm/ExecutionContext.h>

typedef CORBA_RTC_RTObject RTC_RtcBase; /* Base Interface */

#endif /* RTM_RTM_H */
