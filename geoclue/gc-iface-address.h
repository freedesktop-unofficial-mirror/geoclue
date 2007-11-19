/*
 * Geoclue
 * gc-iface-address.h - GInterface for org.freedesktop.Address
 * 
 * Author: Iain Holmes <iain@openedhand.com>
 */

#ifndef _GC_IFACE_ADDRESS_H
#define _GC_IFACE_ADDRESS_H

#include <geoclue/geoclue-types.h>

G_BEGIN_DECLS

#define GC_TYPE_IFACE_ADDRESS (gc_iface_address_get_type ())
#define GC_IFACE_ADDRESS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GC_TYPE_IFACE_ADDRESS, GcIfaceAddress))
#define GC_IFACE_ADDRESS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GC_TYPE_IFACE_ADDRESS, GcIfaceAddressClass))
#define GC_IS_IFACE_ADDRESS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GC_TYPE_IFACE_ADDRESS))
#define GC_IS_IFACE_ADDRESS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GC_TYPE_IFACE_ADDRESS))
#define GC_IFACE_ADDRESS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GC_TYPE_IFACE_ADDRESS, GcIfaceAddressClass))

typedef struct _GcIfaceAddress GcIfaceAddress; /* Dummy typedef */
typedef struct _GcIfaceAddressClass GcIfaceAddressClass;

struct _GcIfaceAddressClass {
	GTypeInterface base_iface;

	/* signals */
	void (* address_changed) (GcIfaceAddress *gc,
				  int             timestamp,
				  GHashTable     *address,
				  GeoclueAccuracy accuracy_level,
				  double          horizontal_accuracy,
				  double          vertical_accuracy);

	/* vtable */
	gboolean (*get_address) (GcIfaceAddress  *gc,
				 int             *timestamp,
				 GHashTable     **address,
				 GeoclueAccuracy *accuracy_level,
				 double          *horizontal_accuracy,
				 double          *vertical_accuracy,
				 GError         **error);
};

GType gc_iface_address_get_type (void);

G_END_DECLS

#endif
