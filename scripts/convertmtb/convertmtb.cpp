/*
Program             : C++ program to convert XSens MTB files to text files
Requested libraries : Provided by MT Software Suite 4.8
Author              : J. Vandenplas
Date                : 16 November 2018
in.a. Changed Yam to Yaw
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <xsensdeviceapi.h>
#include <service.h>

std::string datasetFileName = "MT_0120067F_001.mtb";

int main(int argc, char *argv[])
{
    checkArguments(argc, argv, 1, &datasetFileName);
    std::cout << "\n Received " << datasetFileName << "\n\n";
    XsString path = XsString(datasetFileName);

    XsControl* control = XsControl::construct(); assert(control != 0);
    if(control == 0)
    {
     std::cout << "Failed to construct the XsControl instance";
    }

    if(control->openLogFile(path))
    {
        std::cout << " Open LogFile successful\n\n";

        XsDeviceIdArray dev = control->mainDeviceIds();
	std::cout << " Number of main device Ids: "<< dev.size() <<std::endl ;
  
        if(dev.size()!=1)
        {
         std::cout <<" ERROR: This program can work with only one single device";
         return 1;
        }

	XsDeviceId deviceid(dev[0]);
	std::cout << " Device Id "<<deviceid <<"\n\n";
	XsDevice* device =control->device(deviceid);

	device->setOptions(XSO_RetainRecordingData,XSO_None);
	device->setOptions(XSO_Orientation,XSO_None);

	if(device->loadLogFile()) std::cout <<" File loading...\n\n";

        while(device->isLoadLogFileInProgress())
        {
         device->waitForLoadLogFileDone();
        }
        //std::cout << " Press [ENTER] to continue." << std::endl; std::cin.get();
        /*
        //Stupid loop to wait file loaded
        float val(0);
        for(size_t i=0;i<5000000000000;i++)
        {
          val+=1.;
        }
        */

	XsDevicePtrArray childDevice=device->children();
        std::cout << " Number of child devices: "<<childDevice.size()<<"\n\n";
        for (XsSize i=0;i<childDevice.size();i++)
        {
         XsDevice* cdevice=childDevice[i];
	 XsDeviceId cdeviceid(cdevice->deviceId());
  	 std::cout << " Child device Id "<<cdeviceid <<"\n";
	 std::cout << "  Number of Packets: " << cdevice->getDataPacketCount() <<"\n\n";

         XsString ff(path+"_"+cdeviceid.toString()+".txt");
         std::ofstream outputlog(ff.c_str());

         outputlog << "\n\n\n\n" ;
         outputlog << "PackedCounter"<<" " ;
         outputlog << "SampleTimeFine"<<" " ;
         outputlog << "UTC_Nano UTC_Year UTC_Month UTC_Day UTC_Hour UTC_Minute UTC_Second UTC_Valid"<<" " ;
         outputlog << "StatusWord"<<" " ;
         outputlog << "RSSI"<<" " ;
         outputlog << "Acc_X Acc_Y Acc_Z"<<" " ;
         outputlog << "FreeAcc_X FreeAcc_Y FreeAcc_Z"<<" ";
         outputlog << "Gyr_X Gyr_Y Gyr_Z Mag_X Mag_Y Mag_Z "<<" ";
        
         outputlog << "VelInc_X VelInc_Y VelInc_Z OriInc_q0 OriInc_q1 OriInc_q2 OriInc_q3"<<" " ;
         outputlog << "Pressure"<<" " ;
         outputlog << "Roll Pitch Yaw"<<" " ;
         outputlog << "Latitude Longitude"<<" " ;
         outputlog << "Altitude"<<" " ;
//         outputlog << ""<<" " ;
//         outputlog << ""<<" " ;
 

         //Not sure to what they correspond
         outputlog << "calibacc0 calibacc1 calibacc2"<<" " ;
         outputlog << "calimgf0 calimgf1 calimgf2"<<" " ;
         outputlog<<"\n";

         //Extraction
         for (XsSize index=0;index<cdevice->getDataPacketCount();index++)
         {
	  XsDataPacket packet(cdevice->getDataPacketByIndex(index));

	  if(packet.containsPacketCounter())
          {
           outputlog<<packet.packetCounter()<<" ";
          }
          else
          {
           outputlog<<"NaN ";
          }

          if(packet.containsSampleTimeFine())
          {
           outputlog<<packet.sampleTimeFine()<<" ";
          }
          else
          {
           outputlog<<"NaN ";
          }

  	  if(packet.containsUtcTime())
          {
           outputlog<<packet.utcTime().m_nano
               <<packet.utcTime().m_year
               <<packet.utcTime().m_month
               <<packet.utcTime().m_day
               <<packet.utcTime().m_hour
               <<packet.utcTime().m_minute
               <<packet.utcTime().m_second
               <<packet.utcTime().m_valid
               <<" ";
          }
          else
          {
           for(size_t ind=0;ind<8;ind++)outputlog<<"NaN ";
          }

          if(packet.containsStatus())
          {
           outputlog<<packet.status() <<" ";
          }
          else
          {
           outputlog<<"NaN ";
          }

          if(packet.containsRssi())
          {
           outputlog<<packet.rssi()<<" ";
          }
          else
          {
           outputlog<<"NaN ";
          }

          if(packet.containsCalibratedData())
          {
           XsVector3 vect=packet.calibratedData().m_acc;
           for (XsSize ind(0);ind<vect.size();ind++)
           {
            outputlog << vect[ind]<<" ";
           }
          }
          else
          {
           for(size_t ind=0;ind<3;ind++)outputlog<<"NaN ";
          }

          if(packet.containsFreeAcceleration())
          {
           XsVector vect=packet.freeAcceleration();
           for (XsSize ind(0);ind<vect.size();ind++)
           {
            outputlog << vect[ind]<<" ";
           }
          }
          else
          {
           for(size_t ind=0;ind<3;ind++)outputlog<<"NaN ";
          }

          if(packet.containsCalibratedData())
          {
           XsVector3 vect1=packet.calibratedData().m_gyr;
           for (XsSize ind(0);ind<vect1.size();ind++)
           {
            outputlog << vect1[ind]<<" ";
           }
           XsVector3 vect2=packet.calibratedData().m_mag;
           for (XsSize ind(0);ind<vect2.size();ind++)
           {
            outputlog << vect2[ind]<<" ";
           }
          }
          else
          {
           for(size_t ind=0;ind<6;ind++)outputlog<<"NaN ";
          }

  	  if(packet.containsSdiData())
          {
           XsSdiData sdidata=packet.sdiData();
           outputlog << sdidata.velocityIncrement()[0] <<" "<< sdidata.velocityIncrement()[1] <<" "<< sdidata.velocityIncrement()[2] <<" ";
           outputlog << sdidata.orientationIncrement().w()<<" "<<sdidata.orientationIncrement().x() << " " << sdidata.orientationIncrement().y() << " " <<sdidata.orientationIncrement().z() <<" ";
          }
          else
          {
           for(size_t ind=0;ind<7;ind++)outputlog<<"NaN ";
          }

          if(packet.containsPressure())
          {
           outputlog<<packet.pressure().m_pressure <<" ";
          }
          else
          {
           outputlog<<"NaN  ";
          }
  
          if(packet.containsOrientation())
          {
           XsEuler euler=packet.orientationEuler();
           outputlog << euler.roll() << " "<< euler.pitch() <<" "<< euler.yaw() <<" ";
          }
          else
          {
           for(size_t ind=0;ind<3;ind++)outputlog<<"NaN ";
          }
 
          if(packet.containsLatitudeLongitude())
          {
           XsVector vect=packet.latitudeLongitude();
           for (XsSize ind(0);ind<vect.size();ind++)
           {
            outputlog << vect[ind]<<" ";
           }
          }
          else
          {
           for(size_t ind=0;ind<2;ind++)outputlog<<"NaN ";
          }

          if(packet.containsAltitude())
          {
           outputlog<<packet.altitude() <<" ";
          }
          else
          {
           outputlog<<"NaN ";    //should it be 0.0000?
          }

//

          if(packet.containsCalibratedAcceleration())
          {
           XsVector vect=packet.calibratedAcceleration();
           for (XsSize ind(0);ind<vect.size();ind++)
           {
            outputlog << vect[ind]<<" ";
           }
          }

          if(packet.containsCalibratedMagneticField())
          {
           XsVector vect=packet.calibratedMagneticField();
           for (XsSize ind(0);ind<vect.size();ind++)
           {
            outputlog << vect[ind]<<" ";
           }
          }


          /*
          if(packet.containsStoredDeviceId())
          {
           std::cout <<"a faire\n";
          }
          if(packet.containsDetailedStatus())
          {
           std::cout <<"a faire\n";
          }
          */       
          if(packet.containsPressureAge())
          {
           //std::cout <<"a faire\n";
          }
          if(packet.containsFrameRange())
          {
           //std::cout <<"a faire\n";
          }
          if(packet.containsRawData()) std::cout <<"iciii\n";
          if(packet.containsRawAcceleration()) std::cout <<"iciii\n";
          if(packet.containsRawGyroscopeData()) std::cout <<"iciii\n";
          if(packet.containsRawGyroscopeTemperatureData()) std::cout <<"iciii\n";
          if(packet.containsPacketCounter8()) std::cout <<"iciii\n";
          if(packet.containsSampleTimeFine()) std::cout <<"iciii\n";
          if(packet.containsSampleTimeCoarse()) std::cout <<"iciii\n";
          if(packet.containsSampleTime64()) std::cout <<"iciii\n";
          if(packet.containsTemperature()) std::cout <<"iciii\n";
          if(packet.containsGpsPvtData()) std::cout <<"iciii1\n";
          if(packet.containsAnalogIn1Data()) std::cout <<"iciii4\n";
          if(packet.containsAnalogIn2Data()) std::cout <<"iciii5\n";
          if(packet.containsPositionLLA()) std::cout <<"iciii6\n";
          if(packet.containsAltitudeMsl()) std::cout <<"iciii9\n";
          if(packet.containsVelocity()) std::cout <<"iciii9\n";
          if(packet.containsUtcTime()) std::cout <<"iciii10\n";
          if(packet.containsRawGpsDop()) std::cout <<"iciii12\n";
          if(packet.containsRawGpsSol()) std::cout <<"iciii11\n";
          if(packet.containsRawGpsTimeUtc()) std::cout <<"iciii11\n";
          if(packet.containsRawGpsSvInfo()) std::cout <<"iciii11\n";
          if(packet.containsRawGnssPvtData()) std::cout <<"iciii11\n";
          if(packet.containsRawGnssSatInfo()) std::cout <<"iciii11\n";
          if(packet.containsFullSnapshot()) std::cout <<"iciii11\n";
          //if(packet.containsTriggerIndication()) std::cout <<"iciii11\n";
          if(packet.containsRawBlob()) std::cout <<"iciii11\n";
          //if(packet.contains()) std::cout <<"iciii\n";

          outputlog<<"\n";
         }
         outputlog.close();
        }
    }
    else
    {
     std::cout << "Load unsuccessful\n";
    }

    control->close();

    return 0;
}
