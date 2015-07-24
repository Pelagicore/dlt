#include <stdio.h>
#include <gtest/gtest.h>

extern "C" {
#include "dlt_daemon_common.h"
#include "dlt_daemon_common_cfg.h"
#include "dlt_user_shared_cfg.h"
#include "errno.h"
#include <syslog.h>
#include "dlt_types.h"
#include "dlt-daemon.h"
#include "dlt-daemon_cfg.h"
#include "dlt_daemon_common_cfg.h"
#include "dlt_daemon_socket.h"
#include "dlt_daemon_serial.h"
#include "dlt_daemon_client.h"
#include "dlt_offline_trace.h"
}

/* Begin Method:dlt_daemon_common::dlt_daemon_application_add */
TEST(t_dlt_daemon_application_add, normal)
{
    DltDaemon daemon;
    const char * apid = "TEST";
    pid_t pid = 0;
    const char * desc = "HELLO_TEST";
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    //printf("### APP: APID=%s  DESCR=%s NUMCONTEXT=%i PID=%i USERHANDLE=%i\n", app->apid,app->application_description, app->num_contexts, app->pid, app->user_handle);
    EXPECT_STREQ(apid, app->apid);
    EXPECT_STREQ(desc, app->application_description);
    EXPECT_EQ(pid, app->pid);
    EXPECT_LE(0, dlt_daemon_application_del(&daemon,app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Apid > 4, expected truncate to 4 char or error
    apid = "TO_LONG";
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    char  tmp[5];
    strncpy(tmp, apid, 4);
    tmp[4] = '\0';
    EXPECT_STREQ(tmp, app->apid);
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_application_add, abnormal)
{
//    DltDaemon daemon;
//    const char * apid = "TEST";
//    pid_t pid = 0;
//    const char * desc = "HELLO_TEST";
//    DltDaemonApplication *app;

    // Add the same application with same pid twice
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_LE((DltDaemonApplication *) 0, app);
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_EQ((DltDaemonApplication *) 0, app);
//    dlt_daemon_application_del(&daemon,app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Add the same applicaiotn with different pid
//    app = dlt_daemon_application_add(&daemon,(char *) apid, 0, (char *) desc, 0);
//    EXPECT_LE((DltDaemonApplication *) 0, app);
//    app = dlt_daemon_application_add(&daemon,(char *) apid, 123, (char *) desc, 0);
//    EXPECT_EQ((DltDaemonApplication *) 0, app);
//    dlt_daemon_application_del(&daemon,app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);


    // verbose value != 0 or 1
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 12345678));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Apid < 4, expected fill to 4 chars or error
//    apid = "SH";
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    char tmp[5];
//    strncpy(tmp, apid, 4);
//    tmp[4] = '\0';
//    EXPECT_STREQ(tmp, app->apid);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

}
TEST(t_dlt_daemon_application_add, nullpointer)
{
    DltDaemon daemon;
    const char * apid = "TEST";
    const char * desc = "HELLO_TEST";

    // NULL-Pointer test
    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(NULL,NULL, 0, NULL, 0));
    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(NULL,NULL, 0, (char *) desc, 0));
    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(NULL,(char *) apid, 0, NULL, 0));
    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(NULL,(char *) apid, 0, (char *) desc, 0));
    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(&daemon,NULL, 0, NULL, 0));
    EXPECT_EQ((DltDaemonApplication *)0, dlt_daemon_application_add(&daemon,NULL, 0, (char *) desc, 0));
}
/* End Method:dlt_daemon_common::dlt_daemon_application_add */




/* Begin Method: dlt_daemon_common::dlt_daemon_application_del */
TEST(t_dlt_daemon_application_del, normal)
{
    DltDaemon daemon;
    const char * apid = "TEST";
    pid_t pid = 0;
    const char * desc = "HELLO_TEST";
    DltDaemonApplication *app;

    // Normal Use-Case, retrun type cannot be tested, only apid and desc
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    EXPECT_LE(0,dlt_daemon_application_del(&daemon,app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_application_del, abnormal)
{
    DltDaemon daemon;
//    const char * apid = "TEST";
//    pid_t pid = 0;
//    const char * desc = "HELLO_TEST";
    DltDaemonApplication *app;

    // no application exists, expect < 0
    EXPECT_GE(-1, dlt_daemon_application_del(&daemon, app, 0));

    // Call delete two times
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_LE(0, dlt_daemon_application_del(&daemon,app, 0));
//    EXPECT_GE(-1, dlt_daemon_application_del(&daemon,app, 0));
//    dlt_daemon_applications_clear(&daemon, 0);


    // Verbose parameter != 0 or 1
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_GE(-1, dlt_daemon_application_del(&daemon,app, 123456789));
//    dlt_daemon_applications_clear(&daemon, 0);

}
TEST(t_dlt_daemon_application_del, nullpointer)
{
    DltDaemon daemon;
    DltDaemonApplication *app;

    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_application_del(NULL,NULL, 0));
    EXPECT_GE(-1, dlt_daemon_application_del(NULL, app , 0));
    EXPECT_GE(-1, dlt_daemon_application_del(&daemon,NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_application_del */




/* Begin Method: dlt_daemon_common::dlt_daemon_applikation_find */
TEST(t_dlt_daemon_application_find, normal)
{
    DltDaemon daemon;
    const char * apid = "TEST";
    pid_t pid = 0;
    const char * desc = "HELLO_TEST";
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    EXPECT_STREQ(apid, app->apid);
    EXPECT_STREQ(desc, app->application_description);
    EXPECT_EQ(pid, app->pid);
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Application doesn't exist, expect NULL
    EXPECT_EQ((DltDaemonApplication *) 0, dlt_daemon_application_find(&daemon, (char *) apid, 0));

    // Use a different apid, expect NULL
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    EXPECT_LE((DltDaemonApplication *) 0, dlt_daemon_application_find(&daemon, (char *) apid, 0));
    EXPECT_EQ((DltDaemonApplication *) 0, dlt_daemon_application_find(&daemon, (char *) "NEXI", 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_application_find, abnormal)
{
//    DltDaemon daemon;
//    const char * apid = "TEST";
//    pid_t pid = 0;
//    const char * desc = "HELLO_TEST";
//    DltDaemonApplication *app;

    // Verbose != 0 or 1, expect error
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    dlt_daemon_application_find(&daemon, (char *) apid, 0);
//    EXPECT_EQ((DltDaemonApplication *) 0, dlt_daemon_application_find(&daemon, (char *) apid, 123456789));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

}
TEST(t_dlt_daemon_application_find, nullpointer)
{
    DltDaemon daemon;
    const char * apid = "TEST";

    // NULL-Pointer, expected NULL
    EXPECT_EQ((DltDaemonApplication *) 0, dlt_daemon_application_find(NULL, NULL, 0));
    EXPECT_EQ((DltDaemonApplication *) 0, dlt_daemon_application_find(NULL, (char *) apid, 0));
    EXPECT_EQ((DltDaemonApplication *) 0, dlt_daemon_application_find(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_applikation_find */




/* Begin Method: dlt_daemon_common::dlt_daemon_applications_clear */
TEST(t_dlt_daemon_applications_clear, normal)
{
    DltDaemon daemon;
    pid_t pid = 0;

    // Normal Use Case, expect >= 0
    EXPECT_LE((DltDaemonApplication *) 0, dlt_daemon_application_add(&daemon, (char *) "TES1", pid, (char *) "Test clear 1", 0));
    dlt_daemon_application_add(&daemon, (char *) "TES2", pid, (char *) "Test clear 2", 0);
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_applications_clear, abnormal)
{
//    DltDaemon daemon;
//    pid_t pid = 0;

    // No applications added, expect < -1
//    EXPECT_GE(-1, dlt_daemon_applications_clear(&daemon, 0));

    // Verbose != 0 or 1, expect error
//    dlt_daemon_application_add(&daemon, (char *) "TEST", pid, (char *) "Test clear", 0);
//    EXPECT_GE(-1, dlt_daemon_applications_clear(&daemon, 123456789));
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_applications_clear, nullpointer)
{
    // NULL-Pointer, expect < 0
    EXPECT_GE(-1, dlt_daemon_applications_clear(NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_applications_clear */



/* Begin Method: dlt_daemon_common::dlt_daemon_applications_invalidate_fd */
TEST(t_dlt_daemon_applications_invalidate_fd, normal)
{
    DltDaemon daemon;
    const char * apid = "TEST";
    pid_t pid = 0;
    const char * desc = "HELLO_TEST";
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    EXPECT_LE(0, dlt_daemon_applications_invalidate_fd(&daemon, app->user_handle, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_applications_invalidate_fd, abnormal)
{
//    DltDaemon daemon;
//    const char * apid = "TEST";
//    pid_t pid = 0;
//    const char * desc = "HELLO_TEST";
//    DltDaemonApplication *app;

    // Daemon isn't initialized, expected error
//    EXPECT_GE(-1, dlt_daemon_applications_invalidate_fd(&daemon, 0, 0));

    // Verbose != 0 or 1, expect error
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_GE(-1, dlt_daemon_applications_invalidate_fd(&daemon, app->user_handle, 123456789));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_applications_invalidate_fd, nullpointer)
{
    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_applications_invalidate_fd(NULL, 0, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_applications_invalidate_fd */




/* Begin Method: dlt_daemon_common::dlt_daemon_applications_save */
TEST(t_dlt_daemon_applications_save, normal)
{
    DltDaemon daemon;
    const char * apid = "TEST";
    pid_t pid = 0;
    const char * desc = "HELLO_TEST";
    DltDaemonApplication *app;
    const char * filename = "/tmp/dlt-runtime.cfg";

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
    EXPECT_LE(0, dlt_daemon_applications_save(&daemon, (char *) filename, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_applications_save, abnormal)
{
//    DltDaemon daemon;
//    const char * apid = "TEST";
//    pid_t pid = 0;
//    const char * desc = "HELLO_TEST";
//    DltDaemonApplication *app;
//    const char * filename = "/tmp/dlt-runtime.cfg";

    // Uninitialized
//    EXPECT_GE(-1, dlt_daemon_applications_save(&daemon, (char *) filename, 0));

    // Verbose != 1 or 0, expect error
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_GE(-1, dlt_daemon_applications_save(&daemon, (char *) filename, 123456789));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Wrong path filename
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_GE(-1, dlt_daemon_applications_save(&daemon, (char *) "PATH_DONT_EXIST", 0));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_applications_save, nullpointer)
{
    DltDaemon daemon;
    const char * filename = "/tmp/dlt-runtime.cfg";

    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_applications_save(NULL, NULL, 0));
    EXPECT_GE(-1, dlt_daemon_applications_save(NULL, (char *) filename, 0));
    EXPECT_GE(-1, dlt_daemon_applications_save(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_applications_save */




/* Begin Method: dlt_daemon_common::dlt_daemon_applications_load */
TEST(t_dlt_daemon_applications_load, normal)
{
    DltDaemon daemon;
    const char * filename = "/tmp/dlt-runtime.cfg";

    // Normal Use-Case, first execute t_dlt_daemon_applications_save !!
    EXPECT_LE(0, dlt_daemon_applications_load(&daemon,(char *) filename, 0));
}
TEST(t_dlt_daemon_applications_load, abnormal)
{
//    DltDaemon daemon;
//    const char * apid = "TEST";
//    pid_t pid = 0;
//    const char * desc = "HELLO_TEST";
//    DltDaemonApplication *app;
//    const char * filename = "/tmp/dlt-runtime.cfg";

    // Uninitialized
//    EXPECT_GE(-1, dlt_daemon_applications_load(&daemon, (char *) filename, 0));

    // Verbose != 1 or 0, expect error
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_GE(-1, dlt_daemon_applications_load(&daemon, (char *) filename, 123456789));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Wrong path filename
//    app = dlt_daemon_application_add(&daemon,(char *) apid, pid, (char *) desc, 0);
//    EXPECT_GE(-1, dlt_daemon_applications_load(&daemon, (char *) "PATH_DONT_EXIST", 0));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_applications_load, nullpointer)
{
    DltDaemon daemon;
    const char * filename = "/tmp/dlt-runtime.cfg";

    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_applications_load(NULL, NULL, 0));
    EXPECT_GE(-1, dlt_daemon_applications_load(NULL, (char *) filename, 0));
    EXPECT_GE(-1, dlt_daemon_applications_load(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_applications_load */




/*##############################################################################################################################*/
/*##############################################################################################################################*/
/*##############################################################################################################################*/




/* Begin Method: dlt_daemon_common::dlt_daemon_context_add */
TEST(t_dlt_daemon_context_add, normal)
{
//  Log Level
//  DLT_LOG_DEFAULT =    		  -1,   /**< Default log level */
//	DLT_LOG_OFF     =      		0x00,   /**< Log level off */
//	DLT_LOG_FATAL   =   		0x01, 	/**< fatal system error */
//	DLT_LOG_ERROR   =   		0x02, 	/**< error with impact to correct functionality */
//	DLT_LOG_WARN    =   		0x03, 	/**< warning, correct behaviour could not be ensured */
//	DLT_LOG_INFO    =   		0x04, 	/**< informational */
//	DLT_LOG_DEBUG   =   		0x05, 	/**< debug  */
//	DLT_LOG_VERBOSE =   		0x06 	/**< highest grade of information */

//  Trace Status
//  DLT_TRACE_STATUS_DEFAULT =   -1, 	/**< Default trace status */
//	DLT_TRACE_STATUS_OFF	 = 0x00, 	/**< Trace status: Off */
//	DLT_TRACE_STATUS_ON      = 0x01 	/**< Trace status: On */

    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
    EXPECT_STREQ(apid, daecontext->apid);
    EXPECT_STREQ(ctid, daecontext->ctid);
    EXPECT_STREQ(desc, daecontext->context_description);
    EXPECT_EQ(DLT_LOG_DEFAULT, daecontext->log_level);
    EXPECT_EQ(DLT_TRACE_STATUS_DEFAULT, daecontext->trace_status);
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_context_add, abnormal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Log Level dont exists
    DltLogLevelType DLT_LOG_NOT_EXIST = (DltLogLevelType) - 100;
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_NOT_EXIST,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
    EXPECT_EQ((DltDaemonContext *) 0, daecontext);
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Trace Status dont exists
    DltTraceStatusType DLT_TRACE_TYPE_NOT_EXIST = (DltTraceStatusType) - 100;
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_TYPE_NOT_EXIST,0,0,desc,0);
    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
    EXPECT_EQ((DltDaemonContext *) 0, daecontext);
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Apid to long
//    char apid_tl[8] = "TO_LONG";
//    app = dlt_daemon_application_add(&daemon, apid_tl, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid_tl,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
//    EXPECT_STREQ(apid_tl, daecontext->apid);
//    EXPECT_STREQ(ctid, daecontext->ctid);
//    EXPECT_STREQ(desc, daecontext->context_description);
//    EXPECT_EQ(DLT_LOG_DEFAULT, daecontext->log_level);
//    EXPECT_EQ(DLT_TRACE_STATUS_DEFAULT, daecontext->trace_status);
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Apid to short
//    char apid_ts[3] = "TS";
//    app = dlt_daemon_application_add(&daemon, apid_ts, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid_ts,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
//    EXPECT_STREQ(apid_ts, daecontext->apid);
//    EXPECT_STREQ(ctid, daecontext->ctid);
//    EXPECT_STREQ(desc, daecontext->context_description);
//    EXPECT_EQ(DLT_LOG_DEFAULT, daecontext->log_level);
//    EXPECT_EQ(DLT_TRACE_STATUS_DEFAULT, daecontext->trace_status);
//    //EXPECT_EQ(4, strlen(apid_ts));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Ctid to long
//    char ctid_tl[8] = "TO_LONG";
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid_tl,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
//    EXPECT_STREQ(apid, daecontext->apid);
//    EXPECT_STREQ(ctid_tl, daecontext->ctid);
//    EXPECT_STREQ(desc, daecontext->context_description);
//    EXPECT_EQ(DLT_LOG_DEFAULT, daecontext->log_level);
//    EXPECT_EQ(DLT_TRACE_STATUS_DEFAULT, daecontext->trace_status);
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Ctid to short
//    char ctid_ts[4] = "TS";
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid_ts,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
//    EXPECT_STREQ(apid, daecontext->apid);
//    EXPECT_STREQ(ctid_ts, daecontext->ctid);
//    EXPECT_STREQ(desc, daecontext->context_description);
//    EXPECT_EQ(DLT_LOG_DEFAULT, daecontext->log_level);
//    EXPECT_EQ(DLT_TRACE_STATUS_DEFAULT, daecontext->trace_status);
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Verbose != 0 or 1
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,123456789);
//    //printf("### CONTEXT: APID=%s\tCTID=%s\n", daecontext->apid,daecontext->ctid);
//    EXPECT_EQ((DltDaemonContext *) 0, daecontext);
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_context_add, nullpointer)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";

    // NULL-Pointer
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,NULL,NULL,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,NULL,NULL,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,NULL,ctid,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,NULL,ctid,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,apid,NULL,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,apid,NULL,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,apid,ctid,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(NULL,apid,ctid,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,NULL,NULL,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,NULL,NULL,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,NULL,ctid,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,NULL,ctid,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,apid,NULL,0,0,0,0,NULL,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,apid,NULL,0,0,0,0,desc,0));
    EXPECT_EQ((DltDaemonContext *) 0, dlt_daemon_context_add(&daemon,apid,ctid,0,0,0,0,NULL,0));
}
/* End Method: dlt_daemon_common::dlt_daemon_context_add */



/* Begin Method: dlt_daemon_common::dlt_daemon_context_del */
TEST(t_dlt_daemon_context_del, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_context_del, abnormal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Context uninitialized
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));

    // No application used
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_GE(-1, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // No contex added
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Verbose != 0 or 1
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 123456789));
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_context_del, nullpointer)
{
    DltDaemon daemon;
    DltDaemonContext *daecontext;

    //NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_context_del(NULL, NULL, 0));
    EXPECT_GE(-1, dlt_daemon_context_del(NULL, daecontext, 0));
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_context_del */




/* Begin Method: dlt_daemon_common::dlt_daemon_context_find */
TEST(t_dlt_daemon_context_find, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_STREQ(apid, daecontext->apid);
    EXPECT_STREQ(ctid, daecontext->ctid);
    EXPECT_STREQ(desc, daecontext->context_description);
    EXPECT_EQ(DLT_LOG_DEFAULT, daecontext->log_level);
    EXPECT_EQ(DLT_TRACE_STATUS_DEFAULT, daecontext->trace_status);
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_context_find, abnormal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Uninitialized
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, apid, ctid, 0));

    // No apid
    char no_apid[1] = "";
    app = dlt_daemon_application_add(&daemon, no_apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,no_apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, no_apid, ctid, 0));
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_GE(-1, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // No ctid
    char no_ctid[1] = "";
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,no_ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, apid, no_ctid, 0));
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // No application added
    daecontext = dlt_daemon_context_add(&daemon,no_apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, no_apid, ctid, 0));
    EXPECT_GE(-1, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Verbose != 0 or 1
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, apid, ctid, 123456789));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_context_find, nullpointer)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";

    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(NULL, NULL, NULL, 0));
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(NULL, NULL, ctid, 0));
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(NULL, apid, NULL, 0));
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(NULL, apid, ctid, 0));
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, NULL, NULL, 0));
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, NULL, ctid, 0));
    EXPECT_EQ((DltDaemonContext *) 0 ,dlt_daemon_context_find(&daemon, apid, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_context_find */




/* Begin Method: dlt_daemon_common::dlt_daemon_contexts_clear */
TEST(t_dlt_daemon_contexts_clear, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_contexts_clear, abnormal)
{
//    DltDaemon daemon;
//    ID4 apid = "TES";
//    ID4 ctid = "CON";
//    char desc[255] = "TEST dlt_daemon_context_add";
//    DltDaemonContext *daecontext;
//    DltDaemonApplication *app;

    // No context added
//    EXPECT_GE(-1, dlt_daemon_contexts_clear(&daemon, 0));

    // Verbose != 0 or 1
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 123456789));
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_contexts_clear, nullpointer)
{
    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_contexts_clear(NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_contexts_clear */




/* Begin Method: dlt_daemon_common::dlt_daemon_contexts_invalidate_fd */
TEST(t_dlt_daemon_contexts_invalidate_fd, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_LE(0, dlt_daemon_contexts_invalidate_fd(&daemon, app->user_handle, 0));
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_contexts_invalidate_fd, abnormal)
{
//    DltDaemon daemon;
//    ID4 apid = "TES";
//    ID4 ctid = "CON";
//    char desc[255] = "TEST dlt_daemon_context_add";
//    DltDaemonContext *daecontext;
//    DltDaemonApplication *app;

    // Uninitialized
//    EXPECT_GE(-1, dlt_daemon_contexts_invalidate_fd(&daemon, app->user_handle, 0));

    // Verbose != 0 or 1
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_contexts_invalidate_fd(&daemon, app->user_handle, 123456789));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_contexts_invalidate_fd, nullpointer)
{
    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_contexts_invalidate_fd(NULL, 0, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_contexts_invalidate_fd */




/* Begin Method: dlt_daemon_common::dlt_daemon_contexts_save */
TEST(t_dlt_daemon_contexts_save, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;
    const char * filename = "/tmp/dlt-runtime-context.cfg";

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_LE(0, dlt_daemon_contexts_save(&daemon, filename, 0));
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_contexts_save, abnormal)
{
//    DltDaemon daemon;
//    ID4 apid = "TES";
//    ID4 ctid = "CON";
//    char desc[255] = "TEST dlt_daemon_context_add";
//    DltDaemonContext *daecontext;
//    DltDaemonApplication *app;
//    const char * filename = "/tmp/dlt-runtime-context.cfg";

    // Uninitialized
//    EXPECT_GE(-1, dlt_daemon_contexts_save(&daemon, filename, 0));

    // Verbose != 1 or 0, expect error
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_contexts_save(&daemon, filename, 123456789));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Wrong path filename
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_contexts_save(&daemon, (char *) "PATCH_NOT_EXISTS", 0));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_contexts_save, nullpointer)
{
    DltDaemon daemon;
    const char * filename = "/tmp/dlt-runtime-context.cfg";

    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_contexts_save(NULL, NULL, 0));
    EXPECT_GE(-1, dlt_daemon_contexts_save(NULL, filename, 0));
    EXPECT_GE(-1, dlt_daemon_contexts_save(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_contexts_save */




/* Begin Method: dlt_daemon_common::dlt_daemon_contexts_load */
TEST(t_dlt_daemon_contexts_load, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;
    const char * filename = "/tmp/dlt-runtime-context.cfg";

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_LE(0, dlt_daemon_contexts_load(&daemon, filename, 0));
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_contexts_load, abnormal)
{
//    DltDaemon daemon;
//    ID4 apid = "TES";
//    ID4 ctid = "CON";
//    char desc[255] = "TEST dlt_daemon_context_add";
//    DltDaemonContext *daecontext;
//    DltDaemonApplication *app;
//    const char * filename = "/tmp/dlt-runtime-context.cfg";

    // Uninitialized
//    EXPECT_GE(-1, dlt_daemon_contexts_load(&daemon, filename, 0));

    // Verbose != 1 or 0, expect error
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_contexts_load(&daemon, filename, 123456789));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);

    // Wrong path filename
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_contexts_load(&daemon, (char *) "PATCH_NOT_EXISTS", 0));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_contexts_load, nullpointer)
{
    DltDaemon daemon;
    const char * filename = "/tmp/dlt-runtime-context.cfg";

    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_contexts_load(NULL, NULL, 0));
    EXPECT_GE(-1, dlt_daemon_contexts_load(NULL, filename, 0));
    EXPECT_GE(-1, dlt_daemon_contexts_load(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_contexts_load */





/*##############################################################################################################################*/
/*##############################################################################################################################*/
/*##############################################################################################################################*/




/* Begin Method: dlt_daemon_common::dlt_daemon_user_send_all_log_state */
// Can't test this Method, maybe a return value would be a better solution
TEST(t_dlt_daemon_user_send_all_log_state, normal)
{
    DltDaemon daemon;

    // Normal Use-Case
    EXPECT_NO_FATAL_FAILURE(dlt_daemon_user_send_all_log_state(&daemon, 0));
}
TEST(t_dlt_daemon_user_send_all_log_state, abnormal)
{

}
TEST(t_dlt_daemon_user_send_all_log_state, nullpointer)
{
    EXPECT_NO_FATAL_FAILURE(dlt_daemon_user_send_all_log_state(NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_user_send_all_log_state */




/* Begin Method: dlt_daemon_common::dlt_daemon_user_send_default_update */
// Can't test this Method, maybe a return value would be a better solution
TEST(t_dlt_daemon_user_send_default_update, normal)
{
    DltDaemon daemon;

    // Normal Use-Case
    EXPECT_NO_FATAL_FAILURE(dlt_daemon_user_send_default_update(&daemon, 0));
}
TEST(t_dlt_daemon_user_send_default_update, abnormal)
{

}
TEST(t_dlt_daemon_user_send_default_update, nullpointer)
{
    EXPECT_NO_FATAL_FAILURE(dlt_daemon_user_send_default_update(NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_user_send_default_update */




/* Begin Method: dlt_daemon_common::dlt_daemon_user_send_log_level */
TEST(t_dlt_daemon_user_send_log_level, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Normal Use-Case
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,1,desc,0);
    EXPECT_LE(0, dlt_daemon_user_send_log_level(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
}
TEST(t_dlt_daemon_user_send_log_level, abnormal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;

    // Uninitialized
    EXPECT_GE(-1, dlt_daemon_user_send_log_level(&daemon, daecontext, 0));

    // File Handler <= 0
    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,-1,desc,0);
    EXPECT_GE(-1, dlt_daemon_user_send_log_level(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));

    // Verbose != 0 or 1
//    app = dlt_daemon_application_add(&daemon, apid, 0, desc, 0);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,1,desc,0);
//    EXPECT_GE(-1, dlt_daemon_user_send_log_level(&daemon, daecontext, 123456789));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
}
TEST(t_dlt_daemon_user_send_log_level, nullpointer)
{
    DltDaemon daemon;
    DltDaemonContext *daecontext;

    // NULL-Pointer
    EXPECT_GE(-1, dlt_daemon_user_send_log_level(NULL, NULL, 0));
    EXPECT_GE(-1, dlt_daemon_user_send_log_level(NULL, daecontext, 0));
    EXPECT_GE(-1, dlt_daemon_user_send_log_level(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_user_send_log_level */




/* Begin Method: dlt_daemon_common::dlt_daemon_user_send_log_state */
TEST(t_dlt_daemon_user_send_log_state, normal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;
    pid_t pid = 18166;
    char filename[DLT_DAEMON_COMMON_TEXTBUFSIZE+1];
    snprintf(filename,DLT_DAEMON_COMMON_TEXTBUFSIZE,"%s/dlt%d",DLT_USER_DIR,pid);

    // Normal Use-Case
//    open(filename, O_RDWR |O_NONBLOCK);
//    dlt_daemon_init(&daemon, DLT_DAEMON_RINGBUFFER_MIN_SIZE, DLT_DAEMON_RINGBUFFER_MAX_SIZE, DLT_DAEMON_RINGBUFFER_STEP_SIZE, "",0);
//    app = dlt_daemon_application_add(&daemon, apid, pid, desc, 0);
//    //printf("### USERHANDLE=%i\n", app->user_handle);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(0, dlt_daemon_user_send_log_state(&daemon, app, 0));
//    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
//    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
//    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
//    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
//    EXPECT_LE(0, close(app->user_handle));
}
TEST(t_dlt_daemon_user_send_log_state, abnormal)
{
    DltDaemon daemon;
    ID4 apid = "TES";
    ID4 ctid = "CON";
    char desc[255] = "TEST dlt_daemon_context_add";
    DltDaemonContext *daecontext;
    DltDaemonApplication *app;
    pid_t pid = 18166;
    char filename[DLT_DAEMON_COMMON_TEXTBUFSIZE+1];
    snprintf(filename,DLT_DAEMON_COMMON_TEXTBUFSIZE,"%s/dlt%d",DLT_USER_DIR,pid);

    //Uninitialized
    EXPECT_GE(-1, dlt_daemon_user_send_log_state(&daemon, app, 0));

    // No Pipe open
    //open(filename, O_RDWR |O_NONBLOCK);
    dlt_daemon_init(&daemon, DLT_DAEMON_RINGBUFFER_MIN_SIZE, DLT_DAEMON_RINGBUFFER_MAX_SIZE, DLT_DAEMON_RINGBUFFER_STEP_SIZE, "",0);
    app = dlt_daemon_application_add(&daemon, apid, pid, desc, 0);
    //printf("### USERHANDLE=%i\n", app->user_handle);
    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
    EXPECT_GE(-1, dlt_daemon_user_send_log_state(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_context_del(&daemon, daecontext, 0));
    EXPECT_LE(0, dlt_daemon_application_del(&daemon, app, 0));
    EXPECT_LE(0, dlt_daemon_contexts_clear(&daemon, 0));
    EXPECT_LE(0, dlt_daemon_applications_clear(&daemon, 0));
    EXPECT_LE(0, close(app->user_handle));

    // Verbose != 1 or 0
//    open(filename, O_RDWR |O_NONBLOCK);
//    dlt_daemon_init(&daemon, DLT_DAEMON_RINGBUFFER_MIN_SIZE, DLT_DAEMON_RINGBUFFER_MAX_SIZE, DLT_DAEMON_RINGBUFFER_STEP_SIZE, "",0);
//    app = dlt_daemon_application_add(&daemon, apid, pid, desc, 0);
//    //printf("### USERHANDLE=%i\n", app->user_handle);
//    daecontext = dlt_daemon_context_add(&daemon,apid,ctid,DLT_LOG_DEFAULT,DLT_TRACE_STATUS_DEFAULT,0,0,desc,0);
//    EXPECT_GE(-1, dlt_daemon_user_send_log_state(&daemon, app, 123456789));
//    dlt_daemon_context_del(&daemon, daecontext, 0);
//    dlt_daemon_application_del(&daemon, app, 0);
//    dlt_daemon_contexts_clear(&daemon, 0);
//    dlt_daemon_applications_clear(&daemon, 0);
//    close(app->user_handle);
}
TEST(t_dlt_daemon_user_send_log_state, nullpointer)
{
    DltDaemon daemon;
    DltDaemonApplication *app;

    EXPECT_GE(0, dlt_daemon_user_send_log_state(NULL, NULL, 0));
    EXPECT_GE(0, dlt_daemon_user_send_log_state(NULL, app, 0));
    EXPECT_GE(0, dlt_daemon_user_send_log_state(&daemon, NULL, 0));
}
/* End Method: dlt_daemon_common::dlt_daemon_user_send_log_state */




/*##############################################################################################################################*/
/*##############################################################################################################################*/
/*##############################################################################################################################*/




int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_break_on_failure = true;
    //::testing::FLAGS_gtest_filter = "*.normal";
    //::testing::FLAGS_gtest_repeat = 10000;
    return RUN_ALL_TESTS();
}
