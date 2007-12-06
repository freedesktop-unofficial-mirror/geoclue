/*
 * Geoclue
 * geoclue-address.c - Client API for accessing GcIfaceAddress
 *
 * Author: Iain Holmes <iain@openedhand.com>
 * Copyright 2007 by Garmin Ltd. or its subsidiaries
 */

/**
 * SECTION:geoclue-address
 * @short_description: Geoclue address client API
 *
 * #GeoclueAddress contains Address-related methods and signals. 
 * It is part of the Geoclue public client API which uses the D-Bus 
 * API to communicate with the actual provider.
 * 
 * After a #GeoclueAddress is created with geoclue_address_new(), the 
 * geoclue_address_get_address() method and the AddressChanged signal
 * can be used to obtain the current address.
 */

#include <geoclue/geoclue-address.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-address-bindings.h"

typedef struct _GeoclueAddressPrivate {
	int dummy;
} GeoclueAddressPrivate;

enum {
	ADDRESS_CHANGED,
	LAST_SIGNAL
};

static guint32 signals[LAST_SIGNAL] = {0, };

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_ADDRESS, GeoclueAddressPrivate))

#define GEOCLUE_ADDRESS_TYPE (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_STRING))

G_DEFINE_TYPE (GeoclueAddress, geoclue_address, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_address_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_address_parent_class)->dispose (object);
}

static void
address_changed (DBusGProxy      *proxy,
		 int              timestamp,
		 GPtrArray       *details,
		 GPtrArray       *accuracy,
		 GeoclueAddress *address)
{
	g_signal_emit (address, signals[ADDRESS_CHANGED], 0, 
		       timestamp, address, accuracy);
}

static GObject *
constructor (GType                  type,
	     guint                  n_props,
	     GObjectConstructParam *props)
{
	GObject *object;
	GeoclueProvider *provider;

	object = G_OBJECT_CLASS (geoclue_address_parent_class)->constructor
		(type, n_props, props);
	provider = GEOCLUE_PROVIDER (object);

	dbus_g_proxy_add_signal (provider->proxy, "AddressChanged",
				 G_TYPE_INT, GEOCLUE_ADDRESS_TYPE,
				 GEOCLUE_ACCURACY_TYPE,
				 G_TYPE_INVALID);
	dbus_g_proxy_connect_signal (provider->proxy, "AddressChanged",
				     G_CALLBACK (address_changed),
				     object, NULL);

	return object;
}

static void
geoclue_address_class_init (GeoclueAddressClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;
	o_class->constructor = constructor;

	g_type_class_add_private (klass, sizeof (GeoclueAddressPrivate));

	signals[ADDRESS_CHANGED] = g_signal_new ("address-changed",
						 G_TYPE_FROM_CLASS (klass),
						 G_SIGNAL_RUN_FIRST |
						 G_SIGNAL_NO_RECURSE,
						 G_STRUCT_OFFSET (GeoclueAddressClass, address_changed), 
						 NULL, NULL,
						 geoclue_marshal_VOID__INT_BOXED_BOXED,
						 G_TYPE_NONE, 3,
						 G_TYPE_INT, 
						 dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_STRING),
						 dbus_g_type_get_collection ("GPtrArray", GEOCLUE_ACCURACY_TYPE));
}

static void
geoclue_address_init (GeoclueAddress *address)
{
}

/**
 * geoclue_address_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeoclueAddress with given D-Bus service name and path.
 * 
 * Return value: Pointer to a new #GeoclueAddress
 */
GeoclueAddress *
geoclue_address_new (const char *service,
		     const char *path)
{
	return g_object_new (GEOCLUE_TYPE_ADDRESS,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_ADDRESS_INTERFACE_NAME,
			     NULL);
}

/**
 * geoclue_address_get_address:
 * @address: A #GeoclueAddress object
 * @timestamp: Pointer to returned Unix timestamp
 * @details: Pointer to returned hashtable with address details
 * @accuracy: Pointer to returned #GeoclueAccuracy
 * @error: Pointer to returned #Gerror
 * 
 * Obtains the current address. @timestamp will contain the time of 
 * the actual address measurement. @accuracy is a rough estimate of the
 * accuracy of the current address information. details is a hashtable 
 * with the address data, see geoclue-types.h for the hashtable keys.
 * 
 * If the caller is not interested in some values, the pointers can be 
 * left %NULL.
 * 
 * Return value: #TRUE if there is no @error
 */
gboolean
geoclue_address_get_address (GeoclueAddress   *address,
			     int              *timestamp,
			     GHashTable      **details,
			     GeoclueAccuracy **accuracy,
			     GError          **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (address);

	if (!org_freedesktop_Geoclue_Address_get_address (provider->proxy,
							  timestamp, details,
							  accuracy, error)) {
		return FALSE;
	}

	return TRUE;
}
