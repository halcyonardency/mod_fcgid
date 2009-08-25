/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FCGID_CONF_H
#define FCGID_CONF_H
#include "apr_user.h"
#include "fcgid_global.h"

typedef struct {
    char path[_POSIX_PATH_MAX];
    apr_ino_t inode;
    apr_dev_t deviceid;
    apr_size_t share_group_id;
} auth_conf;

typedef struct {
    char args[_POSIX_PATH_MAX];
    apr_ino_t inode;
    apr_dev_t deviceid;
    apr_size_t share_group_id;
} fcgid_wrapper_conf;

typedef struct {
    int idle_timeout;
    int idle_scan_interval;
    int busy_scan_interval;
    int proc_lifetime;
    int error_scan_interval;
    int zombie_scan_interval;
    char *sockname_prefix;
    char *shmname_path;
    int spawnscore_uplimit;
    int spawn_score;
    int termination_score;
    int time_score;
    int max_process_count;
    int max_class_process_count;
    int min_class_process_count;
    int max_request_len;
    int max_mem_request_len;
    int output_buffersize;
    int max_requests_per_process;
    apr_table_t *default_init_env;
    apr_array_header_t *pass_headers;
    int ipc_connect_timeout;
    int ipc_comm_timeout;
    int busy_timeout;
    int php_fix_pathinfo_enable;
} fcgid_server_conf;

typedef struct {
    /* wrapper */
    apr_hash_t *wrapper_info_hash;

    /* authenticator */
    auth_conf *authenticator_info;
    int authenticator_authoritative;

    /* authorizer */
    auth_conf *authorizer_info;
    int authorizer_authoritative;

    /* access check */
    auth_conf *access_info;
    int access_authoritative;
} fcgid_dir_conf;

void *create_fcgid_server_config(apr_pool_t * p, server_rec * s);
void *merge_fcgid_server_config(apr_pool_t * p, void *basev,
                                void *overridesv);

void *create_fcgid_dir_config(apr_pool_t * p, char *dummy);

const char *set_idle_timeout(cmd_parms * cmd, void *dummy,
                             const char *arg);
int get_idle_timeout(server_rec * s);

const char *set_idle_scan_interval(cmd_parms * cmd, void *dummy,
                                   const char *arg);
int get_idle_scan_interval(server_rec * s);

const char *set_busy_timeout(cmd_parms * cmd, void *dummy,
                             const char *arg);
int get_busy_timeout(server_rec * s);

const char *set_busy_scan_interval(cmd_parms * cmd, void *dummy,
                                   const char *arg);
int get_busy_scan_interval(server_rec * s);

const char *set_proc_lifetime(cmd_parms * cmd, void *dummy,
                              const char *arg);
int get_proc_lifetime(server_rec * s);

const char *set_error_scan_interval(cmd_parms * cmd, void *dummy,
                                    const char *arg);
int get_error_scan_interval(server_rec * s);

const char *set_zombie_scan_interval(cmd_parms * cmd, void *dummy,
                                     const char *arg);
int get_zombie_scan_interval(server_rec * s);

const char *set_socketpath(cmd_parms * cmd, void *dummy, const char *arg);
const char *get_socketpath(server_rec * s);

const char *set_shmpath(cmd_parms * cmd, void *dummy, const char *arg);
const char *get_shmpath(server_rec * s);

const char *set_time_score(cmd_parms * cmd, void *dummy, const char *arg);
int get_time_score(server_rec * s);

const char *set_max_request_len(cmd_parms * cmd, void *dummy,
                                const char *arg);
int get_max_request_len(server_rec * s);

const char *set_max_mem_request_len(cmd_parms * cmd, void *dummy,
                                    const char *arg);
int get_max_mem_request_len(server_rec * s);

const char *set_termination_score(cmd_parms * cmd, void *dummy,
                                  const char *arg);
int get_termination_score(server_rec * s);

const char *set_spawn_score(cmd_parms * cmd, void *dummy, const char *arg);
int get_spawn_score(server_rec * s);

const char *set_spawnscore_uplimit(cmd_parms * cmd, void *dummy,
                                   const char *arg);
int get_spawnscore_uplimit(server_rec * s);

const char *set_max_process(cmd_parms * cmd, void *dummy, const char *arg);
int get_max_process(server_rec * s);

const char *set_max_class_process(cmd_parms * cmd, void *dummy,
                                  const char *arg);
int get_max_class_process(server_rec * s);

const char *set_min_class_process(cmd_parms * cmd, void *dummy,
                                  const char *arg);
int get_min_class_process(server_rec * s);

const char *set_ipc_connect_timeout(cmd_parms * cmd, void *dummy,
                                    const char *arg);
int get_ipc_connect_timeout(server_rec * s);

const char *set_ipc_comm_timeout(cmd_parms * cmd, void *dummy,
                                 const char *arg);
int get_ipc_comm_timeout(server_rec * s);

const char *set_output_buffersize(cmd_parms * cmd, void *dummy,
                                  const char *arg);
int get_output_buffersize(server_rec * s);

const char *add_default_env_vars(cmd_parms * cmd, void *sconf,
                                 const char *name, const char *value);
apr_table_t *get_default_env_vars(request_rec * r);

const char *add_pass_headers(cmd_parms * cmd, void *sconf,
                             const char *name);

apr_array_header_t *get_pass_headers(request_rec * r);

const char *set_wrapper_config(cmd_parms * cmd, void *dummy,
                               const char *wrapper, const char *extension);
fcgid_wrapper_conf *get_wrapper_info(const char *cgipath, request_rec * r);

const char *set_authenticator_info(cmd_parms * cmd, void *config,
                                   const char *arg);
const char *set_authenticator_authoritative(cmd_parms * cmd,
                                            void *config, int arg);
auth_conf *get_authenticator_info(request_rec * r, int *authoritative);

const char *set_authorizer_info(cmd_parms * cmd, void *config,
                                const char *arg);
const char *set_authorizer_authoritative(cmd_parms * cmd,
                                         void *config, int arg);
auth_conf *get_authorizer_info(request_rec * r, int *authoritative);

const char *set_access_info(cmd_parms * cmd, void *config,
                            const char *arg);
const char *set_access_authoritative(cmd_parms * cmd,
                                     void *config, int arg);
auth_conf *get_access_info(request_rec * r, int *authoritative);

const char *set_php_fix_pathinfo_enable(cmd_parms * cmd, void *dummy,
                                        const char *arg);
int get_php_fix_pathinfo_enable(server_rec * s);

const char *set_max_requests_per_process(cmd_parms * cmd, void *dummy,
                                         const char *arg);
int get_max_requests_per_process(server_rec * s);

#endif