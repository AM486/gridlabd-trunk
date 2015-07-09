#include "WT_as_service.h"


#include <memory>
#include <staff/utils/Log.h>
#include <staff/common/logoperators.h>
#include <staff/common/Exception.h>
#include <staff/client/ServiceFactory.h>
#include "windturbine_service.h"

using namespace std;

//#include "soapwebServiceSoap12BindingProxy.h"
//#include "StdAfx.h"
 //std::auto_ptr< ::WHeater > pWHeater(::staff::ServiceFactory::Inst().GetService< ::WHeater >());

  //  STAFF_ASSERT(pWHeater.get(), "Cannot get client for service WHeater!");

std::auto_ptr< ::energy::WindTurbine::windturbine_service > pwindturbine_service(::staff::ServiceFactory::Inst().GetService< ::energy::WindTurbine::windturbine_service >());

CLASS* WT_as_service::oclass = NULL;

WT_as_service::WT_as_service(MODULE *module)
{
	if (oclass==NULL)
	{
		oclass = gl_register_class(module,"WT_as_service",sizeof(WT_as_service),PC_BOTTOMUP|PC_AUTOLOCK);
		if (oclass==NULL)
			GL_THROW("unable to register object class implemented by %s", __FILE__);

		if (gl_publish_variable(oclass,
				PT_double,"a",PADDR(a),PT_DESCRIPTION, "Total ",
				NULL)<1) 
			GL_THROW("unable to publish properties in %s",__FILE__);
		
		memset(this,0,sizeof(WT_as_service));
	}
}

int WT_as_service::create()
{
	double windturb_dgcreateResult = pwindturbine_service->windturb_dgcreate();
	
	return SUCCESS;
}

int WT_as_service::init(OBJECT *parent)
{
	double pLine_I_A_Re = 0;
	double pLine_I_A_Im = 0;
	double pLine_I_B_Re = 0;
	double pLine_I_B_Im = 0;
	double pLine_I_C_Re = 0;
	double pLine_I_C_Im = 0;
	int windturb_dginitResult = pwindturbine_service->windturb_dginit(pLine_I_A_Re, pLine_I_A_Im, pLine_I_B_Re, pLine_I_B_Im, pLine_I_C_Re, pLine_I_C_Im);
	a=9;
	return SUCCESS;
}

int WT_as_service::isa(char *classname)
{
	return strcmp(classname,"WT_as_service")==0;
}

TIMESTAMP WT_as_service::sync(TIMESTAMP t0, TIMESTAMP t1)
{

	double pCircuit_V_A_Re = 0;
	double pCircuit_V_A_Im = 0;
	double pCircuit_V_B_Re = 0;
	double pCircuit_V_B_Im = 0;
	double pCircuit_V_C_Re = 0;
	double pCircuit_V_C_Im = 0;
	double windturb_dgsyncResult = pwindturbine_service->windturb_dgsync(pCircuit_V_A_Re, pCircuit_V_A_Im, pCircuit_V_B_Re, pCircuit_V_B_Im, pCircuit_V_C_Re, pCircuit_V_C_Im);
	int windturb_dg_postsyncResult = pwindturbine_service->windturb_dg_postsync(t0, t1);
	
	return TS_NEVER;
}

//////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF CORE LINKAGE
//////////////////////////////////////////////////////////////////////////

EXPORT int create_WT_as_service(OBJECT **obj, OBJECT *parent)
{
	try
	{
		*obj = gl_create_object(WT_as_service::oclass);
		if (*obj!=NULL)
		{
			WT_as_service *my = OBJECTDATA(*obj,WT_as_service);
			gl_set_parent(*obj,parent);
			return my->create();
		}
	}
	catch (const char *msg)
	{
		gl_error("create_WT_as_service: %s", msg);
		return 0;
	}
	return 1;
}

EXPORT int init_WT_as_service(OBJECT *obj, OBJECT *parent)
{
	try
	{
		if (obj!=NULL){
			return OBJECTDATA(obj,WT_as_service)->init(parent);
		}
	}
	catch (const char *msg)
	{
		char name[64];
		gl_error("init_WT_as_service(obj=%s): %s", gl_name(obj,name,sizeof(name)), msg);
		return 0;
	}
	return 1;
}

EXPORT int isa_WT_as_service(OBJECT *obj, char *classname)
{
	if(obj != 0 && classname != 0){
		return OBJECTDATA(obj,WT_as_service)->isa(classname);
	} else {
		return 0;
	}
}

EXPORT TIMESTAMP sync_WT_as_service(OBJECT *obj, TIMESTAMP t1, PASSCONFIG pass)
{
	TIMESTAMP t2 = TS_NEVER;
	WT_as_service *my = OBJECTDATA(obj,WT_as_service);
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