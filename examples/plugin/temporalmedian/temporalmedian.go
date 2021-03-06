package main

import (
	"log"
	"os"
	"os/signal"

	"github.com/bksworm/gst"
)

func main() {
	// If you like to see youself
	// pipeline, err := gst.ParseLaunch("v4l2src device=/dev/video0 ! video/x-raw,width=320,height=240 " +
	// 	" ! videoconvert  " +
	// 	" !  video/x-raw,format=GRAY8,width=320,height=240 " +
	// 	" !  govideocallback name=gofilter ! autovideosink")

	pipeline, err := gst.ParseLaunch("videotestsrc pattern=ball " +
		" !  video/x-raw,format=I420,width=320,height=240 " +
		" !  govideocallback name=gofilter ! autovideosink")

	if err != nil {
		log.Println("pipeline create error ", err.Error())
		return
	}

	log.Println(pipeline.Name())

	element := pipeline.GetByName("gofilter")

	if element == nil {
		log.Println("pipe find element error")
		return
	}

	//plugin := NewSobelPlugin(element)
	//gst.SetVideoTransformIpCallback(plugin)

	pipeline.SetState(gst.StatePlaying)

	c := make(chan os.Signal)
	signal.Notify(c, os.Interrupt)
	go func() {
		<-c
		// Run Cleanup
		pipeline.SetState(gst.StateNull)
		os.Exit(0)
	}()

	select {}

}
