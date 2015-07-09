#include "S_as_service.h"


#include <memory>
#include <staff/utils/Log.h>
#include <staff/common/logoperators.h>
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#include "solarGen_service.h"

using namespace std;

//#include "soapwebServiceSoap12BindingProxy.h"
//#include "StdAfx.h"
 //std::auto_ptr< ::WHeater > pWHeater(::staff::ServiceFactory::Inst().GetService< ::WHeater >());

  //  STAFF_ASSERT(pWHeater.get(), "Cannot get client for service WHeater!");

std::auto_ptr< ::energy::Solar::solarGen_service > psolarGen_service(::staff::ServiceFactory::Inst().GetService< ::energy::Solar::solarGen_service >());

CLASS* S_as_service::oclass = NULL;

S_as_service::S_as_service(MODULE *module)
{
	if (oclass==NULL)
	{
		oclass = gl_register_class(module,"S_as_service",sizeof(S_as_service),PC_BOTTOMUP|PC_AUTOLOCK);
		if (oclass==NULL)
			GL_THROW("unable to register object class implemented by %s", __FILE__);

		if (gl_publish_variable(oclass,
				PT_double,"a",PADDR(a),PT_DESCRIPTION, "Total ",
				NULL)<1) 
			GL_THROW("unable to publish properties in %s",__FILE__);
		
		memset(this,0,sizeof(S_as_service));
	}
}

int S_as_service::create()
{
	double solarcreateResult = psolarGen_service->solarcreate();	
	return SUCCESS;
}

int S_as_service::init(OBJECT *parent)
{
	int gen_mode_v = 0;
    int gen_status_v = 0;
    int panel_type_v = 0;
    int solarinitResult = psolarGen_service->solarinit(gen_mode_v, gen_status_v, panel_type_v);
	a=9;
	return SUCCESS;
}

int S_as_service::isa(char *classname)
{
	return strcmp(classname,"S_as_service")==0;
}

TIMESTAMP S_as_service::sync(TIMESTAMP t0, TIMESTAMP t1)
{

	double solarsyncResult = psolarGen_service->solarsync(t0, t1);
		
	return TS_NEVER;
}

//////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF CORE LINKAGE
//////////////////////////////////////////////////////////////////////////

EXPORT int create_S_as_service(OBJECT **obj, OBJECT *parent)
{
	try
	{
		*obj = gl_create_object(S_as_service::oclass);
		if (*obj!=NULL)
		{
			S_as_service *my = OBJECTDATA(*obj,S_as_service);
			gl_set_parent(*obj,parent);
			return my->create();
		}
	}
	catch (const char *msg)
	{
		gl_error("create_S_as_service: %s", msg);
		return 0;
	}
	return 1;
}

EXPORT int init_S_as_service(OBJECT *obj, OBJECT *parent)
{
	try
	{
		if (obj!=NULL){
			return OBJECTDATA(obj,S_as_service)->init(parent);
		}
	}
	catch (const char *msg)
	{
		char name[64];
		gl_error("init_S_as_service(obj=%s): %s", gl_name(obj,name,sizeof(name)), msg);
		return 0;
	}
	return 1;
}

EXPORT int isa_S_as_service(OBJECT *obj, char *classname)
{
	if(obj != 0 && classname != 0){
		return OBJECTDATA(obj,S_as_service)->isa(classname);
	} else {
		return 0;
	}
}

EXPORT TIMESTAMP sync_S_as_service(OBJECT *obj, TIMESTAMP t1, PASSCONFIG pass)
{
	TIMESTAMP t2 = TS_NEVER;
	S_as_service *my = OBJECTDATA(obj,S_as_service);
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