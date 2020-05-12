package gst

/*
#cgo pkg-config: gstreamer-1.0
#include "gst.h"
*/
import "C"

import (
	"runtime"
	"unsafe"
)

type Structure struct {
	C *C.GstStructure
}

func NewStructure(name string) (structure *Structure) {
	CName := (*C.gchar)(unsafe.Pointer(C.CString(name)))
	CGstStructure := C.gst_structure_new_empty(CName)

	structure = &Structure{
		C: CGstStructure,
	}

	runtime.SetFinalizer(structure, func(structure *Structure) {
		C.gst_structure_free(structure.C)
	})

	return structure
}

func (s *Structure) SetValue(name string, value interface{}) {

	CName := (*C.gchar)(unsafe.Pointer(C.CString(name)))
	defer C.g_free(C.gpointer(unsafe.Pointer(CName)))

	switch val := value.(type) {
	case string:
		str := (*C.gchar)(unsafe.Pointer(C.CString(val)))
		defer C.g_free(C.gpointer(unsafe.Pointer(str)))
		C.X_gst_structure_set_string(s.C, CName, str)
	case int:
		C.X_gst_structure_set_int(s.C, CName, C.gint(val))
	case uint32:
		C.X_gst_structure_set_uint(s.C, CName, C.guint(val))
	case bool:
		var v int
		if val {
			v = 1
		} else {
			v = 0
		}
		C.X_gst_structure_set_bool(s.C, CName, C.gboolean(v))
	}
}

func (s *Structure) ToString() (str string) {
	Cstr := C.gst_structure_to_string(s.C)
	str = C.GoString((*C.char)(unsafe.Pointer(Cstr)))
	C.g_free((C.gpointer)(unsafe.Pointer(Cstr)))

	return
}
