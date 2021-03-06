/* GStreamer
 * Copyright (C) 2020 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_GOVIDEOCALLBACK_H_
#define _GST_GOVIDEOCALLBACK_H_

#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>

G_BEGIN_DECLS

#define GST_TYPE_GOVIDEOCALLBACK   (gst_govideocallback_get_type())
#define GST_GOVIDEOCALLBACK(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_GOVIDEOCALLBACK,GstGoVideoCallback))
#define GST_GOVIDEOCALLBACK_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_GOVIDEOCALLBACK,GstGoVideoCallbackClass))
#define GST_IS_GOVIDEOCALLBACK(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_GOVIDEOCALLBACK))
#define GST_IS_GOVIDEOCALLBACK_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_GOVIDEOCALLBACK))

typedef struct _GstGoVideoCallback GstGoVideoCallback;
typedef struct _GstGoVideoCallbackClass GstGoVideoCallbackClass;

typedef GstFlowReturn (*gst_govideocallback_tarnsform_ip_t) (GstVideoFilter * filter,
        GstVideoFrame * frame) ;
typedef GstFlowReturn (*gst_govideocallback_tarnsform_t) (GstVideoFilter * filter,
        GstVideoFrame * inframe, GstVideoFrame * outframe) ;

void gst_govideocallback_set_tarnsform_ip_callback(GstVideoFilter * filter,
    gst_govideocallback_tarnsform_ip_t* fn, guint64 caller_id ) ;

struct _GstGoVideoCallback
{
    GstVideoFilter base_govideocallback;
    guint64 caller_id ;
    gst_govideocallback_tarnsform_ip_t ip_callback;
    gst_govideocallback_tarnsform_t callback;

};

struct _GstGoVideoCallbackClass
{
  GstVideoFilterClass base_govideocallback_class;
};

GType gst_govideocallback_get_type (void);

G_END_DECLS

#endif
