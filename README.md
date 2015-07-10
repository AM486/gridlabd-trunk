# gridlabd-trunk
gridlabd-trunk containing residential, market, generators folders

I have implemented 5 web services and the corresponting clients. The services are located 
on a virtual machine at http://10.96.12.47:9090/ . The clients that consume the services are running through 
gridlab-d and are located in the followin directories.

in residential folder:
								wheater_service.h:  service library
								wheater_serviceProxy.cpp:  service proxy
								wheater_serviceProxy.h:  service proxy library
								WH_as_service.cpp:  client
								WH_as_service.h:  client library
	
in market folder:
								controller_service.h:  service library
								controllerserviceProxy.cpp:  service proxy
								controllerserviceProxy.h:  service proxy library
								controller_service.cpp:  client
								controller_service.h:  client library							
								
in generators folder:
								microturbine_service.h:  service library
								microturbine_serviceProxy.cpp:  service proxy
								microturbine_serviceProxy.h:  service proxy library
								micro_service.cpp:  client
								micro_service.h:  client library	
								
								solarGen_service.h:  service library
								solarGen_serviceProxy.cpp:  service proxy
								solarGen_serviceProxy.h:  service proxy library
								solar_service.cpp:  client
								solar_service.h:  client library	
								
								windturbine_service.h:  service library
								windturbine_serviceProxy.cpp:  service proxy
								windturbine_serviceProxy.h:  service proxy library
								wind_service.cpp:  client
								wind_service.h:  client library	
