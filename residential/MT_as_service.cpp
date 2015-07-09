#include "MT_as_service.h"


#include <memory>
#include <staff/utils/Log.h>
#include <staff/common/logoperators.h>
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#include "microturbine_service.h"

using namespace std;

//#include "soapwebServiceSoap12BindingProxy.h"
//#include "StdAfx.h"
 //std::auto_ptr< ::WHeater > pWHeater(::staff::ServiceFactory::Inst().GetService< ::WHeater >());

  //  STAFF_ASSERT(pWHeater.get(), "Cannot get client for service WHeater!");

std::auto_ptr< ::energy::Microturbine::microturbine_service > pmicroturbine_service(::staff::ServiceFactory::Inst().GetService< ::energy::Microturbine::microturbine_service >());

CLASS* MT_as_service::oclass = NULL;

MT_as_service::MT_as_service(MODULE *module)
{
	if (oclass==NULL)
	{
		oclass = gl_register_class(module,"MT_as_service",sizeof(MT_as_service),PC_BOTTOMUP|PC_AUTOLOCK);
		if (oclass==NULL)
			GL_THROW("unable to register object class implemented by %s", __FILE__);

		if (gl_publish_variable(oclass,
				PT_double,"a",PADDR(a),PT_DESCRIPTION, "Total ",
				NULL)<1) 
			GL_THROW("unable to publish properties in %s",__FILE__);
		
		memset(this,0,sizeof(MT_as_service));
	}
}

int MT_as_service::create()
{

	
	return SUCCESS;
}

int MT_as_service::init(OBJECT *parent)
{
    double microturbine_initResult = pmicroturbine_service->microturbine_init();
	a=9;
	return SUCCESS;
}

int MT_as_service::isa(char *classname)
{
	return strcmp(classname,"MT_as_service")==0;
}

TIMESTAMP MT_as_service::sync(TIMESTAMP t0, TIMESTAMP t1)
{
	int microturbine_presyncResult = pmicroturbine_service->microturbine_presync(t0, t1);
	
	double CircuitA_V_Out_re = 0;
	double CircuitA_V_Out_im = 0;
	double CircuitB_V_Out_re = 0;
	double CircuitB_V_Out_im = 0;
	double CircuitC_V_Out_re = 0;
	double CircuitC_V_Out_im = 0;
	double LineA_V_Out_re = 0;
	double LineA_V_Out_im = 0;
	double LineB_V_Out_re = 0;
	double LineB_V_Out_im = 0;
	double LineC_V_Out_re = 0;
	double LineC_V_Out_im = 0;
	double microturbine_syncResult = pmicroturbine_service->microturbine_sync(CircuitA_V_Out_re, CircuitA_V_Out_im, CircuitB_V_Out_re, CircuitB_V_Out_im, CircuitC_V_Out_re, CircuitC_V_Out_im, LineA_V_Out_re, LineA_V_Out_im, LineB_V_Out_re, LineB_V_Out_im, LineC_V_Out_re, LineC_V_Out_im);
	
	return TS_NEVER;
}

//////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF CORE LINKAGE
//////////////////////////////////////////////////////////////////////////

EXPORT int create_MT_as_service(OBJECT **obj, OBJECT *parent)
{
	try
	{
		*obj = gl_create_object(MT_as_service::oclass);
		if (*obj!=NULL)
		{
			MT_as_service *my = OBJECTDATA(*obj,MT_as_service);
			gl_set_parent(*obj,parent);
			return my->create();
		}
	}
	catch (const char *msg)
	{
		gl_error("create_MT_as_service: %s", msg);
		return 0;
	}
	return 1;
}

EXPORT int init_MT_as_service(OBJECT *obj, OBJECT *parent)
{
	try
	{
		if (obj!=NULL){
			return OBJECTDATA(obj,MT_as_service)->init(parent);
		}
	}
	catch (const char *msg)
	{
		char name[64];
		gl_error("init_MT_as_service(obj=%s): %s", gl_name(obj,name,sizeof(name)), msg);
		return 0;
	}
	return 1;
}

EXPORT int isa_MT_as_service(OBJECT *obj, char *classname)
{
	if(obj != 0 && classname != 0){
		return OBJECTDATA(obj,MT_as_service)->isa(classname);
	} else {
		return 0;
	}
}

EXPORT TIMESTAMP sync_MT_as_service(OBJECT *obj, TIMESTAMP t1, PASSCONFIG pass)
{
	TIMESTAMP t2 = TS_NEVER;
	MT_as_service *my = OBJECTDATA(obj,MT_as_service);
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