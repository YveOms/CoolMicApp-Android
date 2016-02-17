/* %%%COPYRIGHT%%% */

/* %%%LICENSE%%% */

/*
 * This defines the API used to send a stream (IO Handle) to an Icecast server.
 * This works by setting up the object and then passing an IO Handle to it
 * to read the data from.
 * When the setup stage has completed the iteration function is called within
 * the mainloop or a thread of the application. This will let this API read
 * data of the IO Handle and send it to the Icecast server.
 */

#ifndef __COOLMIC_DSP_SHOUT_H__
#define __COOLMIC_DSP_SHOUT_H__

#include "iohandle.h"

/* forward declare internally used structures */
typedef struct coolmic_shout coolmic_shout_t;

/* public structures */
typedef struct coolmic_shout_config {
    /* connection settings */
    const char *hostname;    /* server's hostname */
    int         port;        /* server's port number */
    int         tlsmode;     /* TLS mode to use (SHOUT_TLS_*) */
    const char *cadir;       /* CA directory (default: NULL) */
    const char *cafile;      /* CA file (default: NULL) */

    /* mount point settings */
    const char *mount;       /* mount point name */

    /* credentials */
    const char *username;    /* username to login as (default: NULL) */
    const char *password;    /* password to use with username */
    const char *client_cert; /* client cerificate (TLS) (default: NULL=none) */
} coolmic_shout_config_t;

/* Management of the encoder object */
coolmic_shout_t *coolmic_shout_new(void);
int              coolmic_shout_ref(coolmic_shout_t *self);
int              coolmic_shout_unref(coolmic_shout_t *self);

/* configure remote connection */
int              coolmic_shout_set_config(coolmic_shout_t *self, const coolmic_shout_config_t *conf);

/* This is to attach the IO Handle of the Ogg data stream that is to be passed to the Icecast server */
int              coolmic_shout_attach_iohandle(coolmic_shout_t *self, coolmic_iohandle_t *handle);

/* Those two functions start and stop the connection to the server */
int              coolmic_shout_start(coolmic_shout_t *self);
int              coolmic_shout_stop(coolmic_shout_t *self);

/* This function is to iterate. It will check internal state and try to send more data
 * to the Icecast server. If needed it will read more encoded data from the IO Handle that was attached.
 */
int              coolmic_shout_iter(coolmic_shout_t *self);

#endif
