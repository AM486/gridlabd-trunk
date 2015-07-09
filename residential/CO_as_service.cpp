#include "CO_as_service.h"


#include <memory>
#include <staff/utils/Log.h>
#include <staff/common/logoperators.h>
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#include "controller_service.h"

using namespace std;

//#include "soapwebServiceSoap12BindingProxy.h"
//#include "StdAfx.h"
 //std::auto_ptr< ::WHeater > pWHeater(::staff::ServiceFactory::Inst().GetService< ::WHeater >());

  //  STAFF_ASSERT(pWHeater.get(), "Cannot get client for service WHeater!");

std::auto_ptr< ::energy::Controller::controller_service > pcontroller_service(::staff::ServiceFactory::Inst().GetService< ::energy::Controller::controller_service >());


CLASS* CO_as_service::oclass = NULL;

CO_as_service::CO_as_service(MODULE *module)
{
	if (oclass==NULL)
	{
		oclass = gl_register_class(module,"CO_as_service",sizeof(CO_as_service),PC_BOTTOMUP|PC_AUTOLOCK);
		if (oclass==NULL)
			GL_THROW("unable to register object class implemented by %s", __FILE__);

		if (gl_publish_variable(oclass,
				PT_double,"a",PADDR(a),PT_DESCRIPTION, "Total ",
				NULL)<1) 
			GL_THROW("unable to publish properties in %s",__FILE__);
		
		memset(this,0,sizeof(CO_as_service));
	}
}

int CO_as_service::create()
{

	
	return SUCCESS;
}

int CO_as_service::init(OBJECT *parent)
{

	
	double market_init_price = 0;
	int pstate = 0;
	int market_period = 0;
	int control_mode = 0;
	double psetpoint = 0;
	double base_setpoint = 0;
	double heating_base_setpoint = 0;
	double cooling_base_setpoint = 0;
	double COinitResult = pcontroller_service->COinit(market_init_price, pstate, market_period, control_mode, psetpoint, base_setpoint, heating_base_setpoint, cooling_base_setpoint);
	a=9;
	return SUCCESS;
}

int CO_as_service::isa(char *classname)
{
	return strcmp(classname,"CO_as_service")==0;
}

TIMESTAMP CO_as_service::sync(TIMESTAMP t0, TIMESTAMP t1)
{

	double base_setpoint = 0;
	double psetpoint = 0;
	int control_mode = 0;
	int COpresyncResult = pcontroller_service->COpresync(base_setpoint, psetpoint, control_mode);
	

	double load = 0;
	double demand = 0;
	int pstate = 0;
	double total = 0;
	double target = 0;
	double pAvg = 0;
	double pStd = 0;
	double market_current_frameclearing_price = 0;
	double COsyncResult = pcontroller_service->COsync(load, demand, pstate, total, target, pAvg, pStd, base_setpoint, control_mode, market_current_frameclearing_price);
	
	return TS_NEVER;
}

//////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF CORE LINKAGE
//////////////////////////////////////////////////////////////////////////

EXPORT int create_CO_as_service(OBJECT **obj, OBJECT *parent)
{
	try
	{
		*obj = gl_create_object(CO_as_service::oclass);
		if (*obj!=NULL)
		{
			CO_as_service *my = OBJECTDATA(*obj,CO_as_service);
			gl_set_parent(*obj,parent);
			return my->create();
		}
	}
	catch (const char *msg)
	{
		gl_error("create_CO_as_service: %s", msg);
		return 0;
	}
	return 1;
}

EXPORT int init_CO_as_service(OBJECT *obj, OBJECT *parent)
{
	try
	{
		if (obj!=NULL){
			return OBJECTDATA(obj,CO_as_service)->init(parent);
		}
	}
	catch (const char *msg)
	{
		char name[64];
		gl_error("init_CO_as_service(obj=%s): %s", gl_name(obj,name,sizeof(name)), msg);
		return 0;
	}
	return 1;
}

EXPORT int isa_CO_as_service(OBJECT *obj, char *classname)
{
	if(obj != 0 && classname != 0){
		return OBJECTDATA(obj,CO_as_service)->isa(classname);
	} else {
		return 0;
	}
}

EXPORT TIMESTAMP sync_CO_as_service(OBJECT *obj, TIMESTAMP t1, PASSCONFIG pass)
{
	TIMESTAMP t2 = TS_NEVER;
	CO_as_service *my = OBJECTDATA(obj,CO_as_service);
	switch (pass) {
	case PC_BOTTOMUP:
		t2 = my->sync(obj->clock,t1);
		obj->clock = t1;
		break;
	default:
		break;
	}
	return t2;
}