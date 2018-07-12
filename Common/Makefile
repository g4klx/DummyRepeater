OBJECTS = AddressTextCtrl.o ArduinoController.o Bleeper.o CallsignTextCtrl.o CCITTChecksumReverse.o DongleThread.o DummyController.o \
	  DV3000Controller.o DV3000NetworkController.o DV3000SerialController.o DV3000Thread.o DVDongleController.o DVDongleThread.o \
	  DVMEGAAMBEController.o DVMEGAAMBEThread.o ExternalController.o FIRFilter.o HardwareController.o HeaderData.o K8055Controller.o \
	  Logger.o MessageData.o MessageTextCtrl.o PortTextCtrl.o RepeaterProtocolHandler.o RestrictedTextCtrl.o SerialDataController.o \
	  SerialLineController.o SerialPortSelector.o SlowDataDecoder.o SlowDataEncoder.o SoundCardReaderWriter.o STARDVController.o \
	  STARDVNetworkController.o STARDVThread.o Timer.o UDPReaderWriter.o URIUSBController.o Utils.o

all:		Common.a

Common.a:	$(OBJECTS)
		$(AR) rcs Common.a $(OBJECTS)

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

clean:
		$(RM) Common.a *.o *.d *.bak *~

