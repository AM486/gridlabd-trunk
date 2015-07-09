#ifndef _CO_as_service_h
#define _CO_as_service_h

#include <stdarg.h>
#include "gridlabd.h"


#include "residential.h"
class CO_as_service : public gld_object {
public:
	CO_as_service(MODULE *);
	int create(void);
	int init(OBJECT *parent);
	int isa(char *classname);
	TIMESTAMP presync(TIMESTAMP t0, TIMESTAMP t1);
	TIMESTAMP sync(TIMESTAMP t0, TIMESTAMP t1);
	TIMESTAMP postsync(TIMESTAMP t0, TIMESTAMP t1);
	static CLASS *oclass;
public:
	double a;

};

#endif //_CO_as_service_h