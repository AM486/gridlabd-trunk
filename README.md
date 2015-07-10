# gridlabd-trunk
gridlabd-trunk containing residential, market, generators folders

I have implemented 5 web services for **GRIDLAB-D**, a simulation software, and the respective clients. The services are 
located on a virtual machine at http://10.96.12.47:9090/ where you can log in with the default credentials. The clients 
that consume the services are running through **GRIDLAB-D** and are located in the following directories.

####in gridlab-d-code-5154-trunk/residential folder:						
								wheater_service.h:  service library
								wheater_serviceProxy.cpp:  service proxy
								wheater_serviceProxy.h:  service proxy library
								WH_as_service.cpp:  client
								WH_as_service.h:  client library
	
####in gridlab-d-code-5154-trunk/market folder:						
								controller_service.h:  service library
								controllerserviceProxy.cpp:  service proxy
								controllerserviceProxy.h:  service proxy library
								controller_service.cpp:  client
								controller_service.h:  client library

####in gridlab-d-code-5154-trunk/generators folder:						
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
								
