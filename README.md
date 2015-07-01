# CollisionDetectionFPGA

The project was implemented on the ZedBoard with the Zynq-7000 AP SoC

hardware/image_filter : Fast-Hessian Detector (HLS)

hardware/image_filter_2 : Bilinear Interpolation and MSE (HLS)

hardware/project_1 : Vivado Zynq architecture

software : Software host code to run on Linaro ARM

Getting Started

	Install Linaro Ubuntu on the Zedboard
		http://wiki.analog.com/resources/tools-software/linux-software/zynq_images
		
	Put the bitstream onto the device and write it using /dev/xdevcfg

	Compile the software on the board itself and run