// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/

#ifndef _solarGen_service_h_
#define _solarGen_service_h_

#include <staff/common/IService.h>

// *interface.targetNamespace: http://tempui.org/energy.Solar
// *interface.url: http://10.96.12.47:9090/axis2/services/staff.wsdl.Wsdl/get/energy.Solar/energy.Solar.solarGen_service.wsdl




namespace energy
{
namespace Solar
{

  //! solarGen_service service
  // *serviceUri: http://10.96.12.47:9090/axis2/services/energy.Solar.solarGen_service
  // *soapVersion: 1.1
  // *targetNamespace: http://tempui.org/energy.Solar
  class solarGen_service: public staff::IService
  {
  public:
    // *requestElement: solarcreate
    // *responseElement: solarcreateResult
    virtual double solarcreate() = 0;

    // *requestElement: solarinit
    // *responseElement: solarinitResult
    virtual int solarinit(int gen_mode_v, int gen_status_v, int panel_type_v) = 0;

    // *requestElement: solarsync
    // *responseElement: solarsyncResult
    virtual double solarsync(int t0, int t1) = 0;
  };

}
}

#endif // _solarGen_service_h_

