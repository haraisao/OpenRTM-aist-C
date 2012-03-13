/*
 * Copyright (c) 2012, AIST.
 * All rights reserved. This program is made available under the terms of the
 * Eclipse Public License v1.0 which accompanies this distribution, and is
 * available at http://www.eclipse.org/legal/epl-v10.html
 * Contributors:
 * National Institute of Advanced Industrial Science and Technology (AIST)
 */
/*!
 * \file DefaultConfig.h
 * \brief Manager用のDefaultコンフィギュレーションパラメータを定義したもの。
 * \author National Institute of Advanced Industrial Science and Technology (AIST)
 */

#ifndef RTM_DEFAULT_CONFIG_H
#define RTM_DEFAULT_CONFIG_H

static const char openrtm_version[] = "1.0";
static const char openrtm_name[] = "OpenRTM-aist-C-1.0";
static const char corba_name[] = "RtORB-1.0";

/*!
 * @brief Manager用 デフォルト・コンフィギュレーションパラメータ。["名称"/"データ"]のセット
 */
static const char* default_config[] =
{
  "config.version",                     openrtm_version,
  "openrtm.version",                    openrtm_name,
  "manager.instance_name",              "manager",
  "manager.name",                       "manager",
  "manager.naming_formats",             "%h.host_cxt/%n.mgr",
  "manager.pid",                        "",
  "manager.refstring_path",             "/var/log/rtcmanager.ref",
  "os.name",                            "",
  "os.release",                         "",
  "os.version",                         "",
  "os.arch",                            "",
  "os.hostname",                        "",
  "logger.enable",                      "YES",
  "logger.file_name",                   "./rtc%p.log",
  "logger.date_format",                 "%b %d %H:%M:%S.%Q",
  "logger.log_level",                   "INFO",
  "logger.stream_lock",                 "NO",
  "logger.master_logger",               "",
  "module.conf_path",                   "",
  "module.load_path",                   "",
  "naming.enable",                      "YES",
  "naming.type",                        "corba",
  "naming.formats",                     "%h.host_cxt/%n.rtc",
  "naming.update.enable",               "YES",
  "naming.update.interval",             "10.0",
  "timer.enable",                       "YES",
  "timer.tick",                         "0.1",
  "corba.args",                         "",
  "corba.endpoint",                     "",  /*:port_number */
  "corba.id",                           corba_name,
  "corba.nameservers",                  "localhost:2809",
  "corba.master_manager",               "localhost:2810",
  "corba.nameservice.replace_endpoint", "NO",
  "exec_cxt.periodic.type",             "PeriodicExecutionContext",
  "exec_cxt.periodic.rate",             "1000",
  "exec_cxt.evdriven.type",             "EventDrivenExecutionContext",
  "manager.modules.load_path",          "./",
  "manager.modules.abs_path_allowed",   "YES",
  "manager.is_master",                  "NO",
  "manager.corba_servant",              "YES",
  "manager.shutdown_on_nortcs",         "YES",
  "manager.shutdown_auto",              "YES",
  "manager.name",                       "manager",
  "manager.command",                    "rtcd",
  "manager.supported_languages",        "C++, Python, Java",
  "manager.modules.C++.manager_cmd",    "rtcd",
  "manager.modules.C++.profile_cmd",    "rtcprof",
#ifdef WIN32
  "manager.modules.C++.suffixes",       "dll",
#else
  "manager.modules.C++.suffixes",       "so",
#endif
  "manager.modules.C++.load_paths",     "./",
  "manager.modules.Python.manager_cmd", "rtcd_python",
  "manager.modules.Python.profile_cmd", "rtcprof_python",
  "manager.modules.Python.suffixes",    "py",
  "manager.modules.Python.load_paths",  "./",
  "manager.modules.Java.manager_cmd",   "rtcd_java",
  "manager.modules.Java.profile_cmd",   "rtcprof_java",
  "manager.modules.Java.suffixes",      "class",
  "manager.modules.Java.load_paths",    "./",
  NULL, NULL
};


#endif  /* RTM_DEFAULT_CONFIG_H */
