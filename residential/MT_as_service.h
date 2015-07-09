#ifndef _MT_as_service_h
#define _MT_as_service_h

#include <stdarg.h>
#include "gridlabd.h"


#include "residential.h"
class MT_as_service : public gld_object {
public:
	MT_as_service(MODULE *);
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

#endif //_MT_as_service_h